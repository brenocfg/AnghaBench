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
typedef  int /*<<< orphan*/  umode_t ;
struct task_struct {int dummy; } ;
struct super_block {int dummy; } ;
struct proc_inode {int /*<<< orphan*/  pid; } ;
struct inode {int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIDTYPE_PID ; 
 struct proc_inode* PROC_I (struct inode*) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  get_next_ino () ; 
 int /*<<< orphan*/  get_task_pid (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  proc_def_inode_operations ; 
 int /*<<< orphan*/  security_task_to_inode (struct task_struct*,struct inode*) ; 
 int /*<<< orphan*/  task_dump_owner (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct inode *proc_pid_make_inode(struct super_block * sb,
				  struct task_struct *task, umode_t mode)
{
	struct inode * inode;
	struct proc_inode *ei;

	/* We need a new inode */

	inode = new_inode(sb);
	if (!inode)
		goto out;

	/* Common stuff */
	ei = PROC_I(inode);
	inode->i_mode = mode;
	inode->i_ino = get_next_ino();
	inode->i_mtime = inode->i_atime = inode->i_ctime = current_time(inode);
	inode->i_op = &proc_def_inode_operations;

	/*
	 * grab the reference to task.
	 */
	ei->pid = get_task_pid(task, PIDTYPE_PID);
	if (!ei->pid)
		goto out_unlock;

	task_dump_owner(task, 0, &inode->i_uid, &inode->i_gid);
	security_task_to_inode(task, inode);

out:
	return inode;

out_unlock:
	iput(inode);
	return NULL;
}