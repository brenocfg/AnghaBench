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
struct dentry {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int RENAME_EXCHANGE ; 
 unsigned int RENAME_NOREPLACE ; 
 unsigned int RENAME_WHITEOUT ; 
 int f2fs_cross_rename (struct inode*,struct dentry*,struct inode*,struct dentry*) ; 
 int f2fs_rename (struct inode*,struct dentry*,struct inode*,struct dentry*,unsigned int) ; 
 int fscrypt_prepare_rename (struct inode*,struct dentry*,struct inode*,struct dentry*,unsigned int) ; 

__attribute__((used)) static int f2fs_rename2(struct inode *old_dir, struct dentry *old_dentry,
			struct inode *new_dir, struct dentry *new_dentry,
			unsigned int flags)
{
	int err;

	if (flags & ~(RENAME_NOREPLACE | RENAME_EXCHANGE | RENAME_WHITEOUT))
		return -EINVAL;

	err = fscrypt_prepare_rename(old_dir, old_dentry, new_dir, new_dentry,
				     flags);
	if (err)
		return err;

	if (flags & RENAME_EXCHANGE) {
		return f2fs_cross_rename(old_dir, old_dentry,
					 new_dir, new_dentry);
	}
	/*
	 * VFS has already handled the new dentry existence case,
	 * here, we just deal with "RENAME_NOREPLACE" as regular rename.
	 */
	return f2fs_rename(old_dir, old_dentry, new_dir, new_dentry, flags);
}