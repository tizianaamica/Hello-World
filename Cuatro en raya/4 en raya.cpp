#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include<windows.h>
#include<conio.h>
#include<string.h>

bool tablero(int matriz[8][8],int &turno,int vec[3],int ts[2],int vcg1[3],int vcg2[3],int l[2]);
void jugar(int matriz[8][8],int &turno,int j,int vector[8]);
void color(int x);
bool ganar(int matriz[8][8],int turno,int j,int vector[8],int vcg1[3],int vcg2[3]);
void empate3(int matriz[8][8],int turno,int j,int vector[8],int vec[3]);
void dados();
int opciones();
void instruc();
void creditos();


int main(){
	
	//printf("\n\n\t\t***CUATRO EN RAYA***\n\n");
	opciones();
	return 0;
}


bool tablero(int cubrir[8][8],int &turno, int vec[3],int ts[2],int vcg1[3],int vcg2[3],int l[2]){ //tablero y cursor
	
	int m[8][8];
	int i,j, i1=0, j1=0,vector[8], cnt[8], prt=0;
	char tecla;
	int cg1=1,cg2=1;
	bool band=true;
	int t=1,s=1;
	int dcg1=0,dcg2=0;
	
	for(i=0; i<8; i++){
		vector[i]=7;
		for(j=0; j<8; j++){
			cubrir[i][j]=0;
		}
	}
	
	for(i=0; i<8; i++){
		printf("\n\n");
			for(j=0; j<8; j++){
			  if(cubrir[i][j]!=0){
			  	if(cubrir[i][j]==1){
					color(13);//fichas
				}
				else{
					color(14);
				}	
			  	if(j==j1 && i==i1){
			  		printf("[%c]%c",3,186); //cursor
			  	 }
			  	 else{
			  	 	printf(" %c %c",3,186);
			  	   }
			  	   color(7);
			  }
			  else{
			  	if(j==j1 && i==i1){
			  		printf("[ ]%c",186); //cursor
			  	 }
			  	 else{
			  	 	printf("   %c",186);
			  	   }
			  }
			}
	}
	
	do{
		
		//system("pause");
		tecla=getch();
		switch(tolower(tecla)){
			
			case 'a': // izquierda 
				if(j1!=0){
					j1--;
				}
			break;
			
			case 'd': // derecha
				if(j1!=7){
					j1++;
				}
			break;
			
			case 32: //barra espacio
				if(turno%2==0){
					ts[0]=t++;
					cg1++;
				}
				else{
					ts[1]=s++;
					cg2++;
				} 
			
				jugar(cubrir,turno,j1,vector);
				band=ganar(cubrir,turno,j1,vector, vcg1, vcg2);
				empate3( cubrir,  turno,  j1,  vector, vec);
			break;
			default:
			break;
		}
		
		system("cls");
		int k1=0, k2=0, l[2];
		
		
		if(turno%2==0 || ts[1]==0){
				printf("\n\tTurno del jugador 1 ");
				printf("\n\tTurno numero : %d ",cg1);
				color(13); //rosado
				printf("%c",3);
				k1++;
		}else{
				
			printf("\n\tTurno del jugador 2 ");
			printf("\n\tTurno numero : %d ",cg2);
			color(14);//amarillo
			printf("%c",3);
			k2++;
		}
		if(turno%2==0){
			l[0]=k1++;
		}
		else{
			l[1]=k2++;
		}
		
		color(7);//negro
		
			
			for(i=0; i<8; i++){
				
				printf("\n\n");
				for(j=0; j<8; j++){
				if(cubrir[i][j]!=0){
				  	if(cubrir[i][j]==1){
						color(13);
					  }
					else{
						color(14);
					}	
				  	if(j==j1 && i==i1){
				  		printf("[%c]%c",3,186); //cursor
				  	 }
				  	 else{
				  	 	printf(" %c %c",3,186);
				  	   }
				  	   color(7);
				  }//fin if grande
				  else{
				  	if(j==j1 && i==i1){
				  		printf("[ ]%c",186); //cursor
				  	 }
				  	 else{
				  	 	printf("   %c",186);
				  	   }
				  }//fin else
				
				}//fin for
		
			}//fin for grande
	
	}while(band && turno!=64);
	return band;

}

void jugar(int matriz[8][8],int &turno,int j,int vector[8]){
	
	if(vector[j]!=-1){
	
		if(turno%2==0){ //jugador 1
			matriz[vector[j]][j]=1;
		}
		else{ //jugador 2
			matriz[vector[j]][j]=2;
		}
	
		vector[j]--;
		turno++;
	}
}

void color(int x){
	HANDLE hcon= GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon,x);
}

bool ganar(int matriz[8][8],int turno,int j,int vector[8],int vcg1[3],int vcg2[3]){
	
	int k=j,p=vector[j]+1 ,aux=0,cont[8],i,numerito=0,i2, vecg[3];
	int jug1=0, jug2=0, part=0;
	int xv=0,vx=0,hj=0;
	int ps,po;
	
	if(turno%2!=0){
		aux=1;
	}
	else{
		aux=2;
	}
	for(i=0;i<8;i++){
		cont[i]=0;
	}
	
	
	//derecha
	for(i=k;i<k+4;i++){
		if(i!=8){
			if(matriz[p][i]==aux){
				cont[numerito]++;
			}
		}
	}
	numerito++;

	//izquierda
	for(i=k;i>k-4;i--){
		if(i!=-1){
			if(matriz[p][i]==aux){
				cont[numerito]++;
			}
		}
	}
	numerito++;
	
	//abajo
	for(i=p;i<p+4;i++){
		if(i!=8){
			if(matriz[i][k]==aux){
				cont[numerito]++;
			}
		}
	}
	numerito++;
	//Arriba no existe
	
	//diagonal arriba izquierda
	for(i=p,i2=k;i>p-4;i--,i2--){
		if(i!=-1 && i2!=-1){
			if(matriz[i][i2]==aux){
				cont[numerito]++;
				
			}
		}
	}
	numerito++;
	
	//diagonal derecha bajando
		for(i=p,i2=k;i<p+4;i++,i2++){
			if(i!=8 && i2!=8){
				if(matriz[i][i2]==aux){
					cont[numerito]++;
				}
			}
		}
	numerito++;
	
	//diagonal arriba a la derecha
		for(i=p,i2=k;i>p-4;i--,i2++){
			if(i!=-1 && i2!=8){
				if(matriz[i][i2]==aux){
				cont[numerito]++;
				
				}
			}
		}
	numerito++;
	
	//diagonal abajo a la izquierda 
		for(i=p,i2=k;i<p+4;i++,i2--){
			if(i!=8 && i2!=-1){
				if(matriz[i][i2]==aux){
					cont[numerito]++;
				
				}
			}
		}
	numerito++;
	
	int ll=0,oo=0,pp=0;
		for(i=0;i<numerito;i++){
			if(turno%2==0){
				if(cont[i]==4)
				if(i==0||i==1)
				vcg1[0]++;
				else if(i==2)
				vcg1[1]++;
				else
				vcg1[2]++;
			}
			else{
				if(cont[i]==4)
				if(i==0||i==1)
				vcg2[0]++;
				else if(i==2)
				vcg2[1]++;
				else
				vcg2[2]++;
			}
		}
		
	/*system("pause");
	printf("\nPOSICIONES FICHAS FILAS %d COLUM %d ",p,k);
	system("pause");*/
	

	jug1=0;
	jug2=0;
	part=0;

	//Comprovar
	for(i=0;i<numerito;i++){
		part++;
		//printf("\n%d\tk=%d\tp=%d\n",cont[i],k,p);
			if(cont[i]==4 && aux==1){
			//	printf("\nGano jugador 1");
				jug1++;
			//	getch();
				return false;
			} 
			if(cont[i]==4 && aux==2){
			//	printf("\nGano jugador 2");
				jug2++;
			//	getch();
				return false;
			}
			if(cont[i]==4 && jug1==jug2){
					printf("\nEMPATE!");	
				//	tablero(matriz,turno ,vec);	
			}
	}
	//system("pause");
	return true;
	
}

void empate3(int matriz[8][8],int turno,int j,int vector[8],int vec[3]){
	
	int k=j,p=vector[j]+1 ,aux=0,cont[8],i,numerito=0,i2;
	int jug1=0, jug2=0, part=0;
	
	if(turno%2!=0){
		aux=1;
	}
	else{
		aux=2;
	}
	for(i=0;i<8;i++){
		cont[i]=0;
	}
	
	
	//derecha
	for(i=k;i<k+3;i++){
		if(i!=8){
			if(matriz[p][i]==aux){
				cont[numerito]++;
			}
		}
	}
	numerito++;
	
	//izquierda
	for(i=k;i>k-3;i--){
		if(i!=-1){
			if(matriz[p][i]==aux){
				cont[numerito]++;
			}
		}
	}
	numerito++;
	
	//abajo
	for(i=p;i<p+3;i++){
		if(i!=8){
			if(matriz[i][k]==aux){
				cont[numerito]++;
			}
		}
	}
	numerito++;
	//Arriba no existe
	
	//diagonal arriba izquierda
	for(i=p,i2=k;i>p-3;i--,i2--){
		if(i!=-1 && i2!=-1){
			if(matriz[i][i2]==aux){
				cont[numerito]++;
				
			}
		}
	}
	numerito++;
	
	//diagonal derecha bajando
		for(i=p,i2=k;i<p+3;i++,i2++){
			if(i!=8 && i2!=8){
				if(matriz[i][i2]==aux){
					cont[numerito]++;
					
				}
			}
		}
	numerito++;
	
	//diagonal arriba a la derecha
		for(i=p,i2=k;i>p-3;i--,i2++){
			if(i!=-1 && i2!=8){
				if(matriz[i][i2]==aux){
					cont[numerito]++;
				
				}
			}
		}
	numerito++;
	
	//diagonal abajo a la izquierda 
		for(i=p,i2=k;i<p+3;i++,i2--){
			if(i!=8 && i2!=-1){
				if(matriz[i][i2]==aux){
					cont[numerito]++;
				
				}
			}
		}
	numerito++;
	
		int o=0,pl=0,q=0;
		for(i=0;i<numerito;i++){
			
			if(cont[i]==3)
			if(i==0||i==1)
			vec[0]=pl++;
			else if(i==2)
			vec[1]=q++;
			else
			vec[2]=o++;
			
		}
	
	
}

void dados(){
	
	system("color 0f");
	int mp[8][8], cont1=0,cont2=0, prt=0,turno=0,i;
	bool band=true;
	char nombre1[20], nombre2[20],aux1[20],aux2[20];
	int dado1, dado2;
	int vec[3];
	int ts[2];
	int l[2];
	int vcg1[3],vcg2[3];
	float porc;
	int dado=2;
	int tata=0;
	
	srand(time(0));
	for(int m=0;m<4;m++){
		vcg1[m]=0;
		vcg2[m]=0;
	}
	for(int m=0;m<4;m++){
		vec[m]=0;
		vec[m]=0;
	}

	printf("\n\t\t****  CUATRO EN RAYA  ****    %c",3);
	printf("\n\nPara empezar a jugar, cada jugador deben ingresar un nombre\n");
	printf("\nSeguido de esto se lanzara un dado, el numero mayor sera quien empiza la partida\n");
	printf("\n\nNombre del primer jugador: ");
	fflush(stdin);
	gets(nombre1);
	printf("\nPresione alguna tecla para lanzar el dado\n");
	getch();
	dado1=rand()%6+1;
	printf("\nResultado DADO 1: %d\n\n",dado1);
	printf("\nNombre del segundo jugador: ");
	fflush(stdin);
	gets(nombre2);
	printf("\nPresione alguna tecla para lanzar el dado\n");
	getch();
	dado2=rand()%6+1;
	printf("\nResultado DADO 2: %d\n",dado2);
	dado++;
	
	while(dado1==dado2){
		system("cls");
		dado+=2;
		printf("\n\t **DADOS IGUALES**");
		printf("\nDeben volver a lanzar los dados");
		printf("\n\t %s Presiona alguna tecla para volver a lanzar el dado",nombre1);
		getch();
		dado1=rand()%6+1;
		printf("\nResultado DADO 1: %d",dado1);
		fflush(stdin);
		printf("\n\t %s Presiona alguna tecla para volver a lanzar el dado",nombre2);
		getch();
		dado2=rand()%6+1;
		printf("\nResultado DADO 2: %d",dado2);
	}
	
	
	if(dado1>dado2){
		printf("\n %s vas a ser el jugador 1",nombre1);
		printf("\n %s eres el jugador 2",nombre2);
	}
	else{
		printf("\n %s vas a ser el jugador 1",nombre2);
		printf("\n %s eres el jugador 2",nombre1);
		
	}
	
	getch();
	int partg=0;
	int partidas=5;
	
for(i=0; i<4; i++){
	
system("cls");	 
	partg++;
	
 
	band=tablero(mp,turno,vec,ts,vcg1,vcg2,l);
		
		
		//Ganadores, empate
		printf("\n\n\tFin de la partida numero #%d\n",i+1);
		if(band==false){
			if(dado1>dado2){
				strcpy(aux1,nombre1);
				strcpy(aux2,nombre2);
			}
			else{
				strcpy(aux1,nombre2);
				strcpy(aux2,nombre1);
			}
		
			if(turno%2!=0){
				printf("\nFelicitaciones %s Ganaste!",aux1);
				printf("ganaste en %d  turnos",ts[0]);
				cont1++;
				turno =0;
			}
			else{
				cont2++;
				printf("\nFelicitaciones %s Ganaste!",aux2);
				printf("\nGanaste en %d  turnos",ts[1]);
				turno = 1;
			}
			//nombres bien
			if(turno%2!=0 && cont1!=0){
				printf("\n%s inicia la proxima partida",aux2);
			}
			else{
				printf("\n%s inicia la proxima partida",aux1);
			}
		}
		
		
		else{
			tata++;
			printf("\nEmpate D:");
			printf("\nLa cantidad de 3 en lineas horizontales es: %d ",vec[0]);
			printf("\nLa cantidad de 3 en lineas verticales es: %d ",vec[1]);
			printf("\nLa cantidad de 3 en lineas diagonales es: %d ",vec[2]);
			prt++;
			printf("\nSe vuelven a lanzar los dados! ");
			dado+=2;
			printf("\n\t %s Presiona alguna tecla para volver a lanzar el DADO",nombre1);
			getch();
			dado1=rand()%6+1;
			printf("\nResultado DADO 1: %d",dado1);
			fflush(stdin);
			printf("\n\t %s Presiona alguna tecla para volver a lanzar el dado",nombre2);
			getch();
			dado2=rand()%6+1;
			printf("\nResultado DADO 2: %d",dado2);
			
				while(dado1==dado2){
					dado+=2;
					printf("\n\tDADOS iguales");
					printf("\n\t %s Presiona alguna tecla para volver a lanzar el DADO",nombre1);
					getch();
					dado1=rand()%6+1;
					printf("\nResultado DADO 1: %d",dado1);
					fflush(stdin);
					printf("\n\t %s Presiona alguna tecla para volver a lanzar el dado",nombre2);
					getch();
					dado2=rand()%6+1;
					printf("\nResultado DADO 2: %d",dado2);
				}
			 tablero(mp,turno,vec,ts,vcg1,vcg2,l);
			
		}
		getch();
		system("cls"); 
}

band=true;


while(band && (prt>=2 || (cont1==cont2) )){

		i++;
		band=tablero(mp,turno,vec,ts,vcg1,vcg2,l);
		system("cls");
		printf("\n\tFin de la partida numero #%d",i+1);
		
		if(!band){
			printf("\nEmpate D:");
			prt++;
		}else{
			if(turno%2==0){
				printf("Gano el jugador 1");
					//printf("utilizaste %d turnos",cg1);
				cont1++;
			}else{
				cont2++;
				printf("Gano el jugador 2");
					//printf("utilizaste %d turnos",cg2);
			}
		}
	//	int vecg;
		
}

	porc=(prt*100)/partg;
	//ESTADISTICAS
	
	system("cls");
	getch();
	system("color fd");
 	printf("\nEstadisticas del juego");
 	if(cont1==3)
 	printf("\nEL GANADOR es: %s ",aux1);
 	else
 	printf("\nEL GANADOR es: %s ",aux2);
 	
 	printf("\nPartidas jugadas %d",partg);
 	printf("\n\nPartidas ganadas por cada jugador: ");
 	if(cont1==3){
 		
		printf("\n%s gano %d partidas",aux1,cont1);
 		
 	} else{
 		printf("\n%s gano %d partidas",aux2,cont2);
 	}
 	
	
 	if(cont1==3){
 		printf("\nGanador indiscutible: %s",aux1);
 	}
 	else {
 		printf("\nGanador indiscutible: %s",aux2);
 	}
 	
 	printf("\nPartidas empatadas: %d",prt);
 	if(porc!=0 && cont1>=3){
 		printf("\nPorcentaje de partidas empatadas: %.2f %",porc);
 	}
 	if(porc==0){
 		printf("\nNo hubo partidas empatadas");
 	}
 	
 	if(cont1>=3){
 		printf("\nJugadas de %s",aux2);
	 	printf("\nVeces ganas de manera vertical: %d",vcg1[1]);
	 	printf("\nVeces ganas de manera horizontal: %d",vcg1[0]);
	 	printf("\nVeces ganas de manera diagonal: %d",vcg1[2]);
 	}
 	else{
 		printf("\nJugadas de %s",aux1);
	 	printf("\nVeces ganas de manera vertical: %d",vcg2[1]);
	 	printf("\nVeces ganas de manera horizontal: %d",vcg2[0]);
	 	printf("\nVeces ganas de manera diagonal: %d",vcg2[2]);
	}
	
	printf("\nNumero de lanzamiento de dado: %d",dado);
	if(dado1>dado2 && tata!=0){
		printf("\nLanzados en el juego, en la partida #%d de %s",tata,nombre1);
	}
	else{
		printf("\nLanzados en el juego, en la partida #%d por %s",tata,nombre2);
	}
	

}

int opciones(){
	
	int opcion, matriz[8][8], opci, cont=0;
		int cg1=0,cg2=0;
	do{
		
		system("color f9");
		printf("\n\t\t****CUATRO EN RAYA****");
		printf("\n\n\tSeleccione una opcion para empezar:  %c\n",3);
		printf("\n\t\t 1) Jugar");
		printf("\n\t\t 2) Instrucciones");
		printf("\n\t\t 3) Creditos");
		printf("\n\t\t 4) Salir\n");
		scanf("%d",&opcion);
		
		if(opcion <0 || opcion >5){
			printf("\nIngrese una opccion indicada");
			scanf("%d",&opcion);
		}
	}while(opcion <=0 || opcion>=5);
	system("cls");
	
	if(opcion==1){
			dados();
	}
	
	if(opcion==2){
		system("cls");
		instruc();
		
	}
	if(opcion==3){
		system("cls");
		creditos( );
	}
	
	if(opcion==4){
		system("cls");
		return 0;
	}

}

void instruc(){
	
	int res, salir, tecla,cont;
	system("color f9");
	printf("\n\t\tInstrucciones de Juego");
	printf("\nEl juego consiste en conectar cuatro fichas en raya,");
	printf("\nLa raya puede ser horizontal, vertical o diagonal.");
	printf("\nSon cuatro partidas por jugada, en caso de empate,");
	printf("\nSe decidira el ganador con una partida de desempate,");
	printf("\nLa cual continuara hasta que exista un ganador indiscutible\n\n");
	printf("\n\t\t\tComandos del juego\n");
	printf("\n\tPara mover el cursor deben utilizar: ");
	printf("\n\t'A' Para ir a la izquierda");
	printf("\n\t'D' Para ir a la derecha");
	printf("\nPara soltar una ficha se pulsar 'la barra espaciadora'\n");
	printf("\nPara iniciar el juego, cada participante debe ingresar su nombre");
	printf("\nSeguido de esto se hara un lanzamiento de dados");
	printf("\nPara decidir que jugador empienza la primera partida");
	printf("\nEn caso de que exista un empate en la partida, se volveran a lanzar los dados");
	printf("\nPara decidir quien empieza la proxima partida\n");
	printf("\n\t\t\tCuando gana un jugador?");
	printf("\nCuando realiza 4 fichas horizontales, verticales o diagonales\n\n");
	printf("\n\t\tCuando pierden?");
	printf("\nCuando ningun jugador logra conectar 4 fichas");
	printf("\nEn caso de no conectar 4 fichas se considera empate");
	printf("\nSi esto ocurre, se realizara una partida extra para el desempate\n");
	
	printf("\nSi desea salir, presione cualquier tecla");
	printf("\nSi desea volver al menu presione 't': ");
	tecla=getch();
	if(tecla=='t'){
		
		system("pause");
		system("cls");
		opciones(  );
	}

}

void creditos(){
	
	int tecla,cont;
	int p=30;
	
	while(p>0){
		
		for(int i=0;i<p;i++){
			printf("\n");
			
			
		}
		p--;
			system("color fd");
		printf("\n\t\t****CUATRO EN RAYA****");
		printf("\n\nJuego realizado por:");
		printf("\n\n\tTiziana Amicarella Girardi %c",3);
		printf("\n\nEstudiante de Ing. Informatica UNET\n");

	
		Sleep(200);
		system("cls");
	}
			system("color fd");
		printf("\n\t\t****CUATRO EN RAYA****");
		printf("\n\nJuego realizado por:");
		printf("\n\n\tTiziana Amicarella Girardi %c",3);
		printf("\n\nEstudiante de Ing. Informatica UNET\n");

	printf("\nSi desea salir, presione cualquier tecla");	
	printf("\n\nPresione 't' para volver al menu principal: ");
	tecla=getch();
	if(tecla=='t'){
		
		system("pause");
		system("cls");
		opciones();
	}

}

