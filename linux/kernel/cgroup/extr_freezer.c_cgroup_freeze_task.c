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
struct task_struct {int /*<<< orphan*/  jobctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  JOBCTL_TRAP_FREEZE ; 
 int /*<<< orphan*/  lock_task_sighand (struct task_struct*,unsigned long*) ; 
 int /*<<< orphan*/  signal_wake_up (struct task_struct*,int) ; 
 int /*<<< orphan*/  unlock_task_sighand (struct task_struct*,unsigned long*) ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

__attribute__((used)) static void cgroup_freeze_task(struct task_struct *task, bool freeze)
{
	unsigned long flags;

	/* If the task is about to die, don't bother with freezing it. */
	if (!lock_task_sighand(task, &flags))
		return;

	if (freeze) {
		task->jobctl |= JOBCTL_TRAP_FREEZE;
		signal_wake_up(task, false);
	} else {
		task->jobctl &= ~JOBCTL_TRAP_FREEZE;
		wake_up_process(task);
	}

	unlock_task_sighand(task, &flags);
}