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
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_sem; int /*<<< orphan*/  i_xattr_sem; } ;

/* Variables and functions */
 int EIO ; 
 int ENOSPC ; 
 TYPE_1__* F2FS_I (struct inode*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  REQ_TIME ; 
 int __f2fs_setxattr (struct inode*,int,char const*,void const*,size_t,struct page*,int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int dquot_initialize (struct inode*) ; 
 int /*<<< orphan*/  f2fs_balance_fs (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  f2fs_cp_error (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_is_checkpoint_ready (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_lock_op (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_unlock_op (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_update_time (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int f2fs_setxattr(struct inode *inode, int index, const char *name,
				const void *value, size_t size,
				struct page *ipage, int flags)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	int err;

	if (unlikely(f2fs_cp_error(sbi)))
		return -EIO;
	if (!f2fs_is_checkpoint_ready(sbi))
		return -ENOSPC;

	err = dquot_initialize(inode);
	if (err)
		return err;

	/* this case is only from f2fs_init_inode_metadata */
	if (ipage)
		return __f2fs_setxattr(inode, index, name, value,
						size, ipage, flags);
	f2fs_balance_fs(sbi, true);

	f2fs_lock_op(sbi);
	/* protect xattr_ver */
	down_write(&F2FS_I(inode)->i_sem);
	down_write(&F2FS_I(inode)->i_xattr_sem);
	err = __f2fs_setxattr(inode, index, name, value, size, ipage, flags);
	up_write(&F2FS_I(inode)->i_xattr_sem);
	up_write(&F2FS_I(inode)->i_sem);
	f2fs_unlock_op(sbi);

	f2fs_update_time(sbi, REQ_TIME);
	return err;
}