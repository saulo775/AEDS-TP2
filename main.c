#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

/* Tamanho máximo da string de entrada. */
#define MAX 250
#define TAM 20

int main() {

    int matrix[TAM][TAM] ;
    const char* filename = "/Users/saulovictor/Desktop/UFV/2022-02/AEDS-1/AEDS-TP2/entrada_3.txt";
    char *pt;
    double time_spent = 0.0;


    for (int i = 0; i < TAM; ++i) {
        for (int j = 0; j < TAM; ++j) {
            matrix[i][j] = 0;
        }
    }

    FILE *in_file = fopen(filename, "r");
    struct stat sb;
    stat(filename, &sb);


    int m = 0;
    char *file_contents = malloc(sb.st_size);
    while (fscanf(in_file, "%[^\n] ", file_contents) != EOF) {
        pt = strtok(file_contents, " ");
        printf("%s",pt);
        while(pt){
            pt = strtok(NULL, " ");
            if(pt != NULL){
                //printf("%s",pt);

                int x;
                sscanf(pt, "%d", &x);
                printf("%d", x);

                for(int k = 0; k < TAM; k++){
                    if (m==k){
                        matrix[m][k] = -1;
                    }else if (k==x){
                        matrix[m][k] = 1;
                    }
                }

            }
        }
        m++;
        printf("\n");
    }

    for (int j = 0; j < TAM; ++j) {
        for (int l = 0; l < TAM; ++l) {
            printf("%d ", matrix[j][l]);
        }
        printf("\n");
    }

    fclose(in_file);
    /* Nosso número na base n. Ele é um vetor
     * de n+1 posições representando um número
     * na base n.
     */
    int *num ;
    /* input é a string de entrada, e str
     * receberá cada permutação.
     */
    char input[MAX], str[MAX] ;
    int n, r, i, j, k ;

    printf("Entre com o conjunto inicial: ") ;
    scanf("%s", input) ;

    printf("Entre com o r: ") ;
    scanf("%d", &r) ;

    /* Aqui elimina-se caracteres repetidos na entrada.
     * Esse procedimento não faz parte do algoritmo, e
     * só é feito por questões práticas.
     */
    n = strlen(input) ;
    j = 0;
    str[0] = 0 ;
    for ( i = 0; i < n; i++ ) {
        if ( strchr(str, input[i]) == NULL ) {
            str[j] = input[i] ;
            j++ ;
            str[j] = 0 ;
        }
    }
    strcpy(input, str) ;
    n = strlen(input) ;

    /* Cria o nosso número. Ele é um vetor de
     * r+1 posições, sendo que a última é
     * reservada para indicar quando todos os
     * números de tamanho r foram gerados. */
    num = (int *) calloc( (r+1), sizeof(int)) ;
    if ( num == NULL ) {
        perror("calloc") ;
        return -1;
    }

    /* Termina quando a última posição do vetor
     * for 1. */
    clock_t begin = clock();
    while ( num[r] == 0 ) {
        for ( i = 0; i < n; i++ ) {
            /* processo de mapeamento. */
            for ( j = 0, k = r-1; j < r; j++ ) {
                str[k] = input[num[j]] ;
                k-- ;
            }
            /* Mostra o resultado. */
            str[r] = 0 ;
            if(str[0] != str[1]){
                printf("%s\n", str);
                int contante = 0;
                for (int l = 0; l < TAM; ++l) {
                    for (int z = 0; z < TAM; ++z) {
                        if (matrix[l][z] == 1){
                            if(str[l] == str[z]){
                                contante++;
                            }
                        }
                    }
                    if (contante>0){
                        break;
                    }
                    printf("\n");
                }
                if (contante == 0){
                    printf("solucao encontrada");
                }
            }
            /* incrementa o algarismo menos significativo. */
            num[0]++ ;
        }

        /* Muda de "casa" e lança os vai uns. */
        for ( i = 0; i < r; i++ ) {
            if ( num[i] == n ) {
                num[i] = 0 ;
                num[i+1]++ ;
            }
        }
    }
    clock_t end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    printf("time elapsed %f", time_spent);

    return 0 ;
}


/*
    for (int l = 0; l < TAM; ++l) {
        for (int c = 0; c < TAM; ++c) {
            if (matrix[l][c] == 1){
                int compare = strcmp(&str[0], &str[c]);
                if (compare == 1){
                    printf("deu ruim");
                }
            }
        }
    }
*/