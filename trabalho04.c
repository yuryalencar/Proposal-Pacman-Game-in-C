#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LINHAS 7
#define COLUNAS 11

char menu(){
	char opcao;

	printf("\n Menu:\n");
	printf("   8 - Cima:\n");
	printf("   2 - Baixo:\n");
	printf("   4 - Esquerda:\n");
	printf("   6 - Direita:\n");
	printf("   Digite uma opcao:");
	setbuf(stdin, NULL);
	scanf("%c", &opcao);
	
	return opcao;
}

void imprimir_matriz(char matriz [LINHAS][COLUNAS]) {

	int i, j;
	printf("     ## PAC-MAN ##\n\n");

	for (i = 0; i < LINHAS; i++) {
		for (j = 0; j < COLUNAS; j++) {
			printf("%c ", matriz[i][j]);
		}
		printf("\n");
	}

}

int calcular_resultado(char matriz[LINHAS][COLUNAS]) {
	int i, j, quantidade_alimento = 0;

	for (i = 0; i < LINHAS; i++) {
		for (j = 0; j < COLUNAS; j++) {
			if (matriz[i][j] == '#') {
				quantidade_alimento++;
			}
		}
	}

	return (LINHAS - quantidade_alimento);
}

void iniciar_matriz(char matriz [][COLUNAS], int posicao_pac [2]) {
	int i, j, posicao_item_linha, posicao_item_coluna;
	
	// inicializando toda a matriz com posicoes vazias
	for (i = 0; i < LINHAS; i++) {
		for (j = 0; j < COLUNAS; j++) {
			matriz[i][j] = '.';
		}
	}

	// definindo uma semente aleatoria e escolhendo a posicao do pacman
	srand(time(NULL));
	posicao_pac[0] = rand() % LINHAS;
	posicao_pac[1] = rand() % COLUNAS;
	matriz[posicao_pac[0]][posicao_pac[1]] = '0';

	// escolhendo locais vazios para inserir os demais itens
	for (i = 0; i < LINHAS; i++) {
		do {
			posicao_item_linha = rand() % LINHAS;
			posicao_item_coluna = rand() % COLUNAS;

			if (matriz[posicao_item_linha][posicao_item_coluna] == '.') {
				matriz[posicao_item_linha][posicao_item_coluna] = '#';
			}
		} while (matriz[posicao_item_linha][posicao_item_coluna] != '#');
	}

}

int movimentar_pac(char matriz[LINHAS][COLUNAS], char sentido, int posicao_pacman[2]) {
	// Variavel que vai definir se foi movimentado o pacman ou nao, sendo 1 para verdadeiro e 0 para falso
	int movimentou = 0;

    switch(sentido){
        case '8':
            if(posicao_pacman[0] > 0){
                matriz[posicao_pacman[0]][posicao_pacman[1]] = '.';
                posicao_pacman[0] = posicao_pacman[0] - 1;
                matriz[posicao_pacman[0]][posicao_pacman[1]] = '0';
				movimentou++;
            }
        break;
        case '4':
            if(posicao_pacman[1] > 0){
                matriz[posicao_pacman[0]][posicao_pacman[1]] = '.';
                posicao_pacman[1] = posicao_pacman[1] - 1;
                matriz[posicao_pacman[0]][posicao_pacman[1]] = '0';
				movimentou++;
			}
        break;
        case '2':
            if(posicao_pacman[0] < LINHAS-1){
                matriz[posicao_pacman[0]][posicao_pacman[1]] = '.';
                posicao_pacman[0] = posicao_pacman[0] + 1;
                matriz[posicao_pacman[0]][posicao_pacman[1]] = '0';
				movimentou++;
			}
        break;
        case '6':
            if(posicao_pacman[1] < COLUNAS-1){
                matriz[posicao_pacman[0]][posicao_pacman[1]] = '.';
                posicao_pacman[1] = posicao_pacman[1] + 1;
                matriz[posicao_pacman[0]][posicao_pacman[1]] = '0';
				movimentou++;
			}
        break;
    }
    
    return movimentou;
}

void main() {

	char opcao;
	char matriz[LINHAS][COLUNAS];
	int posicao_pac[2];
	int quantidade_restante_movimentos = floor((LINHAS * COLUNAS) / 2.0), alimentos_existentes = LINHAS;
	int quantidade_movimentos;

	iniciar_matriz(matriz, posicao_pac);
	
	do{
		system("cls");
		imprimir_matriz(matriz);
		opcao = menu();
		quantidade_restante_movimentos = quantidade_restante_movimentos - movimentar_pac(matriz, opcao, posicao_pac);
		alimentos_existentes = calcular_resultado(matriz);
	} while (quantidade_restante_movimentos != 0 && alimentos_existentes != LINHAS);

	system("cls");
	imprimir_matriz(matriz);
	if (alimentos_existentes == LINHAS) {
		quantidade_movimentos = floor((LINHAS * COLUNAS) / 2.0) - quantidade_restante_movimentos;
		printf("\nParabens voce venceu, com %d movimentos !\n", quantidade_movimentos);
	} else {
		printf("\nInfelizmente voce perdeu, acabaram seus movimentos !\n");
	}

	system("pause");
	getch();
}
