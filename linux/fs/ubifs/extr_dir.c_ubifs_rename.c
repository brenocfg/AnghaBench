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
struct ubifs_info {int dummy; } ;
struct inode {TYPE_1__* i_sb; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {struct ubifs_info* s_fs_info; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int RENAME_EXCHANGE ; 
 unsigned int RENAME_NOREPLACE ; 
 unsigned int RENAME_WHITEOUT ; 
 int do_rename (struct inode*,struct dentry*,struct inode*,struct dentry*,unsigned int) ; 
 int fscrypt_prepare_rename (struct inode*,struct dentry*,struct inode*,struct dentry*,unsigned int) ; 
 int /*<<< orphan*/  inode_is_locked (struct inode*) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 int ubifs_xrename (struct inode*,struct dentry*,struct inode*,struct dentry*) ; 

__attribute__((used)) static int ubifs_rename(struct inode *old_dir, struct dentry *old_dentry,
			struct inode *new_dir, struct dentry *new_dentry,
			unsigned int flags)
{
	int err;
	struct ubifs_info *c = old_dir->i_sb->s_fs_info;

	if (flags & ~(RENAME_NOREPLACE | RENAME_WHITEOUT | RENAME_EXCHANGE))
		return -EINVAL;

	ubifs_assert(c, inode_is_locked(old_dir));
	ubifs_assert(c, inode_is_locked(new_dir));

	err = fscrypt_prepare_rename(old_dir, old_dentry, new_dir, new_dentry,
				     flags);
	if (err)
		return err;

	if (flags & RENAME_EXCHANGE)
		return ubifs_xrename(old_dir, old_dentry, new_dir, new_dentry);

	return do_rename(old_dir, old_dentry, new_dir, new_dentry, flags);
}