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
typedef  scalar_t__ task_work_func_t ;
struct task_struct {int /*<<< orphan*/  pi_lock; struct callback_head* task_works; } ;
struct callback_head {scalar_t__ func; struct callback_head* next; } ;

/* Variables and functions */
 struct callback_head* READ_ONCE (struct callback_head*) ; 
 struct callback_head* cmpxchg (struct callback_head**,struct callback_head*,struct callback_head*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct callback_head *
task_work_cancel(struct task_struct *task, task_work_func_t func)
{
	struct callback_head **pprev = &task->task_works;
	struct callback_head *work;
	unsigned long flags;

	if (likely(!task->task_works))
		return NULL;
	/*
	 * If cmpxchg() fails we continue without updating pprev.
	 * Either we raced with task_work_add() which added the
	 * new entry before this work, we will find it again. Or
	 * we raced with task_work_run(), *pprev == NULL/exited.
	 */
	raw_spin_lock_irqsave(&task->pi_lock, flags);
	while ((work = READ_ONCE(*pprev))) {
		if (work->func != func)
			pprev = &work->next;
		else if (cmpxchg(pprev, work, work->next) == work)
			break;
	}
	raw_spin_unlock_irqrestore(&task->pi_lock, flags);

	return work;
}