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
struct task_struct {int flags; unsigned long jobctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long JOBCTL_PENDING_MASK ; 
 unsigned long JOBCTL_STOP_CONSUME ; 
 unsigned long JOBCTL_STOP_SIGMASK ; 
 unsigned long JOBCTL_TRAPPING ; 
 int PF_EXITING ; 
 scalar_t__ fatal_signal_pending (struct task_struct*) ; 
 scalar_t__ unlikely (int) ; 

bool task_set_jobctl_pending(struct task_struct *task, unsigned long mask)
{
	BUG_ON(mask & ~(JOBCTL_PENDING_MASK | JOBCTL_STOP_CONSUME |
			JOBCTL_STOP_SIGMASK | JOBCTL_TRAPPING));
	BUG_ON((mask & JOBCTL_TRAPPING) && !(mask & JOBCTL_PENDING_MASK));

	if (unlikely(fatal_signal_pending(task) || (task->flags & PF_EXITING)))
		return false;

	if (mask & JOBCTL_STOP_SIGMASK)
		task->jobctl &= ~JOBCTL_STOP_SIGMASK;

	task->jobctl |= mask;
	return true;
}