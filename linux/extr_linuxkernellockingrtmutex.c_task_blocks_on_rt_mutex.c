#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  deadline; } ;
struct task_struct {int /*<<< orphan*/  pi_lock; struct rt_mutex_waiter* pi_blocked_on; TYPE_1__ dl; int /*<<< orphan*/  prio; } ;
struct rt_mutex_waiter {int /*<<< orphan*/  deadline; int /*<<< orphan*/  prio; struct rt_mutex* lock; struct task_struct* task; } ;
struct rt_mutex {int /*<<< orphan*/  wait_lock; } ;
typedef  enum rtmutex_chainwalk { ____Placeholder_rtmutex_chainwalk } rtmutex_chainwalk ;

/* Variables and functions */
 int EDEADLK ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt_mutex_adjust_prio (struct task_struct*) ; 
 int rt_mutex_adjust_prio_chain (struct task_struct*,int,struct rt_mutex*,struct rt_mutex*,struct rt_mutex_waiter*,struct task_struct*) ; 
 scalar_t__ rt_mutex_cond_detect_deadlock (struct rt_mutex_waiter*,int) ; 
 int /*<<< orphan*/  rt_mutex_dequeue_pi (struct task_struct*,struct rt_mutex_waiter*) ; 
 int /*<<< orphan*/  rt_mutex_enqueue (struct rt_mutex*,struct rt_mutex_waiter*) ; 
 int /*<<< orphan*/  rt_mutex_enqueue_pi (struct task_struct*,struct rt_mutex_waiter*) ; 
 scalar_t__ rt_mutex_has_waiters (struct rt_mutex*) ; 
 struct task_struct* rt_mutex_owner (struct rt_mutex*) ; 
 struct rt_mutex_waiter* rt_mutex_top_waiter (struct rt_mutex*) ; 
 struct rt_mutex* task_blocked_on_lock (struct task_struct*) ; 

__attribute__((used)) static int task_blocks_on_rt_mutex(struct rt_mutex *lock,
				   struct rt_mutex_waiter *waiter,
				   struct task_struct *task,
				   enum rtmutex_chainwalk chwalk)
{
	struct task_struct *owner = rt_mutex_owner(lock);
	struct rt_mutex_waiter *top_waiter = waiter;
	struct rt_mutex *next_lock;
	int chain_walk = 0, res;

	lockdep_assert_held(&lock->wait_lock);

	/*
	 * Early deadlock detection. We really don't want the task to
	 * enqueue on itself just to untangle the mess later. It's not
	 * only an optimization. We drop the locks, so another waiter
	 * can come in before the chain walk detects the deadlock. So
	 * the other will detect the deadlock and return -EDEADLOCK,
	 * which is wrong, as the other waiter is not in a deadlock
	 * situation.
	 */
	if (owner == task)
		return -EDEADLK;

	raw_spin_lock(&task->pi_lock);
	waiter->task = task;
	waiter->lock = lock;
	waiter->prio = task->prio;
	waiter->deadline = task->dl.deadline;

	/* Get the top priority waiter on the lock */
	if (rt_mutex_has_waiters(lock))
		top_waiter = rt_mutex_top_waiter(lock);
	rt_mutex_enqueue(lock, waiter);

	task->pi_blocked_on = waiter;

	raw_spin_unlock(&task->pi_lock);

	if (!owner)
		return 0;

	raw_spin_lock(&owner->pi_lock);
	if (waiter == rt_mutex_top_waiter(lock)) {
		rt_mutex_dequeue_pi(owner, top_waiter);
		rt_mutex_enqueue_pi(owner, waiter);

		rt_mutex_adjust_prio(owner);
		if (owner->pi_blocked_on)
			chain_walk = 1;
	} else if (rt_mutex_cond_detect_deadlock(waiter, chwalk)) {
		chain_walk = 1;
	}

	/* Store the lock on which owner is blocked or NULL */
	next_lock = task_blocked_on_lock(owner);

	raw_spin_unlock(&owner->pi_lock);
	/*
	 * Even if full deadlock detection is on, if the owner is not
	 * blocked itself, we can avoid finding this out in the chain
	 * walk.
	 */
	if (!chain_walk || !next_lock)
		return 0;

	/*
	 * The owner can't disappear while holding a lock,
	 * so the owner struct is protected by wait_lock.
	 * Gets dropped in rt_mutex_adjust_prio_chain()!
	 */
	get_task_struct(owner);

	raw_spin_unlock_irq(&lock->wait_lock);

	res = rt_mutex_adjust_prio_chain(owner, chwalk, lock,
					 next_lock, waiter, task);

	raw_spin_lock_irq(&lock->wait_lock);

	return res;
}