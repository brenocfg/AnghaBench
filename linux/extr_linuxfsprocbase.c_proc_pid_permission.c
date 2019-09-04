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
struct pid_namespace {scalar_t__ hide_pid; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int EPERM ; 
 int ESRCH ; 
 scalar_t__ HIDEPID_INVISIBLE ; 
 int /*<<< orphan*/  HIDEPID_NO_ACCESS ; 
 int generic_permission (struct inode*,int) ; 
 struct task_struct* get_proc_task (struct inode*) ; 
 int has_pid_permissions (struct pid_namespace*,struct task_struct*,int /*<<< orphan*/ ) ; 
 struct pid_namespace* proc_pid_ns (struct inode*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 

__attribute__((used)) static int proc_pid_permission(struct inode *inode, int mask)
{
	struct pid_namespace *pid = proc_pid_ns(inode);
	struct task_struct *task;
	bool has_perms;

	task = get_proc_task(inode);
	if (!task)
		return -ESRCH;
	has_perms = has_pid_permissions(pid, task, HIDEPID_NO_ACCESS);
	put_task_struct(task);

	if (!has_perms) {
		if (pid->hide_pid == HIDEPID_INVISIBLE) {
			/*
			 * Let's make getdents(), stat(), and open()
			 * consistent with each other.  If a process
			 * may not stat() a file, it shouldn't be seen
			 * in procfs at all.
			 */
			return -ENOENT;
		}

		return -EPERM;
	}
	return generic_permission(inode, mask);
}