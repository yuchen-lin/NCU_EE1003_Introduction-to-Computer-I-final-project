#include <conio.h>
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

char map[100][100] = {
	"############################",
	"#............##............#",
	"#.####.#####.##.#####.####.#",
	"#.####.#####.##.#####.####.#",
	"#..........................#",
	"#.####.##.########.##.####.#",
	"#......##....##....##......#",
	"######.#####.##.#####.######",
	"     #.##          ##.#     ",
	"     #.## ###  ### ##.#     ",
	"######.## #      # ##.######",
	"      .   #      #   .      ",
	"######.## #      # ##.######",
	"     #.## ######## ##.#     ",
	"     #.##    C     ##.#     ",
	"######.## ######## ##.######",
	"#............##............#",
	"#.####.#####.##.#####.####.#",
	"#...##................##...#",
	"###.##.##.########.##.##.###",
	"#......##....##....##......#",
	"#.##########.##.##########.#",
	"#..........................#",
	"############################"	//23
};

double speed = 150;
int score = 0;
int x = 13;
int y = 14;

bool gameover = false;
bool win = false;
int mNum = 1;
int mx[10000], my[10000];
int md[10000];
int mc[10000];

int R = 0;
int mdc[5] = {0,0,0,0};//monster direction choise
char save[10000];

int Odirection = 100;
int Ndirection = 100;
bool skip = false;

void SetColor(int f=7,int b=0)
{
    unsigned short ForeColor=f+16*b;
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon,ForeColor);
}

HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord;

void locate(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(hout,coord);
};

void hide()
{
    CONSOLE_CURSOR_INFO cursor_info={1,0};
    SetConsoleCursorInfo(hout, &cursor_info);
}
//遊戲結束
bool finish = false;
int gameOver(){
	for(int i = 0; i < mNum; i++){
		if(x == mx[i] && y == my[i]){
			finish = true;
		}
	}
	if(finish == true)	return 1;
	else return 0;
}
void gC(){
	if(gameOver()){
	gameover = true;
	} else if(score == 216){
		gameover = true;
	    win = true;
	}
}
void makeMonster(){
	for(int i = 0; i < mNum; i++){
		mx[i] = 13;
		my[i] = 11;
		md[i] = 8;
		mc[i] = 0;
		save[i] = ' ';
	}
}
//怪物----------------------------------------------------------------- 
void mW(){
	
	for(int i = 0; i < mNum; i++){
		if(map[my[i]][mx[i]-1] != '#'){
			if(md[i] != 6){
			mdc[mc[i]] = 4;
			mc[i]++;
			}
		}
		if(map[my[i]-1][mx[i]] != '#'){
			if(md[i] != 2){
			mdc[mc[i]] = 8;
			mc[i]++;
			}
		}
		if(map[my[i]][mx[i]+1] != '#'){
			if(md[i] != 4){
			mdc[mc[i]] = 6;
			mc[i]++;
			}
		}
		if(map[my[i]+1][mx[i]] != '#'){
			if(md[i] != 8){
			mdc[mc[i]] = 2;
			mc[i]++;
			}
		}
		R = rand()%mc[i];
		md[i] = mdc[R];
		mc[i] = 0;
		
		if(md[i] == 4){
		if(mx[i] == 0 && my[i] == 11){
			locate(0,11);
			cout<<" ";
			locate(27,11);
			SetColor(2,0);
			cout<<"M";
			SetColor();
			mx[i] = 27;
		}
		locate(mx[i],my[i]);
		cout<<save[i];
		save[i] = map[my[i]][mx[i]-1];
		mx[i]--;
		locate(mx[i],my[i]);
		SetColor(2,0);
		cout<<"M";
		SetColor();
		} else if(md[i] == 8){
			locate(mx[i],my[i]);
			cout<<save[i];
			save[i] = map[my[i]-1][mx[i]];
			my[i]--;
			locate(mx[i],my[i]);
			SetColor(2,0);
			cout<<"M";
			SetColor();
		} else if(md[i] == 6){
			if(mx[i] == 27 && my[i] == 11){
				locate(0,11);
				SetColor(2,0);
				cout<<"M";
				SetColor();
				locate(27,11);
				cout<<" ";
				mx[i] = 0;
			}
			locate(mx[i],my[i]);
			cout<<save[i];
			save[i] = map[my[i]][mx[i]+1];
			mx[i]++;
			locate(mx[i],my[i]);
			SetColor(2,0);
			cout<<"M";
			SetColor();
		} else if(md[i] == 2){
			locate(mx[i],my[i]);
			cout<<save[i];
			save[i] = map[my[i]+1][mx[i]];
			my[i]++;
			locate(mx[i],my[i]);
			SetColor(2,0);
			cout<<"M";
			SetColor();
		}
	}
	
	gC();
}
//---------------------------------------------------------------------- 
void findDirection1(){
	if(Ndirection == 1){
		if(map[y-1][x] != '#'){
			Odirection = 1;
			skip = true;
		}
	}
}

void findDirection2(){
	if(Ndirection == 2){
		if(map[y+1][x] != '#'){
			Odirection = 2;
			skip = true;
		}
	}
}

void findDirection3(){
	if(Ndirection == 3){
		if(map[y][x-1] != '#'){
			Odirection = 3;
			skip = true;
		}
	}
}

void findDirection4(){
	if(Ndirection == 4){
		if(map[y][x+1] != '#'){
			Odirection = 4;
			skip = true;
		}
	}
}

void portalL(){
	if(x == 0 && y == 11){
		x = 27;
		locate(0,11);
		cout<<" ";
		locate(27,11);
		cout<<"C";
	}
}
void portalR(){
	if(x == 27 && y == 11){
		x = 0;
		locate(27,11);
		cout<<" ";
		locate(0,11);
		cout<<"C";
	}
}

//Continue up----------------------------------------------------------------------------------------------------
void runUp(){
	while(1){
		if(gameover){
				locate(0,25);
				break;
			}
		gC();
		findDirection2();
		findDirection3();
		findDirection4();
		if(skip){
			skip = false;
			break;
		}
		if(map[y-1][x] != '#'){
			mW();
			if(map[y-1][x] == '.'){
           		score++;
           		locate(7, 24);
           		cout<<score;
			}
           	map[y][x] = ' ';
           	locate(x,y);
           	cout<<" ";
           	map[y-1][x] = 'C';
           	locate(x,y-1);
           	SetColor(6,0);
			cout<<"C";
			SetColor(7,0);
           	y--;
           		
		} else if(map[y-1][x] == '#') {
			mW();
			Sleep(speed);
			break;
		}

		Sleep(speed);
		if(kbhit()){
			break;
		}
	}
}
//Continue down----------------------------------------------------------------------------------------------------
void runDown(){
	while(1){
		if(gameover){
				locate(0,25);
				break;
			}
		gC();
		findDirection1();
		findDirection3();
		findDirection4();
		if(skip){
			skip = false;
			break;
		}
		if(map[y+1][x] != '#'){
			mW();
			if(map[y+1][x] == '.'){
           		score++;
           		locate(7, 24);
           		cout<<score;
			}	
           	map[y][x] = ' ';
           	locate(x,y);
           	cout<<" ";
           	map[y+1][x] = 'C';
           	locate(x,y+1);
           	SetColor(6,0);
			cout<<"C";
			SetColor(7,0);
           	y++;
           	
		} else if(map[y+1][x] == '#') {
			mW();
			Sleep(speed);
			break;
		}

		Sleep(speed);
		if(kbhit()){
			break;
		}
	}
}
//Continue left----------------------------------------------------------------------------------------------------
void runLeft(){
	while(1){
		if(gameover){
				locate(0,25);
				break;
			}
		gC();
		findDirection1();
		findDirection2();
		findDirection4();
		portalL();

		if(skip){
			skip = false;
			break;
		}
		if(map[y][x-1] != '#'){
			mW();
			if(map[y][x-1] == '.'){
           		score++;
           		locate(7, 24);
           		cout<<score;
			}
           	map[y][x] = ' ';
           	locate(x,y);
           	cout<<" ";
           	map[y][x-1] = 'C';
           	locate(x-1,y);
           	SetColor(6,0);
			cout<<"C";
			SetColor(7,0);
           	x--;
           		
		} else if(map[y][x-1] == '#') {
			mW();
			Sleep(speed);
			break;
		}

		Sleep(speed);
		if(kbhit()){
			break;
		}
	}
}
//Continue right----------------------------------------------------------------------------------------------------
void runRight(){
	while(1){
		if(gameover){
				locate(0,25);
				break;
			}
		gC();
		findDirection2();
		findDirection3();
		findDirection1();

		portalR();
		if(skip){
			skip = false;
			break;
		}
		if(map[y][x+1] != '#'){
			mW();
			if(map[y][x+1] == '.'){
           			score++;
           			locate(7, 24);
           			cout<<score;
			}
           	map[y][x] = ' ';
           	locate(x,y);
           	cout<<" ";
           	map[y][x+1] = 'C';
           	locate(x+1,y);
           	SetColor(6,0);
			cout<<"C";
			SetColor(7,0);
           	x++;
           	
		} else if(map[y][x+1] == '#') {
			mW();
			Sleep(speed);
			break;
		}

		Sleep(speed);
		if(kbhit()){
			break;
		}
	}
}
//Main************************************************************************************************************
int main(){
	bool start = false;
	int c;
	hide();
	cout<<"    <小精靈>"<<endl;
	cout<<endl;
	SetColor(2,0);
	cout<<"  ->開始遊戲<-"<<endl;
	SetColor(7,0);
	cout<<"    設定怪物生成數量"<<endl;
	cout<<endl;
	cout<<endl<<endl;
	cout<<"說明:"<<endl;
	cout<<"使用上下鍵選擇，Enter鍵執行";
	int menu = 1;
	bool back = false;
	while(1){
		locate(0,7);
		SetColor();
		cout<<"說明:"<<endl;
		cout<<"使用上下鍵選擇，Enter鍵執行    "<<endl;
		cout<<"                              ";
		c=getch();
		if(c==224){
        	c=getch();
        	switch(c){
            	case 72://up
            		if(menu != 1){
            			menu--;
					}
            		break;
           		case 80://down
				    if(menu != 2){
				    	menu++;
					}
            		break;
       		}
   		} else if(c == 13 && menu == 1){//選項一+ENTER 
   			break;
		} else if(c == 13 && menu == 2){//選項二+ENTER 
			locate(0,5);
			SetColor(2,0);
			cout<<"    怪物數量: "<<mNum;
			locate(0,8);
			SetColor();
			cout<<"使用上鍵增加、下鍵減少怪物數量"<<endl;
			cout<<"按Enter返回"; 
			while(1){
				if(back == true)	break;
				c=getch();
        		switch(c){
            		case 72://up
            			mNum++;
            			locate(0,5);
            			SetColor(2,0);
            			cout<<"    怪物數量: "<<mNum;
            			break;
           			case 80://down
           				if(mNum > 0){
           					mNum--;
					    	locate(0,5);
					    	SetColor(2,0);
            				cout<<"    怪物數量: "<<mNum<<" ";
						}
						break;
            		case 13:
            			back = true;
            			break;
       			}
			}
		if(back == true){
			back = false;
			locate(0,5);
			cout<<"                            ";
			continue;
		}
		}
   		switch(menu){
   				case 1:
   					SetColor(2,0);
   					locate(0,2);
   					cout<<"  ->開始遊戲<-          ";
   					SetColor(7,0);
   					locate(0,3);
   					cout<<"    設定怪物生成數量                         ";
   					continue;
   				case 2:
   					SetColor(2,0);
   					locate(0,3);
   					cout<<"  ->設定怪物生成數量<-";
   					SetColor(7,0);
   					locate(0,2);
   					cout<<"    開始遊戲          ";
   					
   					continue;
		   }
	}
    system("cls");
    makeMonster();
	for(int i = 0; i<24; i++){
   		for(int j = 0; j<28; j++){
   			cout<<map[i][j];
			}
		cout<<endl;
	}
	locate(12,11);
	SetColor(2,0);
	cout<<"M ";
	SetColor();
	cout<<"x "<<mNum;
	locate(0,24);
	cout<<"Score: "<<score;
	locate(13,14);
	SetColor(6,0);
	cout<<"C";
	SetColor(7,0);
	
	c=getch();
	if(c==224){
        	c=getch();
        	switch(c){
            	case 72://up
            		Odirection = 1;
            		break;
           		case 80://down
				    Odirection = 2;
            		break;
           		case 75://left
				    Odirection = 3;
            		break;
           		case 77://right
				    Odirection = 4;
            		break;
       		}
   	}
   	locate(12,11);
   	cout<<"     #  ";
	while(1){
		while(!kbhit()){
			if(gameover){
				if(win==false){
					locate(x,y);
				SetColor(4,0);
				cout<<"X";
				locate(8,11);
				SetColor(4,0);
				cout<<"<Game Over!>";
				locate(0,25);
				break;
				}
			else{
				locate(9,11);
				SetColor(6,0);
				cout<<"<Victory!>";
				}
			}
			switch(Odirection){
				case 1:
					runUp();
					break;
				case 2:
					runDown();
					break;
				case 3:
					runLeft();
					break;
				case 4:
					runRight();
					break;
			}
    	}
    	c=getch();
       	if(c==224){
        	c=getch();
        	switch(c){
            	case 72://up
            		Ndirection = 1;
            		break;
           		case 80://down
				    Ndirection = 2;
            		break;
           		case 75://left
				    Ndirection = 3;
            		break;
           		case 77://right
				    Ndirection = 4;
            		break;
       		}
   		}
	}
    system("pause");
    return 0;
}

