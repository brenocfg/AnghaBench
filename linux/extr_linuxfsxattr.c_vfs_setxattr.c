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
struct inode {int dummy; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAY_WRITE ; 
 int __vfs_setxattr_noperm (struct dentry*,char const*,void const*,size_t,int) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int security_inode_setxattr (struct dentry*,char const*,void const*,size_t,int) ; 
 int xattr_permission (struct inode*,char const*,int /*<<< orphan*/ ) ; 

int
vfs_setxattr(struct dentry *dentry, const char *name, const void *value,
		size_t size, int flags)
{
	struct inode *inode = dentry->d_inode;
	int error;

	error = xattr_permission(inode, name, MAY_WRITE);
	if (error)
		return error;

	inode_lock(inode);
	error = security_inode_setxattr(dentry, name, value, size, flags);
	if (error)
		goto out;

	error = __vfs_setxattr_noperm(dentry, name, value, size, flags);

out:
	inode_unlock(inode);
	return error;
}