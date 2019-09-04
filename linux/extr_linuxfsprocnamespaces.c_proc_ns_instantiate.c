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
struct proc_ns_operations {int dummy; } ;
struct proc_inode {struct proc_ns_operations const* ns_ops; } ;
struct inode {int /*<<< orphan*/ * i_op; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct proc_inode* PROC_I (struct inode*) ; 
 int S_IFLNK ; 
 int S_IRWXUGO ; 
 int /*<<< orphan*/  d_set_d_op (struct dentry*,int /*<<< orphan*/ *) ; 
 struct dentry* d_splice_alias (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  pid_dentry_operations ; 
 int /*<<< orphan*/  pid_update_inode (struct task_struct*,struct inode*) ; 
 int /*<<< orphan*/  proc_ns_link_inode_operations ; 
 struct inode* proc_pid_make_inode (int /*<<< orphan*/ ,struct task_struct*,int) ; 

__attribute__((used)) static struct dentry *proc_ns_instantiate(struct dentry *dentry,
	struct task_struct *task, const void *ptr)
{
	const struct proc_ns_operations *ns_ops = ptr;
	struct inode *inode;
	struct proc_inode *ei;

	inode = proc_pid_make_inode(dentry->d_sb, task, S_IFLNK | S_IRWXUGO);
	if (!inode)
		return ERR_PTR(-ENOENT);

	ei = PROC_I(inode);
	inode->i_op = &proc_ns_link_inode_operations;
	ei->ns_ops = ns_ops;
	pid_update_inode(task, inode);

	d_set_d_op(dentry, &pid_dentry_operations);
	return d_splice_alias(inode, dentry);
}