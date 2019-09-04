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
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int LONG ;

/* Variables and functions */
 int BARRIERMULTIPLE ; 
 int HEIGHT ; 
 int NUMTHREADS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  barrier ; 
 int /*<<< orphan*/  func ; 
 int /*<<< orphan*/  mx ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 scalar_t__ pthread_barrier_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_barrier_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,void**) ; 
 scalar_t__ pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ totalThreadCrossings ; 

int
main()
{
  int i, j;
  void* result;
  int serialThreadsTotal;
  LONG Crossings;
  pthread_t t[NUMTHREADS + 1];

  for (j = 1; j <= NUMTHREADS; j++)
    {
      int height = j<HEIGHT?j:HEIGHT;

      totalThreadCrossings = 0;
      Crossings = height * BARRIERMULTIPLE;

      printf("Threads=%d, Barrier height=%d\n", j, height);

      assert(pthread_barrier_init(&barrier, NULL, height) == 0);

      for (i = 1; i <= j; i++)
        {
          assert(pthread_create(&t[i], NULL, func, (void *)(size_t)Crossings) == 0);
        }

      serialThreadsTotal = 0;
      for (i = 1; i <= j; i++)
        {
          assert(pthread_join(t[i], &result) == 0);
          serialThreadsTotal += (int)(size_t)result;
        }

      assert(serialThreadsTotal == BARRIERMULTIPLE);

      assert(pthread_barrier_destroy(&barrier) == 0);
    }

  assert(pthread_mutex_destroy(&mx) == 0);

  return 0;
}