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
struct proc_inode {int /*<<< orphan*/  fd; } ;
struct inode {int /*<<< orphan*/ * i_fop; } ;
struct fd_data {int /*<<< orphan*/  fd; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct proc_inode* PROC_I (struct inode*) ; 
 int S_IFREG ; 
 int S_IRUSR ; 
 int /*<<< orphan*/  d_set_d_op (struct dentry*,int /*<<< orphan*/ *) ; 
 struct dentry* d_splice_alias (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  proc_fdinfo_file_operations ; 
 struct inode* proc_pid_make_inode (int /*<<< orphan*/ ,struct task_struct*,int) ; 
 int /*<<< orphan*/  tid_fd_dentry_operations ; 
 int /*<<< orphan*/  tid_fd_update_inode (struct task_struct*,struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *proc_fdinfo_instantiate(struct dentry *dentry,
	struct task_struct *task, const void *ptr)
{
	const struct fd_data *data = ptr;
	struct proc_inode *ei;
	struct inode *inode;

	inode = proc_pid_make_inode(dentry->d_sb, task, S_IFREG | S_IRUSR);
	if (!inode)
		return ERR_PTR(-ENOENT);

	ei = PROC_I(inode);
	ei->fd = data->fd;

	inode->i_fop = &proc_fdinfo_file_operations;
	tid_fd_update_inode(task, inode, 0);

	d_set_d_op(dentry, &tid_fd_dentry_operations);
	return d_splice_alias(inode, dentry);
}