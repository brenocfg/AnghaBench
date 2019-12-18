#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int /*<<< orphan*/  pi_lock; } ;
struct rt_mutex_waiter {int dummy; } ;
struct rt_mutex {int /*<<< orphan*/  wait_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  pi_lock; int /*<<< orphan*/ * pi_blocked_on; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_MUTEX_MIN_CHAINWALK ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt_mutex_adjust_prio (struct task_struct*) ; 
 int /*<<< orphan*/  rt_mutex_adjust_prio_chain (struct task_struct*,int /*<<< orphan*/ ,struct rt_mutex*,struct rt_mutex*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  rt_mutex_dequeue (struct rt_mutex*,struct rt_mutex_waiter*) ; 
 int /*<<< orphan*/  rt_mutex_dequeue_pi (struct task_struct*,struct rt_mutex_waiter*) ; 
 int /*<<< orphan*/  rt_mutex_enqueue_pi (struct task_struct*,struct rt_mutex_waiter*) ; 
 scalar_t__ rt_mutex_has_waiters (struct rt_mutex*) ; 
 struct task_struct* rt_mutex_owner (struct rt_mutex*) ; 
 struct rt_mutex_waiter* rt_mutex_top_waiter (struct rt_mutex*) ; 
 struct rt_mutex* task_blocked_on_lock (struct task_struct*) ; 

__attribute__((used)) static void remove_waiter(struct rt_mutex *lock,
			  struct rt_mutex_waiter *waiter)
{
	bool is_top_waiter = (waiter == rt_mutex_top_waiter(lock));
	struct task_struct *owner = rt_mutex_owner(lock);
	struct rt_mutex *next_lock;

	lockdep_assert_held(&lock->wait_lock);

	raw_spin_lock(&current->pi_lock);
	rt_mutex_dequeue(lock, waiter);
	current->pi_blocked_on = NULL;
	raw_spin_unlock(&current->pi_lock);

	/*
	 * Only update priority if the waiter was the highest priority
	 * waiter of the lock and there is an owner to update.
	 */
	if (!owner || !is_top_waiter)
		return;

	raw_spin_lock(&owner->pi_lock);

	rt_mutex_dequeue_pi(owner, waiter);

	if (rt_mutex_has_waiters(lock))
		rt_mutex_enqueue_pi(owner, rt_mutex_top_waiter(lock));

	rt_mutex_adjust_prio(owner);

	/* Store the lock on which owner is blocked or NULL */
	next_lock = task_blocked_on_lock(owner);

	raw_spin_unlock(&owner->pi_lock);

	/*
	 * Don't walk the chain, if the owner task is not blocked
	 * itself.
	 */
	if (!next_lock)
		return;

	/* gets dropped in rt_mutex_adjust_prio_chain()! */
	get_task_struct(owner);

	raw_spin_unlock_irq(&lock->wait_lock);

	rt_mutex_adjust_prio_chain(owner, RT_MUTEX_MIN_CHAINWALK, lock,
				   next_lock, NULL, current);

	raw_spin_lock_irq(&lock->wait_lock);
}