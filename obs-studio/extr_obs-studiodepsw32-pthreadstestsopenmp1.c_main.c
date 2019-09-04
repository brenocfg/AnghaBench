#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  MainThread () ; 
 int Verbose ; 
 int /*<<< orphan*/  printf (char*) ; 

int main(int argc, char *argv[]) {

  if (argc>1) Verbose = 1;

#ifdef _OPENMP
  omp_set_nested(-1);
  printf("%s%s%s\n", "Nested parallel blocks are ", omp_get_nested()?" ":"NOT ", "supported.");
#endif

  MainThread();

#ifdef SPAWN_THREADS
  {
    pthread_t a_thr;
    pthread_t b_thr;
    int status;

    printf("%s:%d - %s - a_thr:%p - b_thr:%p\n",
           __FILE__,__LINE__,__FUNCTION__,a_thr.p,b_thr.p);

    status = pthread_create(&a_thr, NULL, _thread, (void*) 1 );
    if ( status != 0 ) {
      printf("Failed to create thread 1\n");
      return (-1);
    }

    status = pthread_create(&b_thr, NULL, _thread, (void*) 2 );
    if ( status != 0 ) {
      printf("Failed to create thread 2\n");
      return (-1);
    }

    status = pthread_join(a_thr, NULL);
    if ( status != 0 ) {
      printf("Failed to join thread 1\n");
      return (-1);
    }
    printf("Joined thread1\n");

    status = pthread_join(b_thr, NULL);
    if ( status != 0 ) {
      printf("Failed to join thread 2\n");
      return (-1);
    }
    printf("Joined thread2\n");
  }
#endif // SPAWN_THREADS

  short OK = 0;
  // Check that we have OpenMP before declaring things OK formally.
#ifdef _OPENMP
    OK = 1;
    {
      short i;
      for (i=0;i<3;i++) OK &= ThreadOK[i];
    }
    if (OK) printf("OMP : All looks good\n");
    else printf("OMP : Error\n");
#else
    printf("OpenMP seems not enabled ...\n");
#endif

  return OK?0:1;
}