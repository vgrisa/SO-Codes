#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Variável global
int var_global = 0;

// Mutex para proteger o acesso à variável global
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *sensor(void *param) {
    int var_local = 0;

    while (true) {
        sleep(1);

        // Bloqueia o mutex para acessar a variável global
        pthread_mutex_lock(&mutex);

        // Verifica se a variável global atingiu 100
        if (var_global >= 100) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        // Incrementa a variável global
        var_global++;
        
        // Libera o mutex após atualizar a variável global
        pthread_mutex_unlock(&mutex);

        // Incrementa a variável local
        var_local++;

        // Imprime o valor da variável local e global
        printf("Thread %ld, Var Local: %d, Var Global: %d\n", (long)param, var_local, var_global);
    }

    return NULL;
}

int main() { 
    pthread_t th1, th2, th3;

    // Cria as threads
    pthread_create(&th1, NULL, sensor, (void*)1);
    pthread_create(&th2, NULL, sensor, (void*)2);
    pthread_create(&th3, NULL, sensor, (void*)3);

    // Espera todas as threads terminarem
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);

    printf("Valor final da variável global: %d\n", var_global);
    printf("Processo finalizado\n");

    return 0;
}
