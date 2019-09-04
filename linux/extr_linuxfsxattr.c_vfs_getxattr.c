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
typedef  int ssize_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MAY_READ ; 
 int /*<<< orphan*/  XATTR_SECURITY_PREFIX ; 
 int XATTR_SECURITY_PREFIX_LEN ; 
 int __vfs_getxattr (struct dentry*,struct inode*,char const*,void*,size_t) ; 
 int security_inode_getxattr (struct dentry*,char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,int) ; 
 int xattr_getsecurity (struct inode*,char const*,void*,size_t) ; 
 int xattr_permission (struct inode*,char const*,int /*<<< orphan*/ ) ; 

ssize_t
vfs_getxattr(struct dentry *dentry, const char *name, void *value, size_t size)
{
	struct inode *inode = dentry->d_inode;
	int error;

	error = xattr_permission(inode, name, MAY_READ);
	if (error)
		return error;

	error = security_inode_getxattr(dentry, name);
	if (error)
		return error;

	if (!strncmp(name, XATTR_SECURITY_PREFIX,
				XATTR_SECURITY_PREFIX_LEN)) {
		const char *suffix = name + XATTR_SECURITY_PREFIX_LEN;
		int ret = xattr_getsecurity(inode, suffix, value, size);
		/*
		 * Only overwrite the return value if a security module
		 * is actually active.
		 */
		if (ret == -EOPNOTSUPP)
			goto nolsm;
		return ret;
	}
nolsm:
	return __vfs_getxattr(dentry, inode, name, value, size);
}