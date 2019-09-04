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
struct task_struct {int dummy; } ;
struct rt_mutex_waiter {int dummy; } ;
struct rt_mutex {int /*<<< orphan*/  wait_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_MUTEX_FULL_CHAINWALK ; 
 int /*<<< orphan*/  debug_rt_mutex_print_deadlock (struct rt_mutex_waiter*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt_mutex_owner (struct rt_mutex*) ; 
 int task_blocks_on_rt_mutex (struct rt_mutex*,struct rt_mutex_waiter*,struct task_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ try_to_take_rt_mutex (struct rt_mutex*,struct task_struct*,int /*<<< orphan*/ *) ; 

int __rt_mutex_start_proxy_lock(struct rt_mutex *lock,
			      struct rt_mutex_waiter *waiter,
			      struct task_struct *task)
{
	int ret;

	lockdep_assert_held(&lock->wait_lock);

	if (try_to_take_rt_mutex(lock, task, NULL))
		return 1;

	/* We enforce deadlock detection for futexes */
	ret = task_blocks_on_rt_mutex(lock, waiter, task,
				      RT_MUTEX_FULL_CHAINWALK);

	if (ret && !rt_mutex_owner(lock)) {
		/*
		 * Reset the return value. We might have
		 * returned with -EDEADLK and the owner
		 * released the lock while we were walking the
		 * pi chain.  Let the waiter sort it out.
		 */
		ret = 0;
	}

	debug_rt_mutex_print_deadlock(waiter);

	return ret;
}