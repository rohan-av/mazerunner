#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
class Tile;
class Maze;
char popdir(int loc1y, int loc1x, int loc2y, int loc2x);

class Tile {
	
	private:
		
		bool path;
		bool up;
		bool left;
		bool right;
		bool down;
		int loc[2];
		
	
	public:
		
		Tile(){};
		Tile(int y, int x, bool p = true){
			loc[0]=y;
			loc[1]=x;
			path=p;
			if (path){
				this->up=true;
				this->left=true;
				this->right=true;
				this->down=true;
			}
		}
		
		bool getpath(){
			return path;
		}
		
		bool updatepath(bool p2){
			this->path=p2;
		}
		
		bool getup(){
			return up;
		}
		bool getleft(){
			return left;
		}
		bool getright(){
			return right;
		}
		bool getdown(){
			return down;
		}
		
		void upup(){
			this->up=false;
		}
		void upleft(){
			this->left=false;
		}
		void upright(){
			this->right=false;
		}
		void updown(){
			this->down=false;
		}
		
		int gety(){
			return loc[0];
		}
		
		int getx(){
			return loc[1];
		}
			
};

class Maze {
	
	private:
		
		Tile m[8][8];
		
	public:
		
		Maze(void){
			
			for (int i=0;i<8;i++){ //initializing maze tiles 01367
				for (int j=0;j<8;j++){
					m[i][j] = Tile(i,j,true);
				}
			}
			m[0][0].updatepath(false);
			m[0][1].updatepath(false);
			m[0][3].updatepath(false);
			m[0][6].updatepath(false);
			m[0][7].updatepath(false);
			m[1][0].updatepath(false);
			m[1][1].updatepath(false);
			m[1][5].updatepath(false);
			m[2][2].updatepath(false);
			m[2][4].updatepath(false);
			m[2][5].updatepath(false);
			m[2][7].updatepath(false);
			m[3][0].updatepath(false);
			m[3][5].updatepath(false);
			m[3][7].updatepath(false);
			m[4][0].updatepath(false);
			m[4][1].updatepath(false);
			m[4][2].updatepath(false);
			m[4][3].updatepath(false);
			m[4][7].updatepath(false);
			m[5][5].updatepath(false);
			m[6][0].updatepath(false);
			m[6][1].updatepath(false);
			m[6][3].updatepath(false);
			m[6][5].updatepath(false);
			m[6][6].updatepath(false);
			m[6][7].updatepath(false);
			m[7][0].updatepath(false);
			m[7][3].updatepath(false);
			m[7][5].updatepath(false);
			m[7][6].updatepath(false);
			m[7][7].updatepath(false);
			
			for (int i=0;i<8;i++){ //updating possible locations at each tile
				for (int j=0;j<8;j++){
					if (i==0 || m[i-1][j].getpath()==false){ // short-circuiting employed
						m[i][j].upup();
					}
					if (j==0 || m[i][j-1].getpath()==false){
						m[i][j].upleft();
					}
					if (j==7 || m[i][j+1].getpath()==false){
						m[i][j].upright();
					}
					if (i==7 || m[i+1][j].getpath()==false){
						m[i][j].updown();
					}
				}
			}
		}
		
		Tile gettile(int y, int x){
			return m[y][x];
		}
		
		void updateup(int y, int x){
			m[y][x].upup();
		}
		void updateleft(int y, int x){
			m[y][x].upleft();
		}		
		void updateright(int y, int x){
			m[y][x].upright();
		}		
		void updatedown(int y, int x){
			m[y][x].updown();
		}						
};

int main(void) {
	Maze M;
	vector<Tile> Path;
	bool done = false;
	char PrevDir='E';
	Tile end=M.gettile(2,0);
	Path.push_back(M.gettile(7,1));
	while (!Path.empty() && !done){
		Tile CurSqr=Path.back();
		
		int locx=CurSqr.getx();
		int locy=CurSqr.gety();
		/*cout << locy << locx <<endl;
		cout << CurSqr.getup()<<CurSqr.getleft()<<CurSqr.getright()<<CurSqr.getdown()<<endl;*/
		char NewDir;
		while (true){
			if (CurSqr.getup() /*&& PrevDir!='D'*/){
				NewDir='U';
				break;
			} if (CurSqr.getleft() /*&& PrevDir!='R'*/){
				NewDir='L';
				break;
			} if (CurSqr.getright() /*&& PrevDir!='L'*/){
				NewDir='R';
				break;
			} if (CurSqr.getdown() /*&& PrevDir!='U'*/){
				NewDir='D';
				break;
			} 
			NewDir='X';
			break;
		}
		//cout << NewDir<<endl;
		if (NewDir=='X'){
			Path.pop_back();
			int loc2x=(Path.back()).getx();
			int loc2y=(Path.back()).gety();
			PrevDir=popdir(locy,locx,loc2y,loc2x);
			//cout << "block!"<<endl;
			if (PrevDir=='U'){
				M.updatedown(loc2y,loc2x);
			} else if (PrevDir=='D'){
				M.updateup(loc2y,loc2x);
			} else if (PrevDir=='L'){
				M.updateright(loc2y,loc2x);
			} else if (PrevDir=='R'){
				M.updateleft(loc2y,loc2x);
			}		
		}
		else {
			if (NewDir=='U'){
				(Path.back()).upup();
				M.updateup(locy,locx);
				M.updatedown(locy-1,locx);
				Path.push_back(M.gettile(locy-1,locx));
				PrevDir='U';
				if (locy-1==5 && locx==7){
					done=true;
				}
			}
			else if (NewDir=='L'){
				(Path.back()).upleft();
				M.updateleft(locy,locx);
				M.updateright(locy,locx-1);
				Path.push_back(M.gettile(locy,locx-1));
				PrevDir='L';
				if (locy==5 && locx-1==7){
					done=true;
				}
			}
			else if (NewDir=='R'){
				(Path.back()).upright();
				M.updateright(locy,locx);
				M.updateleft(locy,locx+1);
				Path.push_back(M.gettile(locy,locx+1));
				PrevDir='R';
				if (locy==5 && locx+1==7){
					done=true;
				}
			}
			else if (NewDir=='D'){
				(Path.back()).updown();
				M.updatedown(locy,locx);
				M.updateup(locy+1,locx);
				Path.push_back(M.gettile(locy+1,locx));
				PrevDir='D';
				if (locy+1==5 && locx==7){
					done=true;
				}
			}
		}	
	}
	cout<<"maze solved!"<<endl;
	for(Tile a: Path){
		cout<<"("<<a.gety()<<", "<<a.getx()<<")"<<endl;
	}
	return 0;
}

char popdir(int loc1y, int loc1x, int loc2y, int loc2x){
	if (loc1y==loc2y){
		if (loc1x-loc2x==1){
			return 'L';
		} else {
			return 'R';
		}
	} else {
		if (loc1y-loc2y==1){
			return 'U';
		} else {
			return 'D';
		}
	}
}
