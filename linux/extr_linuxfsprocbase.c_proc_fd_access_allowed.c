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
struct task_struct {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTRACE_MODE_READ_FSCREDS ; 
 struct task_struct* get_proc_task (struct inode*) ; 
 int ptrace_may_access (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 

__attribute__((used)) static int proc_fd_access_allowed(struct inode *inode)
{
	struct task_struct *task;
	int allowed = 0;
	/* Allow access to a task's file descriptors if it is us or we
	 * may use ptrace attach to the process and find out that
	 * information.
	 */
	task = get_proc_task(inode);
	if (task) {
		allowed = ptrace_may_access(task, PTRACE_MODE_READ_FSCREDS);
		put_task_struct(task);
	}
	return allowed;
}