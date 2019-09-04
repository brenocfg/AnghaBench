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
struct rt_mutex_waiter {int dummy; } ;
struct rt_mutex {int /*<<< orphan*/  wait_lock; } ;
struct hrtimer_sleeper {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int __rt_mutex_slowlock (struct rt_mutex*,int /*<<< orphan*/ ,struct hrtimer_sleeper*,struct rt_mutex_waiter*) ; 
 int /*<<< orphan*/  fixup_rt_mutex_waiters (struct rt_mutex*) ; 
 int /*<<< orphan*/  raw_spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 

int rt_mutex_wait_proxy_lock(struct rt_mutex *lock,
			       struct hrtimer_sleeper *to,
			       struct rt_mutex_waiter *waiter)
{
	int ret;

	raw_spin_lock_irq(&lock->wait_lock);
	/* sleep on the mutex */
	set_current_state(TASK_INTERRUPTIBLE);
	ret = __rt_mutex_slowlock(lock, TASK_INTERRUPTIBLE, to, waiter);
	/*
	 * try_to_take_rt_mutex() sets the waiter bit unconditionally. We might
	 * have to fix that up.
	 */
	fixup_rt_mutex_waiters(lock);
	raw_spin_unlock_irq(&lock->wait_lock);

	return ret;
}