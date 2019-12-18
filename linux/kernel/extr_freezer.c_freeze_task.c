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
struct task_struct {int flags; } ;

/* Variables and functions */
 int PF_KTHREAD ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  fake_signal_wake_up (struct task_struct*) ; 
 int /*<<< orphan*/  freezer_lock ; 
 scalar_t__ freezer_should_skip (struct task_struct*) ; 
 int /*<<< orphan*/  freezing (struct task_struct*) ; 
 scalar_t__ frozen (struct task_struct*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_state (struct task_struct*,int /*<<< orphan*/ ) ; 

bool freeze_task(struct task_struct *p)
{
	unsigned long flags;

	/*
	 * This check can race with freezer_do_not_count, but worst case that
	 * will result in an extra wakeup being sent to the task.  It does not
	 * race with freezer_count(), the barriers in freezer_count() and
	 * freezer_should_skip() ensure that either freezer_count() sees
	 * freezing == true in try_to_freeze() and freezes, or
	 * freezer_should_skip() sees !PF_FREEZE_SKIP and freezes the task
	 * normally.
	 */
	if (freezer_should_skip(p))
		return false;

	spin_lock_irqsave(&freezer_lock, flags);
	if (!freezing(p) || frozen(p)) {
		spin_unlock_irqrestore(&freezer_lock, flags);
		return false;
	}

	if (!(p->flags & PF_KTHREAD))
		fake_signal_wake_up(p);
	else
		wake_up_state(p, TASK_INTERRUPTIBLE);

	spin_unlock_irqrestore(&freezer_lock, flags);
	return true;
}