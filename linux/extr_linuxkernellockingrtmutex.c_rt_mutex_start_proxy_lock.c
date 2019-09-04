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
 int __rt_mutex_start_proxy_lock (struct rt_mutex*,struct rt_mutex_waiter*,struct task_struct*) ; 
 int /*<<< orphan*/  raw_spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_waiter (struct rt_mutex*,struct rt_mutex_waiter*) ; 
 scalar_t__ unlikely (int) ; 

int rt_mutex_start_proxy_lock(struct rt_mutex *lock,
			      struct rt_mutex_waiter *waiter,
			      struct task_struct *task)
{
	int ret;

	raw_spin_lock_irq(&lock->wait_lock);
	ret = __rt_mutex_start_proxy_lock(lock, waiter, task);
	if (unlikely(ret))
		remove_waiter(lock, waiter);
	raw_spin_unlock_irq(&lock->wait_lock);

	return ret;
}