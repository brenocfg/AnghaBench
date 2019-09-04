#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wake_q_head {int dummy; } ;
struct rt_mutex_waiter {int /*<<< orphan*/  task; } ;
struct rt_mutex {void* owner; } ;
struct TYPE_4__ {int /*<<< orphan*/  pi_lock; } ;

/* Variables and functions */
 scalar_t__ RT_MUTEX_HAS_WAITERS ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt_mutex_adjust_prio (TYPE_1__*) ; 
 int /*<<< orphan*/  rt_mutex_dequeue_pi (TYPE_1__*,struct rt_mutex_waiter*) ; 
 struct rt_mutex_waiter* rt_mutex_top_waiter (struct rt_mutex*) ; 
 int /*<<< orphan*/  wake_q_add (struct wake_q_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mark_wakeup_next_waiter(struct wake_q_head *wake_q,
				    struct rt_mutex *lock)
{
	struct rt_mutex_waiter *waiter;

	raw_spin_lock(&current->pi_lock);

	waiter = rt_mutex_top_waiter(lock);

	/*
	 * Remove it from current->pi_waiters and deboost.
	 *
	 * We must in fact deboost here in order to ensure we call
	 * rt_mutex_setprio() to update p->pi_top_task before the
	 * task unblocks.
	 */
	rt_mutex_dequeue_pi(current, waiter);
	rt_mutex_adjust_prio(current);

	/*
	 * As we are waking up the top waiter, and the waiter stays
	 * queued on the lock until it gets the lock, this lock
	 * obviously has waiters. Just set the bit here and this has
	 * the added benefit of forcing all new tasks into the
	 * slow path making sure no task of lower priority than
	 * the top waiter can steal this lock.
	 */
	lock->owner = (void *) RT_MUTEX_HAS_WAITERS;

	/*
	 * We deboosted before waking the top waiter task such that we don't
	 * run two tasks with the 'same' priority (and ensure the
	 * p->pi_top_task pointer points to a blocked task). This however can
	 * lead to priority inversion if we would get preempted after the
	 * deboost but before waking our donor task, hence the preempt_disable()
	 * before unlock.
	 *
	 * Pairs with preempt_enable() in rt_mutex_postunlock();
	 */
	preempt_disable();
	wake_q_add(wake_q, waiter->task);
	raw_spin_unlock(&current->pi_lock);
}