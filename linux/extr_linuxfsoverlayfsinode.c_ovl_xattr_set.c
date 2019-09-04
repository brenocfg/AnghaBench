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
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int XATTR_REPLACE ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int ovl_copy_up (struct dentry*) ; 
 int /*<<< orphan*/  ovl_copyattr (int /*<<< orphan*/ ,struct inode*) ; 
 struct dentry* ovl_dentry_lower (struct dentry*) ; 
 struct dentry* ovl_dentry_upper (struct dentry*) ; 
 int /*<<< orphan*/  ovl_drop_write (struct dentry*) ; 
 struct dentry* ovl_i_dentry_upper (struct inode*) ; 
 struct cred* ovl_override_creds (int /*<<< orphan*/ ) ; 
 int ovl_want_write (struct dentry*) ; 
 int /*<<< orphan*/  revert_creds (struct cred const*) ; 
 int vfs_getxattr (struct dentry*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vfs_removexattr (struct dentry*,char const*) ; 
 int vfs_setxattr (struct dentry*,char const*,void const*,size_t,int) ; 

int ovl_xattr_set(struct dentry *dentry, struct inode *inode, const char *name,
		  const void *value, size_t size, int flags)
{
	int err;
	struct dentry *upperdentry = ovl_i_dentry_upper(inode);
	struct dentry *realdentry = upperdentry ?: ovl_dentry_lower(dentry);
	const struct cred *old_cred;

	err = ovl_want_write(dentry);
	if (err)
		goto out;

	if (!value && !upperdentry) {
		err = vfs_getxattr(realdentry, name, NULL, 0);
		if (err < 0)
			goto out_drop_write;
	}

	if (!upperdentry) {
		err = ovl_copy_up(dentry);
		if (err)
			goto out_drop_write;

		realdentry = ovl_dentry_upper(dentry);
	}

	old_cred = ovl_override_creds(dentry->d_sb);
	if (value)
		err = vfs_setxattr(realdentry, name, value, size, flags);
	else {
		WARN_ON(flags != XATTR_REPLACE);
		err = vfs_removexattr(realdentry, name);
	}
	revert_creds(old_cred);

	/* copy c/mtime */
	ovl_copyattr(d_inode(realdentry), inode);

out_drop_write:
	ovl_drop_write(dentry);
out:
	return err;
}