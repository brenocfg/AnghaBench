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
 int __vfs_removexattr (struct dentry*,char const*) ; 
 int /*<<< orphan*/  evm_inode_post_removexattr (struct dentry*,char const*) ; 
 int /*<<< orphan*/  fsnotify_xattr (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int security_inode_removexattr (struct dentry*,char const*) ; 
 int xattr_permission (struct inode*,char const*,int /*<<< orphan*/ ) ; 

int
vfs_removexattr(struct dentry *dentry, const char *name)
{
	struct inode *inode = dentry->d_inode;
	int error;

	error = xattr_permission(inode, name, MAY_WRITE);
	if (error)
		return error;

	inode_lock(inode);
	error = security_inode_removexattr(dentry, name);
	if (error)
		goto out;

	error = __vfs_removexattr(dentry, name);

	if (!error) {
		fsnotify_xattr(dentry);
		evm_inode_post_removexattr(dentry, name);
	}

out:
	inode_unlock(inode);
	return error;
}