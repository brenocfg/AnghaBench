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

/* Variables and functions */
 int NUMTHREADS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  barrier ; 
 int /*<<< orphan*/  func ; 
 int /*<<< orphan*/  mx ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ pthread_barrier_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_barrier_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int serialThreadCount ; 

int
main()
{
  int i, j;
  pthread_t t[NUMTHREADS + 1];

  for (j = 1; j <= NUMTHREADS; j++)
    {
      printf("Barrier height = %d\n", j);

      serialThreadCount = 0;

      assert(pthread_barrier_init(&barrier, NULL, j) == 0);

      for (i = 1; i <= j; i++)
        {
          assert(pthread_create(&t[i], NULL, func, NULL) == 0);
        }

      for (i = 1; i <= j; i++)
        {
          assert(pthread_join(t[i], NULL) == 0);
        }

      assert(serialThreadCount == 1);

      assert(pthread_barrier_destroy(&barrier) == 0);
    }

  assert(pthread_mutex_destroy(&mx) == 0);

  return 0;
}