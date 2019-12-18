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
struct thread_arg {scalar_t__ ret; scalar_t__ id; scalar_t__ timeout; } ;
typedef  int /*<<< orphan*/  futex_t ;

/* Variables and functions */
 scalar_t__ ETIMEDOUT ; 
 int /*<<< orphan*/  FUTEX_PRIVATE_FLAG ; 
 scalar_t__ RET_ERROR ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 int /*<<< orphan*/  f1 ; 
 int /*<<< orphan*/  f2 ; 
 int /*<<< orphan*/  futex_lock_pi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  futex_unlock_pi (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ futex_wait_requeue_pi (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  info (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  pthread_exit (void*) ; 
 char* strerror (scalar_t__) ; 
 int /*<<< orphan*/  usleep (int) ; 
 int /*<<< orphan*/  waiters_blocked ; 
 int /*<<< orphan*/  waiters_woken ; 

void *waiterfn(void *arg)
{
	struct thread_arg *args = (struct thread_arg *)arg;
	futex_t old_val;

	info("Waiter %ld: running\n", args->id);
	/* Each thread sleeps for a different amount of time
	 * This is to avoid races, because we don't lock the
	 * external mutex here */
	usleep(1000 * (long)args->id);

	old_val = f1;
	atomic_inc(&waiters_blocked);
	info("Calling futex_wait_requeue_pi: %p (%u) -> %p\n",
	     &f1, f1, &f2);
	args->ret = futex_wait_requeue_pi(&f1, old_val, &f2, args->timeout,
					  FUTEX_PRIVATE_FLAG);

	info("waiter %ld woke with %d %s\n", args->id, args->ret,
	     args->ret < 0 ? strerror(errno) : "");
	atomic_inc(&waiters_woken);
	if (args->ret < 0) {
		if (args->timeout && errno == ETIMEDOUT)
			args->ret = 0;
		else {
			args->ret = RET_ERROR;
			error("futex_wait_requeue_pi\n", errno);
		}
		futex_lock_pi(&f2, NULL, 0, FUTEX_PRIVATE_FLAG);
	}
	futex_unlock_pi(&f2, FUTEX_PRIVATE_FLAG);

	info("Waiter %ld: exiting with %d\n", args->id, args->ret);
	pthread_exit((void *)&args->ret);
}