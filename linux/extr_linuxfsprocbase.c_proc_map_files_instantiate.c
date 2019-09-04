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
struct proc_inode {TYPE_1__ op; } ;
struct inode {int i_size; int /*<<< orphan*/ * i_op; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
typedef  int fmode_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 struct proc_inode* PROC_I (struct inode*) ; 
 int S_IFLNK ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  d_set_d_op (struct dentry*,int /*<<< orphan*/ *) ; 
 struct dentry* d_splice_alias (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  map_files_get_link ; 
 int /*<<< orphan*/  proc_map_files_link_inode_operations ; 
 struct inode* proc_pid_make_inode (int /*<<< orphan*/ ,struct task_struct*,int) ; 
 int /*<<< orphan*/  tid_map_files_dentry_operations ; 

__attribute__((used)) static struct dentry *
proc_map_files_instantiate(struct dentry *dentry,
			   struct task_struct *task, const void *ptr)
{
	fmode_t mode = (fmode_t)(unsigned long)ptr;
	struct proc_inode *ei;
	struct inode *inode;

	inode = proc_pid_make_inode(dentry->d_sb, task, S_IFLNK |
				    ((mode & FMODE_READ ) ? S_IRUSR : 0) |
				    ((mode & FMODE_WRITE) ? S_IWUSR : 0));
	if (!inode)
		return ERR_PTR(-ENOENT);

	ei = PROC_I(inode);
	ei->op.proc_get_link = map_files_get_link;

	inode->i_op = &proc_map_files_link_inode_operations;
	inode->i_size = 64;

	d_set_d_op(dentry, &tid_map_files_dentry_operations);
	return d_splice_alias(inode, dentry);
}