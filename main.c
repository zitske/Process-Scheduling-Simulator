#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int id;
	int tempoChegada;
	int tempoExecucao;
	int turnaround;
	int tempoEspera;
} Processo;

int main(int argc, char *argv[]) {
	
	// Declaracao de variaveis
	int i, n, timeSlice, tempoAtual, processosKernel, processosUsuario;
	FILE *entrada, *saida;
	
	// Abertura de arquivos
	entrada = fopen(argv[1], "r");
	saida = fopen(argv[2], "w");
	
	// Verificacao de erro na abertura de arquivos
	if (entrada == NULL || saida == NULL){
		printf("Erro na abertura dos arquivos\n");
		return 0;
	}
	
	// Leitura da fatia de tempo do sistema
	fscanf(entrada, "%d", &timeSlice);
	
	// Leitura do numero de processos
	fscanf(entrada, "%d", &n);
	
	// Alocacao dinamica de memoria
	Processo *processos = (Processo *) malloc (n * sizeof(Processo));
	
	// Leitura dos processos
	for(i=0; i<n; i++){
		fscanf(entrada, "%d %d %d", &(processos[i].id), &(processos[i].tempoChegada), &(processos[i].tempoExecucao));
		processos[i].turnaround = 0;
		processos[i].tempoEspera = 0;
	}
	
	// Inicializacao de variaveis
	tempoAtual = 0;
	processosKernel = 0;
	processosUsuario = 0;
	
	// Enquanto existir processos para serem escalonados
	while(processosKernel + processosUsuario < n){
		
		// Verificacao se ha processos de kernel na fila de prontos
		if(processosKernel > 0){
			
			// Execucao dos processos de kernel
			for(i=0; i<n; i++){
				
				// Verificacao de processo de kernel
				if(processos[i].tempoChegada <= tempoAtual && processos[i].tempoExecucao != 0){
					
					// Execucao do processo
					if(processos[i].tempoExecucao > timeSlice){
						
						// Atualizacao do tempo de execucao do processo
						processos[i].tempoExecucao -= timeSlice;
						
						// Atualizacao do tempo de turnaround
						processos[i].turnaround += timeSlice;
						
						// Atualizacao do tempo de espera
						processos[i].tempoEspera += (tempoAtual - processos[i].tempoChegada);
						
						// Saida no arquivo
						fprintf(saida, "Tempo: %d\n", tempoAtual);
						fprintf(saida, "Fila: ");
						for(int j=0; j<n; j++){
							if(processos[j].tempoExecucao != 0){
								fprintf(saida, "%d ", processos[j].id);
							}
						}
						fprintf(saida, "\nProcesso em execucao: %d\n", processos[i].id);
						
						// Atualizacao do tempo
						tempoAtual += timeSlice;
						
						// Saida no arquivo
						fprintf(saida, "Processo %d voltou para fila de prontos\n\n", processos[i].id);
						
					} else {
						
						// Atualizacao do tempo de turnaround
						processos[i].turnaround += processos[i].tempoExecucao;
						
						// Atualizacao do tempo de espera
						processos[i].tempoEspera += (tempoAtual - processos[i].tempoChegada);
						
						// Saida no arquivo
						fprintf(saida, "Tempo: %d\n", tempoAtual);
						fprintf(saida, "Fila: ");
						for(int j=0; j<n; j++){
							if(processos[j].tempoExecucao != 0){
								fprintf(saida, "%d ", processos[j].id);
							}
						}
						fprintf(saida, "\nProcesso em execucao: %d\n", processos[i].id);
						
						// Atualizacao do tempo
						tempoAtual += processos[i].tempoExecucao;
						
						// Saida no arquivo
						fprintf(saida, "Processo %d finalizado\n\n", processos[i].id);
						
						// Atualizacao do tempo de execucao
						processos[i].tempoExecucao = 0;
						
						// Atualizacao do numero de processos de kernel
						processosKernel--;
						
					}
					
					// Parada do loop
					break;
					
				}
				
			}
			
		} else {
			
			// Execucao dos processos de usuario
			for(i=0; i<n; i++){
				
				// Verificacao de processo de usuario
				if(processos[i].tempoChegada <= tempoAtual && processos[i].tempoExecucao != 0 && processos[i].tempoChegada > 0){
					
					// Execucao do processo
					if(processos[i].tempoExecucao > timeSlice){
						
						// Atualizacao do tempo de execucao do processo
						processos[i].tempoExecucao -= timeSlice;
						
						// Atualizacao do tempo de turnaround
						processos[i].turnaround += timeSlice;
						
						// Atualizacao do tempo de espera
						processos[i].tempoEspera += (tempoAtual - processos[i].tempoChegada);
						
						// Saida no arquivo
						fprintf(saida, "Tempo: %d\n", tempoAtual);
						fprintf(saida, "Fila: ");
						for(int j=0; j<n; j++){
							if(processos[j].tempoExecucao != 0){
								fprintf(saida, "%d ", processos[j].id);
							}
						}
						fprintf(saida, "\nProcesso em execucao: %d\n", processos[i].id);
						
						// Atualizacao do tempo
						tempoAtual += timeSlice;
						
						// Saida no arquivo
						fprintf(saida, "Processo %d voltou para fila de prontos\n\n", processos[i].id);
						
					} else {
						
						// Atualizacao do tempo de turnaround
						processos[i].turnaround += processos[i].tempoExecucao;
						
						// Atualizacao do tempo de espera
						processos[i].tempoEspera += (tempoAtual - processos[i].tempoChegada);
						
						// Saida no arquivo
						fprintf(saida, "Tempo: %d\n", tempoAtual);
						fprintf(saida, "Fila: ");
						for(int j=0; j<n; j++){
							if(processos[j].tempoExecucao != 0){
								fprintf(saida, "%d ", processos[j].id);
							}
						}
						fprintf(saida, "\nProcesso em execucao: %d\n", processos[i].id);
						
						// Atualizacao do tempo
						tempoAtual += processos[i].tempoExecucao;
						
						// Saida no arquivo
						fprintf(saida, "Processo %d finalizado\n\n", processos[i].id);
						
						// Atualizacao do tempo de execucao
						processos[i].tempoExecucao = 0;
						
						// Atualizacao do numero de processos de usuario
						processosUsuario--;
						
					}
					
					// Parada do loop
					break;
					
				}
				
			}
			
		}
		
		// Atualizacao do numero de processos de kernel
		processosKernel = 0;
		
		// Atualizacao do numero de processos de usuario
		processosUsuario = 0;
		
		// Atualizacao do numero de processos de kernel e usuario
		for(i=0; i<n; i++){
			if(processos[i].tempoChegada <= tempoAtual && processos[i].tempoExecucao != 0 && processos[i].tempoChegada == 0){
				processosKernel++;
			} else if(processos[i].tempoChegada <= tempoAtual && processos[i].tempoExecucao != 0 && processos[i].tempoChegada > 0){
				processosUsuario++;
			}
		}
		
	}
	
	// Saida no arquivo
	fprintf(saida, "Turnaround dos processos:\n");
	
	// Calculo do turnaround
	for(i=0; i<n; i++){
		fprintf(saida, "Processo %d: %d\n", processos[i].id, processos[i].turnaround);
	}
	
	// Calculo do tempo medio de turnaround
	float turnaroundMedio = 0;
	for(i=0; i<n; i++){
		turnaroundMedio += processos[i].turnaround;
	}
	turnaroundMedio /= n;
	
	// Saida no arquivo
	fprintf(saida, "Tempo medio de turnaround: %.2f\n", turnaroundMedio);
	
	// Saida no arquivo
	fprintf(saida, "Tempo de espera dos processos:\n");
	
	// Calculo do tempo medio de espera
	float esperaMedio = 0;
	for(i=0; i<n; i++){
		fprintf(saida, "Processo %d: %d\n", processos[i].id, processos[i].tempoEspera);
		esperaMedio += processos[i].tempoEspera;
	}
	esperaMedio /= n;
	
	// Saida no arquivo
	fprintf(saida, "Tempo medio de espera: %.2f", esperaMedio);
	
	// Fechamento de arquivos
	fclose(entrada);
	fclose(saida);
	
	// Liberacao de memoria alocada
	free(processos);
	
	return 0;
	
}
