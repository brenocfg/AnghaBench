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
struct task_struct {unsigned int exit_code; scalar_t__ exit_state; int /*<<< orphan*/  ptrace; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PTRACE_DETACH ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __ptrace_detach (int /*<<< orphan*/ ,struct task_struct*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  proc_ptrace_connector (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptrace_disable (struct task_struct*) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 int /*<<< orphan*/  valid_signal (unsigned int) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ptrace_detach(struct task_struct *child, unsigned int data)
{
	if (!valid_signal(data))
		return -EIO;

	/* Architecture-specific hardware disable .. */
	ptrace_disable(child);

	write_lock_irq(&tasklist_lock);
	/*
	 * We rely on ptrace_freeze_traced(). It can't be killed and
	 * untraced by another thread, it can't be a zombie.
	 */
	WARN_ON(!child->ptrace || child->exit_state);
	/*
	 * tasklist_lock avoids the race with wait_task_stopped(), see
	 * the comment in ptrace_resume().
	 */
	child->exit_code = data;
	__ptrace_detach(current, child);
	write_unlock_irq(&tasklist_lock);

	proc_ptrace_connector(child, PTRACE_DETACH);

	return 0;
}