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
struct writeback_control {scalar_t__ nr_to_write; } ;
struct inode {scalar_t__ i_ino; } ;
struct f2fs_sb_info {int dummy; } ;

/* Variables and functions */
 int ENOSPC ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 scalar_t__ F2FS_META_INO (struct f2fs_sb_info*) ; 
 scalar_t__ F2FS_NODE_INO (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  FI_DIRTY_INODE ; 
 int /*<<< orphan*/  f2fs_balance_fs (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  f2fs_is_checkpoint_ready (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_update_inode_page (struct inode*) ; 
 int /*<<< orphan*/  is_inode_flag_set (struct inode*,int /*<<< orphan*/ ) ; 

int f2fs_write_inode(struct inode *inode, struct writeback_control *wbc)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);

	if (inode->i_ino == F2FS_NODE_INO(sbi) ||
			inode->i_ino == F2FS_META_INO(sbi))
		return 0;

	if (!is_inode_flag_set(inode, FI_DIRTY_INODE))
		return 0;

	if (!f2fs_is_checkpoint_ready(sbi))
		return -ENOSPC;

	/*
	 * We need to balance fs here to prevent from producing dirty node pages
	 * during the urgent cleaning time when runing out of free sections.
	 */
	f2fs_update_inode_page(inode);
	if (wbc && wbc->nr_to_write)
		f2fs_balance_fs(sbi, true);
	return 0;
}