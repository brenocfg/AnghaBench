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
struct timespec {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mx; int /*<<< orphan*/  value; int /*<<< orphan*/  cv; } ;

/* Variables and functions */
 scalar_t__ ETIMEDOUT ; 
 int /*<<< orphan*/  allExit ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__ control ; 
 int /*<<< orphan*/  holdBarrier ; 
 int /*<<< orphan*/  millisecondsFromNow (struct timespec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_barrier_wait (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readyBarrier ; 
 int /*<<< orphan*/  signalsTakenCount ; 
 int /*<<< orphan*/  startBarrier ; 
 int /*<<< orphan*/  timeoutCount ; 

void *
slaveThread (void * arg)
{
  struct timespec time;

  pthread_barrier_wait(&startBarrier);

  do
    {
      assert(pthread_mutex_lock(&control.mx) == 0);
      if (pthread_cond_timedwait(&control.cv,
				 &control.mx,
				 millisecondsFromNow(&time, control.value)) == ETIMEDOUT)
	{
	  timeoutCount++;
	}
      else
	{
	  signalsTakenCount++;
	}
      assert(pthread_mutex_unlock(&control.mx) == 0);

      pthread_barrier_wait(&holdBarrier);
      pthread_barrier_wait(&readyBarrier);
    }
  while (!allExit);

  return NULL;
}