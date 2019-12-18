#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  proc_get_link; } ;
struct proc_inode {TYPE_1__ op; int /*<<< orphan*/  fd; } ;
struct inode {int i_size; int /*<<< orphan*/ * i_op; } ;
struct fd_data {int /*<<< orphan*/  mode; int /*<<< orphan*/  fd; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct proc_inode* PROC_I (struct inode*) ; 
 int /*<<< orphan*/  S_IFLNK ; 
 int /*<<< orphan*/  d_set_d_op (struct dentry*,int /*<<< orphan*/ *) ; 
 struct dentry* d_splice_alias (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  proc_fd_link ; 
 int /*<<< orphan*/  proc_pid_link_inode_operations ; 
 struct inode* proc_pid_make_inode (int /*<<< orphan*/ ,struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tid_fd_dentry_operations ; 
 int /*<<< orphan*/  tid_fd_update_inode (struct task_struct*,struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *proc_fd_instantiate(struct dentry *dentry,
	struct task_struct *task, const void *ptr)
{
	const struct fd_data *data = ptr;
	struct proc_inode *ei;
	struct inode *inode;

	inode = proc_pid_make_inode(dentry->d_sb, task, S_IFLNK);
	if (!inode)
		return ERR_PTR(-ENOENT);

	ei = PROC_I(inode);
	ei->fd = data->fd;

	inode->i_op = &proc_pid_link_inode_operations;
	inode->i_size = 64;

	ei->op.proc_get_link = proc_fd_link;
	tid_fd_update_inode(task, inode, data->mode);

	d_set_d_op(dentry, &tid_fd_dentry_operations);
	return d_splice_alias(inode, dentry);
}