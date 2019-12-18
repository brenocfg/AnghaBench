#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  mx; int /*<<< orphan*/  cv; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 unsigned int ITERATIONS ; 
 scalar_t__ TRUE ; 
 scalar_t__ allExit ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ bias ; 
 TYPE_1__ control ; 
 int /*<<< orphan*/  holdBarrier ; 
 int /*<<< orphan*/  master ; 
 int /*<<< orphan*/  masterThread ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int) ; 
 scalar_t__ pthread_barrier_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_barrier_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pthread_barrier_wait (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readyBarrier ; 
 int signalsSent ; 
 int signalsTakenCount ; 
 int /*<<< orphan*/  slave ; 
 int /*<<< orphan*/  slaveThread ; 
 int /*<<< orphan*/  startBarrier ; 
 int timeout ; 
 int timeoutCount ; 

int
main ()
{
  unsigned int i;

  assert(pthread_barrier_init(&startBarrier, NULL, 3) == 0);
  assert(pthread_barrier_init(&readyBarrier, NULL, 3) == 0);
  assert(pthread_barrier_init(&holdBarrier, NULL, 3) == 0);

  assert(pthread_create(&master, NULL, masterThread, (void *)(size_t)timeout) == 0);
  assert(pthread_create(&slave, NULL, slaveThread, NULL) == 0);

  allExit = FALSE;

  pthread_barrier_wait(&startBarrier);

  for (i = 1; !allExit; i++)
    {
      pthread_barrier_wait(&holdBarrier);
      if (i >= ITERATIONS)
	{
	  allExit = TRUE;
	}
      pthread_barrier_wait(&readyBarrier);
    }

  assert(pthread_join(slave, NULL) == 0);
  assert(pthread_join(master, NULL) == 0);

  printf("Signals sent = %d\nWait timeouts = %d\nSignals taken = %d\nBias = %d\nTimeout = %d\n",
	 signalsSent,
	 timeoutCount,
	 signalsTakenCount,
	 (int) bias,
	 timeout);

  /* Cleanup */
  assert(pthread_barrier_destroy(&holdBarrier) == 0);
  assert(pthread_barrier_destroy(&readyBarrier) == 0);
  assert(pthread_barrier_destroy(&startBarrier) == 0);
  assert(pthread_cond_destroy(&control.cv) == 0);
  assert(pthread_mutex_destroy(&control.mx) == 0);

  /* Success. */
  return 0;
}