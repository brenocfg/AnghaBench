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
typedef  long time_t ;
struct timespec {long tv_nsec; long tv_sec; } ;
struct thread_arg {int id; long lock; int ret; struct timespec* timeout; } ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int RET_ERROR ; 
 int RET_PASS ; 
 int /*<<< orphan*/  SCHED_FIFO ; 
 struct thread_arg THREAD_ARG_INITIALIZER ; 
 int THREAD_MAX ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* broadcast_wakerfn (void*) ; 
 int clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 scalar_t__ create_rt_thread (int /*<<< orphan*/ *,void* (*) (void*),void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  info (char*,int) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,void**) ; 
 void* signal_wakerfn (void*) ; 
 void* third_party_blocker (void*) ; 
 void* waiterfn (void*) ; 
 int /*<<< orphan*/  waiters_woken ; 

int unit_test(int broadcast, long lock, int third_party_owner, long timeout_ns)
{
	void *(*wakerfn)(void *) = signal_wakerfn;
	struct thread_arg blocker_arg = THREAD_ARG_INITIALIZER;
	struct thread_arg waker_arg = THREAD_ARG_INITIALIZER;
	pthread_t waiter[THREAD_MAX], waker, blocker;
	struct timespec ts, *tsp = NULL;
	struct thread_arg args[THREAD_MAX];
	int *waiter_ret;
	int i, ret = RET_PASS;

	if (timeout_ns) {
		time_t secs;

		info("timeout_ns = %ld\n", timeout_ns);
		ret = clock_gettime(CLOCK_MONOTONIC, &ts);
		secs = (ts.tv_nsec + timeout_ns) / 1000000000;
		ts.tv_nsec = ((int64_t)ts.tv_nsec + timeout_ns) % 1000000000;
		ts.tv_sec += secs;
		info("ts.tv_sec  = %ld\n", ts.tv_sec);
		info("ts.tv_nsec = %ld\n", ts.tv_nsec);
		tsp = &ts;
	}

	if (broadcast)
		wakerfn = broadcast_wakerfn;

	if (third_party_owner) {
		if (create_rt_thread(&blocker, third_party_blocker,
				     (void *)&blocker_arg, SCHED_FIFO, 1)) {
			error("Creating third party blocker thread failed\n",
			      errno);
			ret = RET_ERROR;
			goto out;
		}
	}

	atomic_set(&waiters_woken, 0);
	for (i = 0; i < THREAD_MAX; i++) {
		args[i].id = i;
		args[i].timeout = tsp;
		info("Starting thread %d\n", i);
		if (create_rt_thread(&waiter[i], waiterfn, (void *)&args[i],
				     SCHED_FIFO, 1)) {
			error("Creating waiting thread failed\n", errno);
			ret = RET_ERROR;
			goto out;
		}
	}
	waker_arg.lock = lock;
	if (create_rt_thread(&waker, wakerfn, (void *)&waker_arg,
			     SCHED_FIFO, 1)) {
		error("Creating waker thread failed\n", errno);
		ret = RET_ERROR;
		goto out;
	}

	/* Wait for threads to finish */
	/* Store the first error or failure encountered in waiter_ret */
	waiter_ret = &args[0].ret;
	for (i = 0; i < THREAD_MAX; i++)
		pthread_join(waiter[i],
			     *waiter_ret ? NULL : (void **)&waiter_ret);

	if (third_party_owner)
		pthread_join(blocker, NULL);
	pthread_join(waker, NULL);

out:
	if (!ret) {
		if (*waiter_ret)
			ret = *waiter_ret;
		else if (waker_arg.ret < 0)
			ret = waker_arg.ret;
		else if (blocker_arg.ret)
			ret = blocker_arg.ret;
	}

	return ret;
}