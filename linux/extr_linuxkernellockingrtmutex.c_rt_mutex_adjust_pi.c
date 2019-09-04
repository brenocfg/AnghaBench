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
struct task_struct {int /*<<< orphan*/  pi_lock; struct rt_mutex_waiter* pi_blocked_on; } ;
struct rt_mutex_waiter {struct rt_mutex* lock; } ;
struct rt_mutex {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_MUTEX_MIN_CHAINWALK ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  rt_mutex_adjust_prio_chain (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct rt_mutex*,int /*<<< orphan*/ *,struct task_struct*) ; 
 scalar_t__ rt_mutex_waiter_equal (struct rt_mutex_waiter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_to_waiter (struct task_struct*) ; 

void rt_mutex_adjust_pi(struct task_struct *task)
{
	struct rt_mutex_waiter *waiter;
	struct rt_mutex *next_lock;
	unsigned long flags;

	raw_spin_lock_irqsave(&task->pi_lock, flags);

	waiter = task->pi_blocked_on;
	if (!waiter || rt_mutex_waiter_equal(waiter, task_to_waiter(task))) {
		raw_spin_unlock_irqrestore(&task->pi_lock, flags);
		return;
	}
	next_lock = waiter->lock;
	raw_spin_unlock_irqrestore(&task->pi_lock, flags);

	/* gets dropped in rt_mutex_adjust_prio_chain()! */
	get_task_struct(task);

	rt_mutex_adjust_prio_chain(task, RT_MUTEX_MIN_CHAINWALK, NULL,
				   next_lock, NULL, task);
}