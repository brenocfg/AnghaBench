#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_5__ {int threadnum; int oncenum; } ;
typedef  TYPE_1__ bag_t ;
struct TYPE_7__ {int i; int /*<<< orphan*/  cs; } ;
struct TYPE_6__ {int /*<<< orphan*/  cs; int /*<<< orphan*/  i; } ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  GetCurrentThread () ; 
 int /*<<< orphan*/  InitializeCriticalSection (int /*<<< orphan*/ *) ; 
 int NUM_ONCE ; 
 int NUM_THREADS ; 
 int /*<<< orphan*/  REALTIME_PRIORITY_CLASS ; 
 int /*<<< orphan*/  SetPriorityClass (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetThreadPriority (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mythread ; 
 TYPE_4__ numOnce ; 
 TYPE_3__ numThreads ; 
 int /*<<< orphan*/  o ; 
 int /*<<< orphan*/ * once ; 
 int /*<<< orphan*/  print_lock ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_yield () ; 
 TYPE_1__** threadbag ; 

int
main()
{
  pthread_t t[NUM_THREADS][NUM_ONCE];
  int i, j;
  
  InitializeCriticalSection(&print_lock);
  InitializeCriticalSection(&numThreads.cs);
  InitializeCriticalSection(&numOnce.cs);

#if 0
  /*       once thrd  prio change */
  printf("once thrd  prio  error\n");
#endif

  /*
   * Set the priority class to realtime - otherwise normal
   * Windows random priority boosting will obscure any problems.
   */
  SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
  /* Set main thread to lower prio than threads */
  SetThreadPriority(GetCurrentThread(), -2);

  for (j = 0; j < NUM_ONCE; j++)
    {
      once[j] = o;

      for (i = 0; i < NUM_THREADS; i++)
        {
	  bag_t * bag = &threadbag[i][j];
	  bag->threadnum = i;
	  bag->oncenum = j;
          /* GCC build: create was failing with EAGAIN after 790 threads */
          while (0 != pthread_create(&t[i][j], NULL, mythread, (void *)bag))
            sched_yield();
        }
    }

  for (j = 0; j < NUM_ONCE; j++)
    for (i = 0; i < NUM_THREADS; i++)
      if (pthread_join(t[i][j], NULL) != 0)
        printf("Join failed for [thread,once] = [%d,%d]\n", i, j);

  /*
   * All threads will cancel, none will return normally from
   * pthread_once and so numThreads should never be incremented. However,
   * numOnce should be incremented by every thread (NUM_THREADS*NUM_ONCE).
   */
  assert(numOnce.i == NUM_ONCE * NUM_THREADS);
  assert(numThreads.i == 0);

  DeleteCriticalSection(&numOnce.cs);
  DeleteCriticalSection(&numThreads.cs);
  DeleteCriticalSection(&print_lock);

  return 0;
}