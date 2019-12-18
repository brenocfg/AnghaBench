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
typedef  int /*<<< orphan*/  umode_t ;
struct inode {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ DUMMY_ENCRYPTION_ENABLED (struct f2fs_sb_info*) ; 
 int EIO ; 
 int ENOSPC ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 scalar_t__ IS_ENCRYPTED (struct inode*) ; 
 int __f2fs_tmpfile (struct inode*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f2fs_cp_error (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_is_checkpoint_ready (struct f2fs_sb_info*) ; 
 int fscrypt_get_encryption_info (struct inode*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int f2fs_tmpfile(struct inode *dir, struct dentry *dentry, umode_t mode)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(dir);

	if (unlikely(f2fs_cp_error(sbi)))
		return -EIO;
	if (!f2fs_is_checkpoint_ready(sbi))
		return -ENOSPC;

	if (IS_ENCRYPTED(dir) || DUMMY_ENCRYPTION_ENABLED(sbi)) {
		int err = fscrypt_get_encryption_info(dir);
		if (err)
			return err;
	}

	return __f2fs_tmpfile(dir, dentry, mode, NULL);
}