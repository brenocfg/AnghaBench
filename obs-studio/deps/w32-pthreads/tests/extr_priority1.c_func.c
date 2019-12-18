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
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int SCHED_OTHER ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ pthread_getschedparam (int /*<<< orphan*/ ,int*,struct sched_param*) ; 
 int /*<<< orphan*/  pthread_self () ; 

void *
func(void * arg)
{
  int policy;
  struct sched_param param;
  pthread_t threadID = pthread_self();

  assert(pthread_getschedparam(threadID, &policy, &param) == 0);
  assert(policy == SCHED_OTHER);
  return (void *) (size_t)(param.sched_priority);
}