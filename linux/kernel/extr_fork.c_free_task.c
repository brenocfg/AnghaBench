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
struct task_struct {int flags; int /*<<< orphan*/  stack_refcount; } ;

/* Variables and functions */
 int PF_KTHREAD ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  arch_release_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  free_kthread_struct (struct task_struct*) ; 
 int /*<<< orphan*/  free_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  ftrace_graph_exit_task (struct task_struct*) ; 
 int /*<<< orphan*/  put_seccomp_filter (struct task_struct*) ; 
 scalar_t__ refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_task_stack (struct task_struct*) ; 
 int /*<<< orphan*/  rt_mutex_debug_task_free (struct task_struct*) ; 

void free_task(struct task_struct *tsk)
{
#ifndef CONFIG_THREAD_INFO_IN_TASK
	/*
	 * The task is finally done with both the stack and thread_info,
	 * so free both.
	 */
	release_task_stack(tsk);
#else
	/*
	 * If the task had a separate stack allocation, it should be gone
	 * by now.
	 */
	WARN_ON_ONCE(refcount_read(&tsk->stack_refcount) != 0);
#endif
	rt_mutex_debug_task_free(tsk);
	ftrace_graph_exit_task(tsk);
	put_seccomp_filter(tsk);
	arch_release_task_struct(tsk);
	if (tsk->flags & PF_KTHREAD)
		free_kthread_struct(tsk);
	free_task_struct(tsk);
}