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
struct kernfs_node {int dummy; } ;
struct inode {struct kernfs_node* i_private; } ;
struct iattr {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int __kernfs_setattr (struct kernfs_node*,struct iattr*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  kernfs_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setattr_copy (struct inode*,struct iattr*) ; 
 int setattr_prepare (struct dentry*,struct iattr*) ; 

int kernfs_iop_setattr(struct dentry *dentry, struct iattr *iattr)
{
	struct inode *inode = d_inode(dentry);
	struct kernfs_node *kn = inode->i_private;
	int error;

	if (!kn)
		return -EINVAL;

	mutex_lock(&kernfs_mutex);
	error = setattr_prepare(dentry, iattr);
	if (error)
		goto out;

	error = __kernfs_setattr(kn, iattr);
	if (error)
		goto out;

	/* this ignores size changes */
	setattr_copy(inode, iattr);

out:
	mutex_unlock(&kernfs_mutex);
	return error;
}