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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct f2fs_sb_info {int dummy; } ;
struct f2fs_io_info {int /*<<< orphan*/  old_blkaddr; int /*<<< orphan*/  page; } ;

/* Variables and functions */
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 scalar_t__ IS_ATOMIC_WRITTEN_PAGE (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_NOQUOTA (struct inode*) ; 
 int /*<<< orphan*/  LFS ; 
 int /*<<< orphan*/  SBI_CP_DISABLED ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ f2fs_is_atomic_file (struct inode*) ; 
 scalar_t__ f2fs_is_checkpointed_data (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_cold_data (int /*<<< orphan*/ ) ; 
 scalar_t__ is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_opt (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

bool f2fs_should_update_outplace(struct inode *inode, struct f2fs_io_info *fio)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);

	if (test_opt(sbi, LFS))
		return true;
	if (S_ISDIR(inode->i_mode))
		return true;
	if (IS_NOQUOTA(inode))
		return true;
	if (f2fs_is_atomic_file(inode))
		return true;
	if (fio) {
		if (is_cold_data(fio->page))
			return true;
		if (IS_ATOMIC_WRITTEN_PAGE(fio->page))
			return true;
		if (unlikely(is_sbi_flag_set(sbi, SBI_CP_DISABLED) &&
			f2fs_is_checkpointed_data(sbi, fio->old_blkaddr)))
			return true;
	}
	return false;
}