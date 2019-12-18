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
struct wake_q_head {int dummy; } ;
struct task_struct {int dummy; } ;
struct futex_q {int /*<<< orphan*/  lock_ptr; scalar_t__ rt_waiter; scalar_t__ pi_state; struct task_struct* task; } ;

/* Variables and functions */
 scalar_t__ WARN (int,char*) ; 
 int /*<<< orphan*/  __unqueue_futex (struct futex_q*) ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_q_add_safe (struct wake_q_head*,struct task_struct*) ; 

__attribute__((used)) static void mark_wake_futex(struct wake_q_head *wake_q, struct futex_q *q)
{
	struct task_struct *p = q->task;

	if (WARN(q->pi_state || q->rt_waiter, "refusing to wake PI futex\n"))
		return;

	get_task_struct(p);
	__unqueue_futex(q);
	/*
	 * The waiting task can free the futex_q as soon as q->lock_ptr = NULL
	 * is written, without taking any locks. This is possible in the event
	 * of a spurious wakeup, for example. A memory barrier is required here
	 * to prevent the following store to lock_ptr from getting ahead of the
	 * plist_del in __unqueue_futex().
	 */
	smp_store_release(&q->lock_ptr, NULL);

	/*
	 * Queue the task for later wakeup for after we've released
	 * the hb->lock. wake_q_add() grabs reference to p.
	 */
	wake_q_add_safe(wake_q, p);
}