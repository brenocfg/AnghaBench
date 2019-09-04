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
 int ESRCH ; 
 int MAY_EXEC ; 
 int /*<<< orphan*/  current ; 
 int generic_permission (struct inode*,int) ; 
 struct task_struct* get_proc_task (struct inode*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int same_thread_group (int /*<<< orphan*/ ,struct task_struct*) ; 

__attribute__((used)) static int proc_tid_comm_permission(struct inode *inode, int mask)
{
	bool is_same_tgroup;
	struct task_struct *task;

	task = get_proc_task(inode);
	if (!task)
		return -ESRCH;
	is_same_tgroup = same_thread_group(current, task);
	put_task_struct(task);

	if (likely(is_same_tgroup && !(mask & MAY_EXEC))) {
		/* This file (/proc/<pid>/task/<tid>/comm) can always be
		 * read or written by the members of the corresponding
		 * thread group.
		 */
		return 0;
	}

	return generic_permission(inode, mask);
}