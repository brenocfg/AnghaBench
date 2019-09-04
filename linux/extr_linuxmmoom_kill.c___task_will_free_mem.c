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
struct task_struct {int flags; struct signal_struct* signal; } ;
struct signal_struct {int flags; } ;

/* Variables and functions */
 int PF_EXITING ; 
 int SIGNAL_GROUP_COREDUMP ; 
 int SIGNAL_GROUP_EXIT ; 
 scalar_t__ thread_group_empty (struct task_struct*) ; 

__attribute__((used)) static inline bool __task_will_free_mem(struct task_struct *task)
{
	struct signal_struct *sig = task->signal;

	/*
	 * A coredumping process may sleep for an extended period in exit_mm(),
	 * so the oom killer cannot assume that the process will promptly exit
	 * and release memory.
	 */
	if (sig->flags & SIGNAL_GROUP_COREDUMP)
		return false;

	if (sig->flags & SIGNAL_GROUP_EXIT)
		return true;

	if (thread_group_empty(task) && (task->flags & PF_EXITING))
		return true;

	return false;
}