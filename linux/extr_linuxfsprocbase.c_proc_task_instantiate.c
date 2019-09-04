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
struct inode {int /*<<< orphan*/  i_flags; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  S_IMMUTABLE ; 
 int S_IRUGO ; 
 int S_IXUGO ; 
 int /*<<< orphan*/  d_set_d_op (struct dentry*,int /*<<< orphan*/ *) ; 
 struct dentry* d_splice_alias (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  nlink_tid ; 
 int /*<<< orphan*/  pid_dentry_operations ; 
 int /*<<< orphan*/  pid_update_inode (struct task_struct*,struct inode*) ; 
 struct inode* proc_pid_make_inode (int /*<<< orphan*/ ,struct task_struct*,int) ; 
 int /*<<< orphan*/  proc_tid_base_inode_operations ; 
 int /*<<< orphan*/  proc_tid_base_operations ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *proc_task_instantiate(struct dentry *dentry,
	struct task_struct *task, const void *ptr)
{
	struct inode *inode;
	inode = proc_pid_make_inode(dentry->d_sb, task, S_IFDIR | S_IRUGO | S_IXUGO);
	if (!inode)
		return ERR_PTR(-ENOENT);

	inode->i_op = &proc_tid_base_inode_operations;
	inode->i_fop = &proc_tid_base_operations;
	inode->i_flags |= S_IMMUTABLE;

	set_nlink(inode, nlink_tid);
	pid_update_inode(task, inode);

	d_set_d_op(dentry, &pid_dentry_operations);
	return d_splice_alias(inode, dentry);
}