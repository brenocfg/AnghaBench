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
struct inode {int dummy; } ;
struct f2fs_sb_info {int /*<<< orphan*/ * inode_lock; int /*<<< orphan*/ * inode_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  gdirty_list; } ;

/* Variables and functions */
 size_t DIRTY_META ; 
 int /*<<< orphan*/  F2FS_DIRTY_IMETA ; 
 TYPE_1__* F2FS_I (struct inode*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  FI_DIRTY_INODE ; 
 int /*<<< orphan*/  inc_page_count (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_inode_flag_set (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stat_inc_dirty_inode (struct f2fs_sb_info*,size_t) ; 

int f2fs_inode_dirtied(struct inode *inode, bool sync)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	int ret = 0;

	spin_lock(&sbi->inode_lock[DIRTY_META]);
	if (is_inode_flag_set(inode, FI_DIRTY_INODE)) {
		ret = 1;
	} else {
		set_inode_flag(inode, FI_DIRTY_INODE);
		stat_inc_dirty_inode(sbi, DIRTY_META);
	}
	if (sync && list_empty(&F2FS_I(inode)->gdirty_list)) {
		list_add_tail(&F2FS_I(inode)->gdirty_list,
				&sbi->inode_list[DIRTY_META]);
		inc_page_count(sbi, F2FS_DIRTY_IMETA);
	}
	spin_unlock(&sbi->inode_lock[DIRTY_META]);
	return ret;
}