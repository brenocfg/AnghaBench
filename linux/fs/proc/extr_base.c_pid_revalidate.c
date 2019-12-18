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
struct dentry {int dummy; } ;

/* Variables and functions */
 int ECHILD ; 
 unsigned int LOOKUP_RCU ; 
 struct inode* d_inode (struct dentry*) ; 
 struct task_struct* get_proc_task (struct inode*) ; 
 int /*<<< orphan*/  pid_update_inode (struct task_struct*,struct inode*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 

__attribute__((used)) static int pid_revalidate(struct dentry *dentry, unsigned int flags)
{
	struct inode *inode;
	struct task_struct *task;

	if (flags & LOOKUP_RCU)
		return -ECHILD;

	inode = d_inode(dentry);
	task = get_proc_task(inode);

	if (task) {
		pid_update_inode(task, inode);
		put_task_struct(task);
		return 1;
	}
	return 0;
}