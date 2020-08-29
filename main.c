/***********************  
 Apuntadores a funciones
 Trabaje con Daniel Roa y Atonio Junco
 Luis Ortiz Revilla - A01022320
 **************************/ 
#include <stdio.h>
#include <stdlib.h>

#define I 10
#define L 3

typedef struct
{
  char * titulo;
  int paginas;
} Libro;

typedef void (*print)(void *);
typedef void (*t_recorre)(void *, size_t, size_t, print);

void *begin(void *vector){
  return vector;
}

void *end(void *vector, size_t count, size_t size){
  return vector + ((count * size) - size);
}

void *next(void *vector, void *current, size_t count, size_t size){
  void * next = current + size;
  void * final = end(vector, count, size);
  if(next > final) {
    return NULL;
  }
  return next;
}

void *prev(void *vector, void *current, size_t count, size_t size){
  void * prev = current - size;
  void * start = begin(vector);
  if(prev < start) {
    return NULL;
  }
  return prev;
}

void forward(void *vector, size_t count, size_t size, print a)
{      
  void * current = begin(vector);  
  
  while (current != NULL)
  {
      (*a)(current);
      current = next(vector, current, count, size);
  }
  
}

void backwards(void *vector, size_t count, size_t size, print a)  
{
  void * current = end(vector, count, size);  
  
  while (current != NULL)
  {
      (*a)(current);
      current = prev(vector, current, count, size);
  }
  
}

void bidirectional(void *vector, size_t count, size_t size, print a)
{
    forward(vector, count, size, a);
    backwards(vector, count, size, a);
}

void imprimeInt(int * vector)
{
    printf(" %d ", *vector);
}

void imprimeLibro(Libro * vector)
{
    printf("Titulo: %s \t", vector-> titulo);
    printf("Pagina: %d |||||||||||", vector -> paginas);
}

void recorre(t_recorre algorithm, void * vector, size_t count, size_t size, print a){
  (*algorithm)(vector, count, size, a);
}

int main (int arc, const char * argv[])
{
    int * vector = (int *) malloc(I * sizeof(int));

    int * aux = vector;
    int * last = vector + I;

    for (; aux < last; ++aux) 
    {
      *aux = rand() % 100;
      printf("%d\t", *aux);
    }

    printf("\n");
    printf("\n");
    printf("Forward................\n");
    recorre(&forward, vector, I, sizeof(*vector), &imprimeInt);
    printf("\n");
    printf("Backwards................\n");
    recorre(&backwards, vector, I, sizeof(*vector), &imprimeInt);
    printf("\n");
    printf("Bidirectional................\n");
    recorre(&bidirectional, vector, I, sizeof(*vector), &imprimeInt);

   Libro * tomo = (Libro *)malloc(sizeof(Libro) * L);
    Libro * aux2 = tomo;
    Libro * fin = tomo + L;

    

   for (Libro * aux2 = tomo; aux2 < fin; ++aux2)
   {
       aux2->titulo = (char *)malloc(sizeof(char) * 20);
       printf("\nNombre del libro: ");
       scanf("%s", aux2->titulo);

       printf("Número de páginas: ");
       scanf("%d", &aux2->paginas);
   }

    printf("Forward................\n");
    recorre(&forward, tomo, L, sizeof(Libro), &imprimeInt);
    printf("\n");
    printf("Backwards................\n");
    recorre(&backwards, tomo, L, sizeof(Libro), &imprimeInt);
    printf("\n");
    printf("Bidirectional................\n");
    recorre(&bidirectional, tomo, L, sizeof(Libro), &imprimeInt);

  printf("\n");
  free(vector);
  printf("\n");
  
  for (aux2 = tomo;aux<fin;++aux2){
    free(aux2->titulo);
  }

    free(tomo);
    free(vector);
}