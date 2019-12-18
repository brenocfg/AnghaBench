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
struct sched_param {scalar_t__ sched_priority; } ;

/* Variables and functions */
 int PTHREAD_BARRIER_SERIAL_THREAD ; 
 int SCHED_OTHER ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  endBarrier ; 
 int pthread_barrier_wait (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_getschedparam (int /*<<< orphan*/ ,int*,struct sched_param*) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  startBarrier ; 

void * func(void * arg)
{
  int policy;
  int result;
  struct sched_param param;

  result = pthread_barrier_wait(&startBarrier);
  assert(result == 0 || result == PTHREAD_BARRIER_SERIAL_THREAD);
  assert(pthread_getschedparam(pthread_self(), &policy, &param) == 0);
  assert(policy == SCHED_OTHER);
  result = pthread_barrier_wait(&endBarrier);
  assert(result == 0 || result == PTHREAD_BARRIER_SERIAL_THREAD);
  return (void *) (size_t)param.sched_priority;
}