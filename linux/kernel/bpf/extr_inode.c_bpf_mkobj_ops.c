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
typedef  int /*<<< orphan*/  umode_t ;
struct inode_operations {int dummy; } ;
struct inode {void* i_private; struct file_operations const* i_fop; struct inode_operations const* i_op; int /*<<< orphan*/  i_sb; } ;
struct file_operations {int dummy; } ;
struct dentry {TYPE_1__* d_parent; } ;
struct TYPE_2__ {struct inode* d_inode; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  bpf_dentry_finalize (struct dentry*,struct inode*,struct inode*) ; 
 struct inode* bpf_get_inode (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bpf_mkobj_ops(struct dentry *dentry, umode_t mode, void *raw,
			 const struct inode_operations *iops,
			 const struct file_operations *fops)
{
	struct inode *dir = dentry->d_parent->d_inode;
	struct inode *inode = bpf_get_inode(dir->i_sb, dir, mode);
	if (IS_ERR(inode))
		return PTR_ERR(inode);

	inode->i_op = iops;
	inode->i_fop = fops;
	inode->i_private = raw;

	bpf_dentry_finalize(dentry, inode, dir);
	return 0;
}