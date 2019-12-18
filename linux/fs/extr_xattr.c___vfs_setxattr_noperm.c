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
struct inode {int i_opflags; int /*<<< orphan*/  i_flags; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int EOPNOTSUPP ; 
 int IOP_XATTR ; 
 int /*<<< orphan*/  S_NOSEC ; 
 int /*<<< orphan*/  XATTR_SECURITY_PREFIX ; 
 int XATTR_SECURITY_PREFIX_LEN ; 
 int __vfs_setxattr (struct dentry*,struct inode*,char const*,void const*,size_t,int) ; 
 int /*<<< orphan*/  fsnotify_xattr (struct dentry*) ; 
 int /*<<< orphan*/  is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  security_inode_post_setxattr (struct dentry*,char const*,void const*,size_t,int) ; 
 int security_inode_setsecurity (struct inode*,char const*,void const*,size_t,int) ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int __vfs_setxattr_noperm(struct dentry *dentry, const char *name,
		const void *value, size_t size, int flags)
{
	struct inode *inode = dentry->d_inode;
	int error = -EAGAIN;
	int issec = !strncmp(name, XATTR_SECURITY_PREFIX,
				   XATTR_SECURITY_PREFIX_LEN);

	if (issec)
		inode->i_flags &= ~S_NOSEC;
	if (inode->i_opflags & IOP_XATTR) {
		error = __vfs_setxattr(dentry, inode, name, value, size, flags);
		if (!error) {
			fsnotify_xattr(dentry);
			security_inode_post_setxattr(dentry, name, value,
						     size, flags);
		}
	} else {
		if (unlikely(is_bad_inode(inode)))
			return -EIO;
	}
	if (error == -EAGAIN) {
		error = -EOPNOTSUPP;

		if (issec) {
			const char *suffix = name + XATTR_SECURITY_PREFIX_LEN;

			error = security_inode_setsecurity(inode, suffix, value,
							   size, flags);
			if (!error)
				fsnotify_xattr(dentry);
		}
	}

	return error;
}