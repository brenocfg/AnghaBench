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
struct task_struct {scalar_t__ state; scalar_t__ parent; TYPE_1__* sighand; int /*<<< orphan*/  ptrace; } ;
struct TYPE_2__ {int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 scalar_t__ TASK_TRACED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ __TASK_TRACED ; 
 scalar_t__ __fatal_signal_pending (struct task_struct*) ; 
 scalar_t__ current ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_state (struct task_struct*,scalar_t__) ; 

__attribute__((used)) static void ptrace_unfreeze_traced(struct task_struct *task)
{
	if (task->state != __TASK_TRACED)
		return;

	WARN_ON(!task->ptrace || task->parent != current);

	/*
	 * PTRACE_LISTEN can allow ptrace_trap_notify to wake us up remotely.
	 * Recheck state under the lock to close this race.
	 */
	spin_lock_irq(&task->sighand->siglock);
	if (task->state == __TASK_TRACED) {
		if (__fatal_signal_pending(task))
			wake_up_state(task, __TASK_TRACED);
		else
			task->state = TASK_TRACED;
	}
	spin_unlock_irq(&task->sighand->siglock);
}