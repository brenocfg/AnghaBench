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
struct task_struct {int jobctl; TYPE_1__* sighand; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 int JOBCTL_LISTENING ; 
 int /*<<< orphan*/  __TASK_TRACED ; 
 int /*<<< orphan*/  __fatal_signal_pending (struct task_struct*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ task_is_traced (struct task_struct*) ; 

__attribute__((used)) static bool ptrace_freeze_traced(struct task_struct *task)
{
	bool ret = false;

	/* Lockless, nobody but us can set this flag */
	if (task->jobctl & JOBCTL_LISTENING)
		return ret;

	spin_lock_irq(&task->sighand->siglock);
	if (task_is_traced(task) && !__fatal_signal_pending(task)) {
		task->state = __TASK_TRACED;
		ret = true;
	}
	spin_unlock_irq(&task->sighand->siglock);

	return ret;
}