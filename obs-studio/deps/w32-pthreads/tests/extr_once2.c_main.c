#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_4__ {int i; int /*<<< orphan*/  cs; } ;
struct TYPE_3__ {int i; int /*<<< orphan*/  cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitializeCriticalSection (int /*<<< orphan*/ *) ; 
 int NUM_ONCE ; 
 int NUM_THREADS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mythread ; 
 TYPE_2__ numOnce ; 
 TYPE_1__ numThreads ; 
 int /*<<< orphan*/  o ; 
 int /*<<< orphan*/ * once ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_yield () ; 

int
main()
{
  pthread_t t[NUM_THREADS][NUM_ONCE];
  int i, j;
  
  InitializeCriticalSection(&numThreads.cs);
  InitializeCriticalSection(&numOnce.cs);

  for (j = 0; j < NUM_ONCE; j++)
    {
      once[j] = o;

      for (i = 0; i < NUM_THREADS; i++)
        {
	  /* GCC build: create was failing with EAGAIN after 790 threads */
          while (0 != pthread_create(&t[i][j], NULL, mythread, (void *)(size_t)j))
	    sched_yield();
        }
    }

  for (j = 0; j < NUM_ONCE; j++)
    for (i = 0; i < NUM_THREADS; i++)
      if (pthread_join(t[i][j], NULL) != 0)
        printf("Join failed for [thread,once] = [%d,%d]\n", i, j);

  assert(numOnce.i == NUM_ONCE);
  assert(numThreads.i == NUM_THREADS * NUM_ONCE);

  DeleteCriticalSection(&numOnce.cs);
  DeleteCriticalSection(&numThreads.cs);

  return 0;
}