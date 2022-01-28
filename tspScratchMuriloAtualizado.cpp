#include <stdio.h> // print, fgets function
#include <stdlib.h> // exit, atoi function
#include <string.h> //strlen function
#include <math.h> // sqrt function
#include <algorithm>    // std::min
#include <limits.h> // INT_MAX
#include <time.h> //time(NULL) usado apra inicializar a semente aleatoria
#include <bits/stdc++.h>
using namespace std;

int calculateTourDistance(int *tour); //calculo da qualidade da solucao (fitness)
void tweak(int* tour, int i, int j); //modifica uma dada solucao (encontra uma solucao vizinha)
void readFile(const char **inputFile); //le o arquivo que foi passado como parametro e armazena os valores em distanceMatrix

int **distanceMatrix, size=-1, pos=0;

int main(const int argc, const char **inputFile){
    if(argc != 2){ //verifica se foi passado o nome do arquivo (o primeiro argumento em C e o nome do executavel)
		fprintf(stderr,"use: tspScratch <tsp file>\n\n");
		exit(1);
	}else
        readFile(inputFile);
    
////    Mostra a distanceMatrix
//     for(int i=0; i<size; i++){
//         for(int j=0; j<size; j++)
//             printf("%d ", distanceMatrix[i][j]);
//         printf("\n");
//     }
    
//    Cria um tour percorrendo as cidades em ordem e mostra o tamanho desse tour    
	int tour[size];
	for(int i=0; i<size; i++)
		tour[i]=i;
    printf("Tamanho %d\n", calculateTourDistance(tour));


//Busca gulosa
    //Fazer uma busca gulosa partindo da cidade 0, depois da 1, depois da 2 ...
    //Salvar melhor resultado encontrado nessa etapa
    
 void findMinRoute(vector<vector<int> > tsp) {
	
	int sum = 0;
    int counter = 0;
    int j = 0, i = 0;
    int min = INT_MAX;
    map<int, int> visitedRouteList;
 	
 	// Atravessar adjacencia
    // matrix tour[][]
    visitedRouteList[0] = 1;
    int route[tsp.size()];
    
    while (i < tour.size() && j < tour[i].size())
    {
 
        // Ponta da matriz
        if (counter >= tour[i].size() - 1)
        {
            break;
        }
 
        // Se o caminho nao e visitado e o custo e menor entao atualizar custo
        if (j != i && (visitedRouteList[j] == 0))
        {
            if (tour[i][j] < min)
            {
                min = tour[i][j];
                route[counter] = j + 1;
            }
        }
        j++;
 
        // Verificar todos os caminhos da inesima cidade indexada
        if (j == tour[i].size())
        {
            sum += min;
            min = INT_MAX;
            visitedRouteList[route[counter] - 1] = 1;
            j = 0;
            i = route[counter] - 1;
            counter++;
        }
    }
 
    // Atualizar a cidade do fim na lista da cidade visitada por ultimo
    i = route[counter - 1] - 1;
 
    for (j = 0; j < tour.size(); j++)
    {
 
        if ((i != j) && tour[i][j] < min)
        {
            min = tour[i][j];
            route[counter] = j + 1;
        }
    }
    sum += min;
 
    // Inicio no mesmo no em que terminou
    cout << ("Minimum Cost is : ");
    cout << (sum);
}
    
// 	Simulated Annealing
    //Usar a melhor solucao encontrada no estagio anterior como solucao inicial do Simulated Annealing
    //Implementar o Simulated annealing, com atencao ao detalhe de que aqui estamos tentando minimizar a distancia total, no algoritmo mostrado, estamos tentando maximizar a qualidade
	
	int i;
    
    vector<int>::iterator it,it2;
    TSP prob1;
    prob1.inputData();
    prob1.createOriginalDistanceGraph();
    numOfCities=prob1.numCities;
    int mini=INT_MAX;

    //Gerar a cidade inicial e tamanho do tour do vizinho mais próximo
    int bestTourLength=getNearestNeighbourTour(); //start with a decent point

    if(mini > bestTourLength ) mini=bestTourLength;
    double temperature,coolingRate=0.9,absoluteTemperature=0.00001,probability;
    int position1=0,position2=0;
    int newTourLength,difference;
    std::fstream fs;
    fs.open ("tspResultados.txt", std::fstream::in | std::fstream::out );
    for(int rs=0;rs<100;rs++)
    {
        temperature=99999999999999999999999999999999999999999.0; //Initial Temperature
        //temperature=DBL_MAX;
        fs<<"[";
        while(temperature > absoluteTemperature) 
        {   
            
            position1=int(getRandomNumber(0,numOfCities-1));
            position2=int(getRandomNumber(0,numOfCities-1));
            while(position1==position2 or( (position1>numOfCities-2) or (position2>numOfCities-2)))
            {
                position1=int(getRandomNumber(0,numOfCities-2));
                position2=int(getRandomNumber(0,numOfCities-2));
                
            }
            //cout<<"position1 e "<<position1<<" position2 e "<<position2<<"\n";
            swap2(position1,position2);
            it2=cities.begin();
            if(position2 > position1)
            random_shuffle(it2+position1,it2+position2);
            newTourLength=getTourLength();
            if(mini > newTourLength ) mini=newTourLength;
            fs<<newTourLength<<",";
            //cout<<"distancia do tour atual e "<<newTourLength<<" n bestTourLength e "<<bestTourLength<<"\n\n";
            difference=newTourLength-bestTourLength;
            
            if(difference <0 or (difference >0 and  getProbability(difference,temperature) > getRandomNumber(0,1)))
            {
                finalOrder.clear();
                
                for(it=cities.begin();it!=cities.end();it++)
                {
                    finalOrder.push_back(*it);
                }
                bestTourLength=difference+bestTourLength;
            }
            temperature=temperature*coolingRate;
            
        }
        fs<<"]\n";
        random_shuffle(cities.begin(),cities.end());
        //cout<<"the best solution is "<<bestTourLength<<"\n";
      }  
      fs.close();
    cout<<"A melhor solucao e "<<bestTourLength<<"\n";
    cout<<" A solucao minima encontrada e "<<mini<<"\n";
    return 0;
}
	
}

void tweak(int *tour, int i, int j){
    //Implementar
    
    //Gerar dois numeros aleatorios entre 0 e o numero de cidades, garantir que esses dois numeros sejam diferentes, eles serao indices digamos x e y
    //Trocar os valores que estao na posicao x e y do vetor tour
    
}

int calculateTourDistance(int *tour){ //calculo da qualidade da solucao (fitness)
	int dist=0;
	for(int i=0; i<size-1; i++){
		dist+=distanceMatrix[tour[i]][tour[i+1]];
	}
	dist+=distanceMatrix[tour[size-1]][tour[0]];
	return dist;
}

void readFile(const char **inputFile){ //le o arquivo que foi passado como parametro e armazena os valores em distanceMatrix
    
    double *x, *y;
	char type[10]="";
	
	char s[500];
	FILE *stream = fopen(inputFile[1], "r"); //read file (read-only permission)
	if( stream == NULL ){ // if the file was not read, error
		fprintf(stderr,"\nFail to Open tsp File!!\n");
		exit(1);
	}
	while(fgets(s,500,stream)){ //read every line (not larger than 500 chars) of the input
		if(strlen(s)-1>0) //remove the last break line of the line
			s[strlen(s)-1]='\0';
		if(('\r'==s[strlen(s)-1]))//in some files there is a carriage return at the end, don't know why. This command removes it
			s[strlen(s)-1]=0;
		
		char* value1 = strtok(s," "); //creating sub-strings separated by space
		char* value2 = strtok(NULL," ");
		char* value3 = strtok(NULL," ");
		
		if(!strcmp(value1, "EDGE_WEIGHT_TYPE")){ //verify if the instance is of type EUC_2D or ATT, only the calculation for this type was implemented
			if(strcmp(value3, "EUC_2D") && strcmp(value3, "ATT") && strcmp(value3, "CEIL_2D")){
				fprintf(stderr,"\nERROR! tsp file is not of type EUC_2D, ATT or CEIL_2D aborting!!\n");
				exit(1);
			}else
				strcpy(type,value3);
		}
		
		if(!strcmp(value1, "TYPE") && (strcmp(value3, "TSP")) ){ //verify if the instance is of type TSP, the other types will not be considered
			fprintf(stderr,"\nERROR! tsp file is not of type TSP, aborting!!\n");
			exit(1);
		}
		
		if(!strcmp(value1, "DIMENSION")){//read the dimension from the header and allocate memory for the cities
			size = atoi(value3);
			distanceMatrix=(int**)malloc(size * sizeof(int*));
			x=(double*)malloc(size * sizeof(double*));
			y=(double*)malloc(size * sizeof(double*));
			
			for (int i=0;i<size;i++)
				distanceMatrix[i] = (int*)malloc(size * sizeof(int));
		}
		
		if(atoi(value1)){//if the first substring is a number, the list of cities started
			if(size==-1){//if the size was not set, it was not in the header, error
				fprintf(stderr,"\nERROR! Dimension not set in file header!!\n");
				exit(1);
			}
			x[pos]=atof(value2);//storing the values from the file in the arrays
			y[pos]=atof(value3);
			pos++;
		}
	}
	
	if(!strcmp(type, "EUC_2D")){
		for(int i=0; i<size; i++){
			for(int j=0; j<size; j++){
				double xd = x[i]-x[j];
				double yd = y[i]-y[j];
				double dist=sqrt(xd*xd+yd*yd);
				distanceMatrix[i][j]=(int)(dist+0.5);//calculating the euclidean distance, rounding to int and storing in the distance matrix
			}
		}
	}else if(!strcmp(type, "CEIL_2D")){
		for(int i=0; i<size; i++){
			for(int j=0; j<size; j++){
				double xd = x[i]-x[j];
				double yd = y[i]-y[j];
				double dist=sqrt(xd*xd+yd*yd);
				distanceMatrix[i][j]=(int)(dist+0.000000001);//calculating the euclidean distance, rounding to int and storing in the distance matrix
			}
		}
	}else if(!strcmp(type, "ATT")){
		for(int i=0; i<size; i++){
			for(int j=0; j<size; j++){
				double xd = x[i]-x[j];
				double yd = y[i]-y[j];
				double rij=sqrt((xd*xd+yd*yd)/10.0);
				double tij=(int)(rij+0.5);
				if(tij<rij)
					distanceMatrix[i][j]=tij+1;
				else 
					distanceMatrix[i][j]=tij;
			}
		}
	}
}
