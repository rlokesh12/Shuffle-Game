#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<process.h>
#include<iostream>
#include<stdlib.h>
#include <sys/time.h>
#include <string>
#include <sstream>
#include<vector>
#include<cstdlib>
//for file reading
#include<fstream>
#include<iomanip>
//for audio playing
#include"mmsystem.h"


//--------
#define ON 1
#define OFF 0
//--------

using namespace std;
//------class start---------
class Player
{
	private: 
		string player_name;
		int classic_score;
		int time_score;
		int classic_mode;
		int time_mode; 
	public:
		void set_fields(string,int,int,int,int);
		void display();
		string get_name();
		int get_classic();
};

void Player :: set_fields(string s,int a,int b,int c,int d)
{
	player_name=s;
	classic_score=a;
	time_score=b;
	classic_mode=c;
	time_mode=d;
}

void Player :: display()
{
	cout<<"Player info:\n";
	cout<<"Player name : "<<player_name<<"\n";
	cout<<"Classic Score : "<<classic_score<<"\n";
	cout<<"Time Score : "<<time_score<<"\n";
	cout<<"Classic mode : "<<classic_mode<<"\n";
	cout<<"Time mode : "<<time_mode<<"\n";
}

string Player :: get_name()
{
	return player_name;
}

int  Player :: get_classic()
{
	return classic_mode;
}
//---------class done--------------

Player P;
int x,y;
int t_n=0;
int arr[8] = {1,2,3,4,5,6,7,8};
int placex_c[3] = {300,400,500};
int placey_c[3] = {250,350,450};
int placex_t[3] = {300,400,500};
int placey_t[3] = {350,450,550};
int emptyx = 2;
int emptyy = 2;
string current[3][3];
char name[80];


//functions definitions
int click_handle(int,int);
int start_click_handle(int,int);
int rule_click_handle(int,int);
int change_grid(int,int);
int change_grid_time(int,int);
int check_grid(int);
int back_start_click(int,int);
void time_locked();
void classic_func();
void time_func();
void start_func();
void rule_func();
void exit();
bool back_func();
void score_func();
bool back_func_classic(int,int);
void reset_grid();
void win_fun(int);
void update_high_classic();
void update_high_time();
void update_player(int);
void update_player_write();
void main_func();	// main start function
//----
void write_name(char);
void doCursor(int);
void newLine();
void getGrString(char *);
//-----
//finish


bool start_click=false,rule_click=false,exit_click=false,classic_click=false,time_click=false,back_click=false,score_click=false;
int high_score_classic,high_score_time,glag=0;
string high_name_classic,high_name_time;
static int mins=0,sec=5,score_classic=0,score_time,move=0;
int en_time_mode,cursor=30,len;
string all[100];

void update_player_write(){
	int l;
	ofstream file;
	file.open("player.txt",std::ofstream::out | std::ofstream::trunc);
	file.close();
	//int len = sizeof(all)/sizeof(*all);
	//cout<<all[0];
	file.open("player.txt");
	for(l=0;l<len;l++){
		cout<<"====="<<all[l];
		file<<all[l];
	}
	file.close();
}

void update_player(int opt){
	fstream file;
	string line,all[100];
	int l=0;
	len = 0;
	cout<<"--------opening file\n";
	file.open("player.txt");
	if(!file.is_open())
	{
		throw "File can't be opened!!";
	}
	try{
		while(getline(file,line))
		{
			all[l] = line;
			cout<<line<<"\t"<<all[l]<<"\n";
			int i=0;
			string check="";
			//cout<<line[0]<<"\t";
			while(line[i]!=' ')
			{
				check=check+line[i];
				i++;
			}
			//cout<<(check.c_str()).length();
			t_n=1;
			for(int j=0;j<i;j++)
			{
			//	cout<<name[j]<<"\t"<<check[j]<<"\n";
				if(name[j]!=check[j])
				{
					t_n=0;
					break;
				}
			}
			if(t_n==1)
			{
				string final_text="";
				cout<<"Match\n";
				i++;
				if(opt == 1){
					//string final_text="";
					string time_text="";
					while(line[i]!=' ')
						i++;
					i++;
					while(line[i]!=' '){
						time_text+=line[i];
						i++;
					}
					stringstream ss;
					ss<<score_classic;
					string s=ss.str();
					final_text = final_text + name+" "+s+" "+time_text+" 1 0\n";
				}
				else{
					//string final_text="";
					string classic_text="";
					while(line[i]!=' '){
						classic_text += line[i];
						i++;
					}
					stringstream ss;
					ss<<score_time;
					string s=ss.str();
					final_text = final_text+name+" "+classic_text+" "+s+" 1 1\n";
				}
				//return;
				//start_func();
				all[l] = final_text;
			}
			//cout<<i<<"\t"<<name.len()<<"\t";
		//	cout<<check.c_str()<<"\n";*/
			l++;
			len++;
		}
		
			//cout<<i<<"\t"<<name.len()<<"\t";
		//	cout<<check.c_str()<<"\n";
	}catch (const char *msg)
	{
		cout<<msg<<"\n";
	}
	file.close();
	update_player_write();
}

void update_high_classic()
{
	//clearing data on the high_score.txt file
	ofstream file;
	file.open("high_score.txt",std::ofstream::out | std::ofstream::trunc);
	file.close();
	//clearing done
	stringstream ss;
	ss<<score_classic;
	string s=ss.str();
	string text="";
	text = text+name+" "+s+"\n";
	file.open("high_score.txt");
	high_name_classic=name;
	high_score_classic=score_classic;
	file<<text.c_str();
	ss<<high_score_time;
	s=ss.str();
	text=high_name_time+" "+s;
	file<<text.c_str();
	file.close();
	
}

void update_high_time()
{
	//clearing data on the high_score.txt file
	ofstream file;
	file.open("high_score.txt",std::ofstream::out | std::ofstream::trunc);
	file.close();
	//clearing done
	file.open("high_score.txt");
	stringstream ss;
	ss<<high_score_classic;
	string s=ss.str();
	string text=high_name_classic+" "+s+"\n";
	file<<text.c_str();
	ss<<score_time;
	s=ss.str();
	text=name+s+"\n";
	high_name_time=name;
	high_score_time=score_time;
	file<<text.c_str();
	file.close();
}

void win_fun(int opt)
{
	bool back = false;
	cout<<"In win"<<opt<<"\n";
	cleardevice();
	//setting background color BLACK
    setbkcolor(BLACK);
    settextjustify(CENTER_TEXT,TOP_TEXT);
    
    //8 is complex_font
    x=getmaxx();
    y=getmaxy();
    if(opt == 1){
	    if(score_classic >= high_score_classic){
		    setcolor(RED);
		    outtextxy(x/2,y/6,"YOU WIN!!!");
		    setcolor(BLUE);
		    char text[100];
			outtextxy(x/2-50,y/6+60,"MODE  : CLASSIC");
			sprintf(text,"BEST  : %d ",high_score_classic);
		    outtextxy(x/2-110,y/6+120,text);
		    sprintf(text,"SCORE : %d ",score_classic);
		    outtextxy(x/2-115,y/6+180,text);
		}
		else{
			setcolor(RED);
		    outtextxy(x/2,y/6,"WE HAVE A HIGHSCORE!!!");
		    setcolor(BLUE);
		    char text[100];
			outtextxy(x/2-28,y/6+60,"MODE      : CLASSIC");
			sprintf(text,"PREV BEST  : %d ",high_score_classic);
		    outtextxy(x/2-72,y/6+120,text);
		    sprintf(text,"YOUR SCORE : %d ",score_classic);
		    outtextxy(x/2-98,y/6+180,text);
		    update_high_classic();
		}
		update_player(1);
	}
	else{
		sec++;
		if(sec==60){
			sec=0;
			mins++;
		}
		score_time = mins*100+sec;
		if(score_time>high_score_time){
			setcolor(RED);
		    outtextxy(x/2,y/6,"WE HAVE A HIGHSCORE!!!");
		    setcolor(BLUE);
		    char text[100];
			outtextxy(x/2-28,y/6+60,"MODE      : TIME");
			sprintf(text,"PREV BEST  : %d:%d ",high_score_time/100,high_score_time%100);
		    outtextxy(x/2-33,y/6+120,text);
		    if(sec>9)
		    	sprintf(text,"YOUR SCORE : %d:%d ",mins,sec);
		  	else
		  		sprintf(text,"YOUR SCORE : %d:0%d ",mins,sec);
		    outtextxy(x/2-31,y/6+180,text);
		    //taking name as input to store 
		    moveto(x/2,y/6+220);
		   // name=" ";
			outtext("Your name? : ");
			getGrString(name);
			newLine();
			moveto(x/2,y/6+250);
			outtext(name);
			newLine();
			//name done
		    update_high_time();
		}
		else{
			setcolor(RED);
		    outtextxy(x/2,y/6,"YOU WIN!!!");
		    setcolor(BLUE);
		    char text[100];
			outtextxy(x/2-50,y/6+60,"MODE  : TIME");
			if(high_score_time%100>9)
				sprintf(text,"BEST  : %d:%d ",high_score_time/100,high_score_time%100);
			else
				sprintf(text,"BEST  : %d:0%d ",high_score_time/100,high_score_time%100);
		    outtextxy(x/2-41,y/6+120,text);
		    if(sec>9)
		    	sprintf(text,"YOUR SCORE : %d:%d ",mins,sec);
		  	else
		  		sprintf(text,"YOUR SCORE : %d:0%d ",mins,sec);
		    outtextxy(x/2-100,y/6+180,text);
		}
		glag = 1;
		update_player(2);
	}
	setfillstyle(SOLID_FILL, WHITE);
	settextstyle(10,HORIZ_DIR,5);
	setcolor(RED);
	rectangle(700,450,900,520);
    setcolor(RED);
	outtextxy(785,460," Back");
	//handling back click
	
	setcolor(WHITE);
	
   //placing numbers in boxes
	int ret=0,mx,my;
    while (!ismouseclick(WM_LBUTTONDOWN))
    {
        delay(500); // 0.5 second delay, so there might be a several clicks
    }
	getmouseclick(WM_LBUTTONDOWN,mx,my);
   // cout<<getpixel(mx,my)<<"\n";
    //cout<<mx<<","<<my<<"\n"; 
 	if(back_func_classic(mx,my))
   	{
   		back_click=false;
   		reset_grid();
   		main_func();
   	}
//    while(back == false)    //uncomment for win check
//    	delay(500);
}


int click_handle(int cx,int cy)
{
	if(cx>=x/2-200 && cx<=x/2+200 && cy>=2*y/6-20 && cy<=2*y/6+50){
		start_click=true;
		return 1;
	}
	if(cx>=x/2-200 && cx<=x/2+200 && cy>=4*y/6-20 && cy<=4*y/6+60){
		rule_click=true;
		return 1;
	}
	if(cx>=x/2-200 && cx<=x/2+200 && cy>=5*y/6-20 && cy<=5*y/6+60){
		exit_click=true;
		return 1;
	}
	if(cx>=x/2-200 && cx<=x/2+200 && cy>=3*y/6-20 && cy<=3*y/6+60){
		score_click=true;
		return 1;
	}
	else{
		return 0;
	}	
}

int rule_back_handle(int cx,int cy)
{
	if(cx>=x/2-100 && cx<=x/2+100 && cy>=530 && cy<=600)
	{
		back_click=true;
		cout<<cx<<" "<<cy<<"\n";
		return 1;
	}
	else
	{
		return 0;
	}
}

int start_click_handle(int cx , int cy)
{
	if(cx>=x/2-200 && cx<=x/2+200 && cy>=2*y/6-20 && cy<=2*y/6+50)
	{
		classic_click=true;
		return 1;
	}
	if(cx>=x/2-200 && cx<=x/2+200 && cy>=3*y/6-20 && cy<=3*y/6+50)
	{
		try{
			if(en_time_mode != 1)
				throw "oops";
			time_click=true;
			return 1;
		}
		catch(const char* msg){
			time_locked();
		}
	}
	if(cx>=x/2-100 && cx<=x/2+100 && cy>=4*y/6-20 && cy<=4*y/6+50)
	{
		back_click=true;
		return 1;
	}
	else
	{
		return 0;
	}
}

bool back_func(int cx,int cy)
{
	if(cx>=700 && cx<=900 && cy>=570 && cy<=640)
	{
		back_click=true;
		return true;
	}
	else
	{
		return false;
	}
}

bool back_func_classic(int cx,int cy)
{
	if(cx>=700 && cx<=900 && cy>=470 && cy<=540)
	{
		back_click=true;
		return true;
	}
	else
	{
		return false;
	}
}

int back_score_click(int cx,int cy)
{
	if(cx>=x/2-200 && cx<=x/2+200 && cy>=4*y/6-20 && cy<=4*y/6+60)
	{
		back_click=true;
		return 1;
	}
	else
	{
		return 0;
	}
}

int change_grid(int cx,int cy)
{
	//cout<<";f\n";
	settextstyle(10,HORIZ_DIR,4);
	move++;
	int fx=0,fy=0;
	if(cx>250){
		if(cx>350){
			if(cx>450){
				if(cx>550){
					return 0;
				}
				else{
					fx=2;
				}
			}
			else{
				fx=1;
			}
		}
		else{
			fx=0;
		}
	}
	if(cy>200){
		if(cy>300){
			if(cy>400){
				if(cy>500){
					return 0;
				}
				else{
					fy=2;
				}
			}
			else{
				fy=1;
			}
		}
		else{
			fy=0;
		}
	}
	string temp;
	if(fx == emptyx+1 || fx == emptyx-1){
		if(fy == emptyy){
			if(fx == emptyx+1){
				current[emptyx][emptyy] = current[fx][fy];
				current[fx][fy] = "";
				emptyx = fx;
				emptyy = fy;
			}
			else{
				current[emptyx][emptyy] = current[fx][fy];
				current[fx][fy] = "";
				emptyx = fx;
				emptyy = fy;
			}
		}
		else
			return 0;	
	}
	else if(fx==emptyx){
		if(fy == emptyy+1){
			current[emptyx][emptyy] = current[fx][fy];
			current[fx][fy] = "";
			emptyx = fx;
			emptyy = fy;
		}
		else if(fy == emptyy-1){
			current[emptyx][emptyy] = current[fx][fy];
			current[fx][fy] = "";
			emptyx = fx;
			emptyy = fy;
		}
		else
			return 0;
	}
	else
		return 0;
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++)
			cout<<current[i][j]<<"\n";
	} 
	//cout<<"ënd\n";
	return 1;
}

int change_grid_time(int cx,int cy)
{
	//cout<<"here\n";
	int fx=0,fy=0;
	if(cx>250){
		if(cx>350){
			if(cx>450){
				if(cx>550){
					return 0;
				}
				else{
					fx=2;
				}
			}
			else{
				fx=1;
			}
		}
		else{
			fx=0;
		}
	}
	if(cy>300){
		if(cy>400){
			if(cy>500){
				if(cy>600){
					return 0;
				}
				else{
					fy=2;
				}
			}
			else{
				fy=1;
			}
		}
		else{
			fy=0;
		}
	}
	string temp;
	if(fx == emptyx+1 || fx == emptyx-1){
		if(fy == emptyy){
			if(fx == emptyx+1){
				current[emptyx][emptyy] = current[fx][fy];
				current[fx][fy] = "";
				emptyx = fx;
				emptyy = fy;
			}
			else{
				current[emptyx][emptyy] = current[fx][fy];
				current[fx][fy] = "";
				emptyx = fx;
				emptyy = fy;
			}
		}
		else
			return 0;	
	}
	else if(fx==emptyx){
		if(fy == emptyy+1){
			current[emptyx][emptyy] = current[fx][fy];
			current[fx][fy] = "";
			emptyx = fx;
			emptyy = fy;
		}
		else if(fy == emptyy-1){
			current[emptyx][emptyy] = current[fx][fy];
			current[fx][fy] = "";
			emptyx = fx;
			emptyy = fy;
		}
		else
			return 0;
	}
	else
		return 0;
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++)
			cout<<current[i][j]<<"\n";
	} 
	//cout<<"ënd\n";
	return 1;
}

int check_grid(int opt)
{
	
	int count = 1;
	int flag = 1;
	win_fun(1);			//uncomment for win check classic
	//win_fun(2);		//uncomment for win check time
	if(current[0][0] == ""){
		for(int i=0; i<3; i++){
			if(flag==0)
				break;
			for(int j=0; j<3; j++){
				if(i==0 && j==0)
					continue;
				if(atoi(&(current[j][i])[0u]) == count)
					count++;
				else{
					flag = 0;
					break;
				}
			}
		}
	}
	else if(current[2][2] == ""){
		for(int i=0; i<3; i++){
			if(flag==0)
				break;
			for(int j=0; j<3; j++){
				if(i==2 && j==2)
					continue;
				if(atoi(&(current[j][i])[0u]) == count)
					count++;
				else{
					flag = 0;
					break;
				}
			}
		}
	}
	else
		flag = 0;
	if(flag==1){
		cout<<"Done!!\n";
		win_fun(opt);
	}
	else
		cout<<"Not yet!!\n";
	//flag=1;
	return flag;
}

void classic_func()
{	
	cout<<score_classic<<"=============== "<<move<<"\n";
	int result;
	cleardevice();
	setbkcolor(BLACK);
    settextjustify(CENTER_TEXT,TOP_TEXT);
    settextstyle(10,HORIZ_DIR,4);
    //showing best scores:
    char text[100];
    setcolor(WHITE);
    //sprintf(text,"BEST:- \nName: %s , Score: %d ",high_name_classic.c_str(),high_score_classic);
    sprintf(text,"BEST: %d ",high_score_classic);
    outtextxy(x/2+300,50,text);
  	settextstyle(10,HORIZ_DIR,4);
	sprintf(text,"MOVES : %d ",score_classic);
    outtextxy(150,250,text);
    setcolor(BLUE);
    settextstyle(10,HORIZ_DIR,5);
    outtextxy(x/2,100," LET'S PLAY !!!");
    line(0,150,1000,150);
    setcolor(WHITE);
    //making boxes
    line(250,200,550,200);
    line(250,200,250,500);
   	// line(650,200,650,600);
    line(350,200,350,500);
    line(450,200,450,500);
    line(550,200,550,500);
    line(250,300,550,300);
    line(250,400,550,400);
    line(250,500,550,500);
   	// line(250,600,650,600);
   	//boxes done
   	//place values
   	for(int i=0;i<8;i++){
   		cout<<arr[i]<<"\n";	
	}
   	
   	int count = 1;
   	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			setcolor(count);
			string s;
			s = current[i][j];
			outtextxy(placex_c[i],placey_c[j],&s[0u]);
			count++;
		}
   	}
   	
   settextstyle(8,HORIZ_DIR,3);
   
   //helping text side to shuffle to box
   outtextxy(800,200,"	Help !!!");
   line(650,230,950,230);
   outtextxy(800,300,"	click on the adjacent");
   outtextxy(800,340,"	numbers around the");
   outtextxy(800,380, "	empty box to");
   outtextxy(800,410,"	exchange their postions.");
   //help text done
   
   //for back button
	setfillstyle(SOLID_FILL, WHITE);
	settextstyle(10,HORIZ_DIR,5);
	setcolor(RED);
	rectangle(700,470,900,540);
    setcolor(RED);
	outtextxy(785,480," Back");
	//handling back click
	
	setcolor(WHITE);
	settextstyle(10,HORIZ_DIR,4);
	sprintf(text,"MOVES : %d ",move);
    outtextxy(150,250,text);
    settextstyle(10,HORIZ_DIR,5);
   //placing numbers in boxes
	int ret=0,mx,my;
   	while(ret==0)
	{
	    while (!ismouseclick(WM_LBUTTONDOWN))
	    {
	        delay(500); // 0.5 second delay, so there might be a several clicks
	    }
	    settextstyle(10,HORIZ_DIR,5);
    	getmouseclick(WM_LBUTTONDOWN,mx,my);
    
	   // cout<<getpixel(mx,my)<<"\n";
	    //cout<<mx<<","<<my<<"\n"; 
     	if(back_func_classic(mx,my))
	   	{
	   		back_click=false;
	   		reset_grid();
	   		main_func();
	   	}
	    ret = change_grid(mx,my);
	    
	}
	result = check_grid(1);
	if(result == 0)
		classic_func();
}

void time_func()
{
	//cout<<"Time attack";
	cleardevice();
	setbkcolor(BLACK);
    settextjustify(CENTER_TEXT,TOP_TEXT);
   	//showing best scores:
    settextstyle(8,HORIZ_DIR,3);
    char text[100];
    setcolor(WHITE);
    if(high_score_time%100>9)
    {
		sprintf(text,"Best: %d:%d ",high_score_time/100,high_score_time%100);
	}
	else
	{
		sprintf(text,"Best: %d:0%d ",high_score_time/100,high_score_time%100);	
	}
    outtextxy(x/2+300,50,text);
   
    settextstyle(10,HORIZ_DIR,5);
    setcolor(BLUE);
    outtextxy(x/2,100," LET'S PLAY !!!");
    line(0,150,1000,150);
    setcolor(WHITE);
    //making boxes
    //first horizontal line
    line(250,300,550,300);
    //veritcal lines
    line(250,300,250,600);
   	// line(650,200,650,600);
    line(350,300,350,600);
    line(450,300,450,600);
    line(550,300,550,600);
    //rest horizontal lines
    line(250,400,550,400);
    line(250,500,550,500);
    line(250,600,550,600);
   	// line(250,600,650,600);
   	//boxes done

   	for(int i=0;i<8;i++)
	{
   		cout<<arr[i]<<"\n";	
	}
   	
   	int count = 1;
   	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			setcolor(count);
			string s;
			s = current[i][j];
			outtextxy(placex_t[i],placey_t[j],&s[0u]);
			count++;
		}
   	}
   	
   settextstyle(8,HORIZ_DIR,3);
   
   //helping text side to shuffle to box
   outtextxy(800,300,"	Help !!!");
   line(650,330,950,330);
   outtextxy(800,400,"	click on the adjacent");
   outtextxy(800,440,"	numbers around the");
   outtextxy(800,480, "	empty box to");
   outtextxy(800,510,"	exchange their postions.");
   //finish help text
   
   //for back button
	setfillstyle(SOLID_FILL, WHITE);
	settextstyle(10,HORIZ_DIR,5);
	setcolor(RED);
	rectangle(700,570,900,640);
    setcolor(RED);
	outtextxy(785,580," Back");
	//handling back click
	setcolor(WHITE);
   //placing numbers in boxes
	int ret=0,mx,my;
	char d[50];
   	while(ret==0)
	{
	    while (!ismouseclick(WM_LBUTTONDOWN) && mins>=0 && sec>=0)
	    {
	    		if(mins==0 && sec==0)
				{
					outtextxy(x/2,50,"GAME OVER");
					//cout<<"timer finish\n";
					break;
				}
	    		if(sec>9)
				{
					sprintf(d,"TIME LEFT: %d:%d ",mins,sec);
				}
				else
				{
					sprintf(d,"TIME LEFT: %d:0%d ",mins,sec);
				}
				outtextxy(x/2,200,d);
				
				sec--;
				if(sec==0)
				{
					mins--;
					sec=59;
				}
				delay(1000);
				
	    }
	    cout<<mins<<" "<<sec<<"\n";
		if(mins==-1 && sec==59)
		{
			outtextxy(x/2,50,"GAME OVER");
		//	cout<<"timer finish\n";
			glag=1;
			break;
		}
	
    	getmouseclick(WM_LBUTTONDOWN,mx,my);
    
	   //cout<<getpixel(mx,my)<<"\n";
	   cout<<mx<<" "<<my<<"\n";
	   if(back_func(mx,my))
	   {	
	   	cout<<"time_back";
	   	
	   		back_click=false;
	   		mins=4;
	   		sec=59;
	   		reset_grid();
	   		main_func();
	   }
	  // cout<<mx<<","<<my<<"\n"; 
	    ret = change_grid_time(mx,my);
	}
	check_grid(2);
	if(glag!=1)
	{
		time_func();
	}
    while (!ismouseclick(WM_LBUTTONDOWN))
    {
        delay(500); // Five second delay, so there might be a several clicks
    }
	getmouseclick(WM_LBUTTONDOWN,mx,my);
	//PlaySound(TEXT("sound3.wav"),NULL,SND_SYNC); 
	
	if(back_func(mx,my))
    {	
   	cout<<"time_back";
   	
   		back_click=false;
   		mins=4;
   		sec=59;
   		reset_grid();
   		main_func();
   }
   	
	//time done
   	
}

void score_func()
{
	cleardevice();
	setbkcolor(BLACK);
	settextjustify(CENTER_TEXT,TOP_TEXT);
    settextstyle(10,HORIZ_DIR,5);
    setcolor(WHITE);
    outtextxy(x/2,y/6,"!! HIGH SCORE !!");
    line(200,2*y/6-30,800,2*y/6-30);
	char text[100];
    //sprintf(text,"BEST:- \nName: %s , Score: %d ",high_name_classic.c_str(),high_score_classic);
    sprintf(text,"Best Classic: %d ",high_score_classic);
    outtextxy(x/2,2*y/6,text);
    //sprintf(text,"BEST:- \nName: %s , Score: %d ",high_name_classic.c_str(),high_score_classic);
    int high_min=0,high_sec=0,score=high_score_time;
    high_sec = score%100;
    high_min = score/100;
//    while(score>=60)
//    {
//    	score-=60;
//    	high_min++;
//	}
//	high_sec=score;
	if(high_sec>9)
	{
    	sprintf(text,"Best Time: %d:%d",high_min,high_sec);
    }
    else
    {
    	sprintf(text,"Best Time: %d:0%d",high_min,high_sec);
	}
    outtextxy(x/2,3*y/6,text);
     //for back button
	setfillstyle(SOLID_FILL, WHITE);
	settextstyle(10,HORIZ_DIR,5);
	setcolor(RED);
	rectangle(x/2-200,4*y/6-20,x/2+200,4*y/6+60);
    setcolor(RED);
	outtextxy(x/2,4*y/6," Back");
	//handling back click
	int mx,my,ret=0;
   // reset_grid();
    while(ret==0)
	{
	    while (!ismouseclick(WM_LBUTTONDOWN))
	    {
	        delay(500); // Five second delay, so there might be a several clicks
	    }
    	getmouseclick(WM_LBUTTONDOWN,mx,my);
    	//PlaySound(TEXT("sound3.wav"),NULL,SND_SYNC); 
    	ret=back_score_click(mx,my);
	}
	if(back_click)
	{
		back_click=false;
		main_func();
	}
   
}

void take_name()
{
	cleardevice();
	char n[80];
	setfillstyle(SOLID_FILL, WHITE);
	setcolor(MAGENTA);
	rectangle(x/2-200,350-20,x/2+200,350+130);
    setcolor(MAGENTA);
	outtextxy(x/2,350,"Enter Name");

	moveto(x/2-50,400);
//	outtextxy(x/2,350,"Enter Name : ");
	getGrString(n);
	strcpy(name,n);
	newLine();
	//moveto(x/2,450);
	//outtext("Welcome name ");
	outtext(name);
	newLine();
	//checking if the name is in player.txt file or not
	ifstream file;
	string line;
	int l=0;
	//cout<<"opening file\n";
	file.open("player.txt");
	if(!file.is_open())
	{
		throw "File can't be opened!!";
	}
	try{
			while(getline(file,line))
			{
				//cout<<line<<"\t"<<name<<"\n";
				int i=0;
				string check="";
				//cout<<line[0]<<"\t";
				while(line[i]!=' ')
				{
					check=check+line[i];
					i++;
				}
				//cout<<(check.c_str()).length();
				t_n=1;
				for(int j=0;j<i;j++)
				{
					cout<<name[j]<<"\t"<<check[j]<<"\n";
					if(name[j]!=check[j])
					{
						t_n=0;
						break;
					}
				}
				if(t_n==1)
				{
					cout<<"Match\n";
					istringstream iss(line);
					vector <string> v;
					do
					{
						string data;
						iss>>data;
						v.push_back(data);
						
					}while(iss);
					int d1,d2,d3,d4;
				//	high_name_classic=v[0];
				//yha pe string ka data separate krke .. d1 ,d2,d3,d4 me daala h 
				//order:  classic_score    time_mode_score    classic_mode    time_mode
					stringstream str(v[1]);
					str>>d1;
					stringstream str1(v[2]);
					str1>>d2;
					stringstream str2(v[3]);
					str2>>d3;
					stringstream str3(v[3]);
					str3>>d4;
					v.clear();
					//yeh player class ka function h 
					P.set_fields(name,d1,d2,d3,d4);
					P.display();
					// yha pe time vale ke liye check kiya h ... neeche func likh dena tumara jba time_func ko call 
					// krte h.. vha comment kr diya h maine... okh/
					if(P.get_classic()==1)
					{
						cout<<"\nclassic is one and time mode enabled\n";
						en_time_mode=1;
					}
					cursor=30;
					//return;
					start_func();
				}
				//cout<<i<<"\t"<<name.len()<<"\t";
			//	cout<<check.c_str()<<"\n";*/
			}
			file.close();
			if(t_n==1)
				{
					cout<<"Match\n";
					istringstream iss(line);
					vector <string> v;
					do
					{
						string data;
						iss>>data;
						v.push_back(data);
						
					}while(iss);
					int d1,d2,d3,d4;
				//	high_name_classic=v[0];
					stringstream str(v[1]);
					str>>d1;
					stringstream str1(v[2]);
					str1>>d2;
					stringstream str2(v[3]);
					str2>>d3;
					stringstream str3(v[3]);
					str3>>d4;
					v.clear();
					//cursor=30;
					P.set_fields(name,d1,d2,d3,d4);
					P.display();
					if(P.get_classic()==1)
					{
						en_time_mode=1;
					}
					//return;
					start_func();
				}
				//cout<<i<<"\t"<<name.len()<<"\t";
			//	cout<<check.c_str()<<"\n";
	}catch (const char *msg)
	{
		cout<<msg<<"\n";
	}
	//player.txt file done
	
	t_n=0;
	P.set_fields(name,0,0,0,0);
	P.display();
	//writing to the file
	ofstream myfile;
	myfile.open("player.txt",std::ios::app);
	string str=name;
	name[str.length()-1]=' ';
	name[str.length()]='0';
	name[str.length()+1]=' ';
	name[str.length()+2]='0';
	name[str.length()+3]=' ';
	name[str.length()+4]='0';
	name[str.length()+5]=' ';
	name[str.length()+6]='0';
	name[str.length()+7]='\n';

	
	str=name;
	myfile<<str;
	myfile.close();
	//return;
	cursor=30;
	start_func();
	
}

void time_locked(){
	cleardevice();
	setbkcolor(BLACK);
    settextjustify(CENTER_TEXT,TOP_TEXT);
    settextstyle(10,HORIZ_DIR,4);
    setcolor(RED);
	outtextxy(x/2,100," Mode locked !!!");
	line(0,150,x,150);
	setcolor(WHITE);
	settextstyle(8,HORIZ_DIR,3);
	outtextxy(x/2,200,"To unlock Time mode :");
	line(200,230,800,230);
	//outtextxy(x/2,250,"1.Classic Mode:);
	outtextxy(x/2,280,"	Complete Classic mode once");
//	outtextxy(x/2,310,"		Arrange all the numbers");
//	line(200,360,800,360);
//	outtextxy(x/2,380,"2.Time Mode:");
//	outtextxy(x/2,410,"		Time limit (5 min)");
	outtextxy(x/2,440,"		All the best");
	//outtextxy(x/2,480,"		Rest rules are as same as Classic mode");
	
	//for back button
	setfillstyle(SOLID_FILL, WHITE);
	settextstyle(10,HORIZ_DIR,5);
	setcolor(RED);
	rectangle(x/2-100,530,x/2+100,600);
    setcolor(RED);
	outtextxy(x/2,540," Back");
	//handling back click
	int mx,my,ret=0;
	while(ret==0)
	{
	    while (!ismouseclick(WM_LBUTTONDOWN))
	    {
	        delay(500); // 0.5 second delay, so there might be a several clicks
	    }
    	getmouseclick(WM_LBUTTONDOWN,mx,my);
	    //cout<<getpixel(mx,my)<<"\n";
	    //cout<<mx<<","<<my<<"\n"; 
	    ret = rule_back_handle(mx,my);
	}
	if(back_click)
    {
    	if(back_click)
    	{
    		back_click=false;
    		start_func();
		}
		
	}
}

void start_func()
{
	cleardevice();
	setbkcolor(BLACK);
    settextjustify(CENTER_TEXT,TOP_TEXT);
    settextstyle(10,HORIZ_DIR,5);
    setcolor(WHITE);
	char h[50];
	sprintf(h,"Welcome %s",(P.get_name()).c_str());
    //h="Welcome "+P.get_name();
    outtextxy(x/2,50,h);
	outtextxy(x/2,100," Choose Your Mode !!!");
	//making option rectangles
	setfillstyle(SOLID_FILL, WHITE);
	setcolor(RED);
	rectangle(x/2-200,2*y/6-20,x/2+200,2*y/6+50);
    setcolor(RED);
	outtextxy(x/2,2*y/6,"Classic Mode");
	//rectangle for second option
	setfillstyle(SOLID_FILL, WHITE);
	setcolor(BLUE);
	rectangle(x/2-200,3*y/6-20,x/2+200,3*y/6+50);
    setcolor(BLUE);
	outtextxy(x/2,3*y/6,"Time Mode");
	//for back button
	setfillstyle(SOLID_FILL, WHITE);
	settextstyle(10,HORIZ_DIR,5);
	setcolor(MAGENTA);
	rectangle(x/2-100,4*y/6-20,x/2+100,4*y/6+50);
    setcolor(MAGENTA);
	outtextxy(x/2,4*y/6,"Back");
	//handling back click
//	PlaySound(TEXT("sound2.wav"),NULL,SND_SYNC);
	//mouse click functions
	int mx,my,ret=0;
	while(ret==0)
	{
	    while (!ismouseclick(WM_LBUTTONDOWN))
	    {
	        delay(500); // 0.5 second delay, so there might be a several clicks
	    }
    	getmouseclick(WM_LBUTTONDOWN,mx,my);
    //	PlaySound(TEXT("sound3.wav"),NULL,SND_SYNC);
	   // cout<<getpixel(mx,my)<<"\n";
	    cout<<mx<<","<<my<<"\n"; 
	    ret = start_click_handle(mx,my);
	}
	if(classic_click || time_click || back_click)
    {
    	if(classic_click)
    	{
    		classic_click=false;
    		classic_func();
    		
		}
		if(time_click)
		{
			time_click=false;
			if(en_time_mode==1)
			{
				en_time_mode=0;
				time_func();
			}
			
		}
		if(back_click)
    	{
    		back_click=false;
    		main_func();
		}
		
	}
	
}

void rule_func()
{
	cleardevice();
	setbkcolor(BLACK);
    settextjustify(CENTER_TEXT,TOP_TEXT);
    settextstyle(10,HORIZ_DIR,4);
    setcolor(LIGHTCYAN);
	outtextxy(x/2,100," Know The Rules !!!");
	line(0,150,x,150);
	setcolor(WHITE);
	settextstyle(8,HORIZ_DIR,3);
	outtextxy(x/2,200,"There are two modes :");
	line(200,230,800,230);
	outtextxy(x/2,250,"1.Classic Mode:");
	outtextxy(x/2,280,"		No time limit");
	outtextxy(x/2,310,"		Arrange all the numbers");
	line(200,360,800,360);
	outtextxy(x/2,380,"2.Time Mode:");
	outtextxy(x/2,410,"		Time limit (5 min)");
	outtextxy(x/2,440,"		If not completed in given time limit ,game will be closed");
	outtextxy(x/2,480,"		Rest rules are as same as Classic mode");
	
	//for back button
	setfillstyle(SOLID_FILL, WHITE);
	settextstyle(10,HORIZ_DIR,5);
	setcolor(RED);
	rectangle(x/2-100,530,x/2+100,600);
    setcolor(RED);
	outtextxy(x/2,540," Back");
	//handling back click
	int mx,my,ret=0;
	while(ret==0)
	{
	    while (!ismouseclick(WM_LBUTTONDOWN))
	    {
	        delay(500); // 0.5 second delay, so there might be a several clicks
	    }
    	getmouseclick(WM_LBUTTONDOWN,mx,my);
	    //cout<<getpixel(mx,my)<<"\n";
	    //cout<<mx<<","<<my<<"\n"; 
	    ret = rule_back_handle(mx,my);
	}
	if(back_click)
    {
    	if(back_click)
    	{
    		back_click=false;
    		main_func();
		}
		
	}
		
}

//-----------------------------------------------

void write_name(char inputChar)
{
	cout<<inputChar<<"\n";
   	char t[10];
   	sprintf(t,"%c",inputChar);
   	cout<<"t is : "<<t<<"\n";
   	outtextxy(x/2+cursor-50,410,t);
   	cursor+=30;
   	
}

void newLine()
{
  moveto(0,gety()+textheight("A"));
}
void getGrString(char *inputString)
{
 /* stringIndex is the current place in the string, so that we
    may build it as we go along getting input characters */
 int stringIndex=0;
 /* xVal will store the screen position for each char as we go
    along, so that we can erase and move the cursor
    successfully during backspacing */
 int xVal[255];
 /* inputChar: the character typed;  outString: the string
    version of that character */
 char inputChar, outString[2];
 /* oldColor saves the previous color value, to restore after
    erasing */
 int oldColor;
 /* outString is just one char + a null-terminator */
 outString[1]=0;
 /* screen starting position for input char string */
 xVal[0]=getx();
 do
 {
    /* turn on the cursor */
    doCursor(ON);
    /* get a single character, in no-echo mode */
    inputChar=getch();
    //writing input name to screen
    write_name(inputChar);
   //writing done
    /* turn off the cursor before we write a new character */
    doCursor(OFF);
    /* avoid dealing with all special keys */
    if (inputChar==0) getch();
    else
    {
        if (inputChar==8) { /* backspace */
            /* save old character color */
            oldColor=getcolor();
            /* back up in the string */
            --stringIndex;
            /* no backing up past beginning of string! */
            if (stringIndex<0) stringIndex=0;
            /* move to (old horz position, current vert
               position) */
            moveto(xVal[stringIndex],gety());
            /* erasing consists of rewriting the old character
               in the background color */
            setcolor(getbkcolor());
            outString[0]=inputString[stringIndex];
            outtext(outString);
            
            /* correct the current screen position since it
               will have advanced after writing outString */
            moveto(xVal[stringIndex],gety());
            /* restore the text color we had */
            setcolor(oldColor);
        }
        else { /* put a character into the string and draw it
                  on screen */
            /* stuff the input into the string */
            inputString[stringIndex]=inputChar;
            /* draw the character on screen, as a string
               (since that's what outttext() needs) */
            outString[0]=inputChar;
            outtext(outString);
            /* proceed to next char in the string */
            ++stringIndex;
            /* save horz position for possible backspacing */
            xVal[stringIndex]=getx();
        }
     }
 /* end getting characters on ENTER or LF */
 } while(inputChar!=13 && inputChar!=10);
 /* null-terminate input string before returning */
 inputString[stringIndex]=0;
}
void doCursor(int on) 
{
  int curX,oldColor;
  /* we'll use an underbar as a cursor */
  char uBarStr[2] = { '_',0 };
  /* if cursor goes OFF, erase by drawing w/bkground color */
  if (!on) {
      oldColor=getcolor();
      setcolor(getbkcolor());
  }
  /* save horizontal position before drawing cursor */
  curX=getx();
  outtext(uBarStr);
  moveto(curX,gety());
  /* if we changed the color to erase cursor, change it back */
  if (!on) setcolor(oldColor);
}
void exit_func()
{
	/*cleardevice();
	moveto(400,300);
	char name[80];
	outtext("Your name? : ");
	getGrString(name);
	newLine();
	moveto(600,300);
	outtext("Your name is :");
	outtext(name);
	newLine();*/
	closegraph();
	exit(0);
}

//---------------------------------------------
void main_func()
{
	
	cleardevice();
	//setting background color BLACK
    setbkcolor(BLACK);
    settextjustify(CENTER_TEXT,TOP_TEXT);
    
    //8 is complex_font
    x=getmaxx();
    y=getmaxy();
    setcolor(WHITE);
    settextstyle(1,HORIZ_DIR,5);
    outtextxy(x/2,40,"!! SHUFFLE GAME !!");
    settextstyle(10,HORIZ_DIR,5);
    setcolor(WHITE);
    outtextxy(x/2,y/6," WELCOME !!!");
    
    //rectangle for start game 
	setfillstyle(SOLID_FILL, WHITE);
	setcolor(MAGENTA);
	rectangle(x/2-200,2*y/6-20,x/2+200,2*y/6+50);
    setcolor(MAGENTA);
	outtextxy(x/2,2*y/6,"Start Game");

	//rectangle finish
	setfillstyle(SOLID_FILL, WHITE);
	setcolor(BROWN);
	rectangle(x/2-200,3*y/6-20,x/2+200,3*y/6+60);
    setcolor(BROWN);
    outtextxy(x/2,3*y/6," High Score");
    
    //rectangle for rules
    setfillstyle(SOLID_FILL, WHITE);
	setcolor(BLUE);
	rectangle(x/2-200,4*y/6-20,x/2+200,4*y/6+60);
    setcolor(BLUE);
	outtextxy(x/2,4*y/6,"Know The Rules");

	//rectangle finish
	
	//rectangle for exit
   	setfillstyle(SOLID_FILL, WHITE);
	setcolor(RED);
	rectangle(x/2-200,5*y/6-20,x/2+200,5*y/6+60);
    setcolor(RED);
	outtextxy(x/2,5*y/6," EXIT");
    //rectangle finish for exit	 

    //registermousehandler(WM_LBUTTONDOWN,click_handler);
    int mx,my,ret=0;
   // reset_grid();
    while(ret==0)
	{
	    while (!ismouseclick(WM_LBUTTONDOWN))
	    {
			//PlaySound(TEXT("sound2.wav"),NULL,SND_SYNC);
	        delay(500); // Five second delay, so there might be a several clicks
	    }
    	getmouseclick(WM_LBUTTONDOWN,mx,my);
    	//PlaySound(TEXT("sound3.wav"),NULL,SND_SYNC);
	    //cout<<getpixel(mx,my)<<"\n";
	    //cout<<mx<<","<<my<<"\n"; 
	    ret = click_handle(mx,my);
	}
    if(start_click || rule_click || exit_click || score_click)
    {
    	if(start_click)
    	{
    		start_click=false;
    		take_name();
    		//start_func();
    		
		}
		if(rule_click)
		{
			rule_click=false;
			rule_func();
		
		}
		if(exit_click)
		{
			exit_click=false;
			exit_func();
			
		}
		if(score_click)
		{
			score_click=false;
			score_func();
		}
	}
}

void reset_grid(){
	//cout<<"Resetting grid===\n";
	for (int i=7; i>0; --i)
  	{
    	//get swap index
    	int j = rand()%i;
    	//swap arr[i] with arr[j]
    	int temp = arr[i];
    	arr[i] = arr[j];
    	arr[j] = temp;
  	}
	current[2][2] = "";
  	int count = 1;
  	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			if(count > 8)
				continue;
  			ostringstream str1;
			string s;
			str1 << arr[count-1];
			s = str1.str();
			current[i][j] = s;
			count++;
		}	
	}
	cout<<"Resetting grid";
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			cout<<current[i][j]<<"\n";
		}
	}
	emptyx = 2;
	emptyy = 2;
	score_classic=0;
	move=0;
	cout<<score_classic<<" "<<move<<"\n";
}

int main( )
{

	//Getting random seq of numbers
	//shuffle arr
	reset_grid();
	//reading data from file for high score
	ifstream file;
	string line;
	int l=0;
	//cout<<"opening file\n";
	file.open("high_score.txt");
	if(!file.is_open())
	{
		throw "File can't be opened!!";
	}
	try{
			while(getline(file,line))
			{
				cout<<line<<"\n";
				istringstream iss(line);
				vector <string> v;
				do
				{
					string data;
					iss>>data;
					v.push_back(data);
					
				}while(iss);
				if(l==0)
				{
					high_name_classic=v[0];
					stringstream str(v[1]);
					str>>high_score_classic;
					v.clear();
				}
				else
				{
					high_name_time=v[0];
					stringstream str(v[1]);
					str>>high_score_time;
					file.close();
					
				}
				l++;
				
			}
			file.close();
	}catch (const char *msg)
	{
		cout<<msg<<"\n";
	}
	//cout<<"name: "<<high_name_classic<<"  score: "<<high_score_classic<<"\n";
	//cout<<"name: "<<high_name_time<<"  score: "<<high_score_time<<"\n";
	//cout<<"opening window\n";
   	initwindow(1000,1000,"first_page");
   //  int gdriver = DETECT, gmode;
     // initgraph(&gdriver, &gmode, NULL);
    
    //calling main start function
    main_func();
    
   	getch();
   	closegraph();
   
    return 0;
}

/*Name	Value   	Description
DEFAULT_FONT	0	8x8 bit-mapped font
TRIPLEX_FONT	1	Stroked triplex font
SMALL_FONT	2	Stroked small font
SANS_SERIF_FONT	3	Stroked sans-serif font
GOTHIC_FONT	4	Stroked gothic font
SCRIPT_FONT	5	Stroked script font
SIMPLEX_FONT	6	Stroked triplex script font
TRIPLEX_SCR_FONT   	7	Stroked triplex script font
COMPLEX_FONT	8	Stroked complex font
EUROPEAN_FONT	9	Stroked European font
BOLD_FONT	10	Stroked bold font*/
