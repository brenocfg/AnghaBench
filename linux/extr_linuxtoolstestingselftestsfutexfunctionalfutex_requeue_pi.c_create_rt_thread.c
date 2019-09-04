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
struct sched_param {int sched_priority; } ;
typedef  int /*<<< orphan*/  schedp ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_EXPLICIT_SCHED ; 
 int /*<<< orphan*/  error (char*,int) ; 
 int /*<<< orphan*/  memset (struct sched_param*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int pthread_attr_setinheritsched (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pthread_attr_setschedparam (int /*<<< orphan*/ *,struct sched_param*) ; 
 int pthread_attr_setschedpolicy (int /*<<< orphan*/ *,int) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void* (*) (void*),void*) ; 

int create_rt_thread(pthread_t *pth, void*(*func)(void *), void *arg,
		     int policy, int prio)
{
	int ret;
	struct sched_param schedp;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	memset(&schedp, 0, sizeof(schedp));

	ret = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	if (ret) {
		error("pthread_attr_setinheritsched\n", ret);
		return -1;
	}

	ret = pthread_attr_setschedpolicy(&attr, policy);
	if (ret) {
		error("pthread_attr_setschedpolicy\n", ret);
		return -1;
	}

	schedp.sched_priority = prio;
	ret = pthread_attr_setschedparam(&attr, &schedp);
	if (ret) {
		error("pthread_attr_setschedparam\n", ret);
		return -1;
	}

	ret = pthread_create(pth, &attr, func, arg);
	if (ret) {
		error("pthread_create\n", ret);
		return -1;
	}
	return 0;
}