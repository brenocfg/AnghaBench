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
struct f2fs_sb_info {scalar_t__ total_valid_block_count; scalar_t__ current_reserved_blocks; scalar_t__ user_block_count; int total_valid_node_count; unsigned int total_node_count; int /*<<< orphan*/  alloc_valid_block_count; int /*<<< orphan*/  stat_lock; } ;
typedef  scalar_t__ block_t ;
struct TYPE_2__ {scalar_t__ root_reserved_blocks; } ;

/* Variables and functions */
 int ENOSPC ; 
 TYPE_1__ F2FS_OPTION (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  FAULT_BLOCK ; 
 int /*<<< orphan*/  __allow_reserved_blocks (struct f2fs_sb_info*,struct inode*,int) ; 
 int /*<<< orphan*/  dquot_release_reservation_block (struct inode*,int) ; 
 int dquot_reserve_block (struct inode*,int) ; 
 int /*<<< orphan*/  f2fs_i_blocks_write (struct inode*,int,int,int) ; 
 int /*<<< orphan*/  f2fs_mark_inode_dirty_sync (struct inode*,int) ; 
 int /*<<< orphan*/  f2fs_show_injection_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  percpu_counter_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_to_inject (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int inc_valid_node_count(struct f2fs_sb_info *sbi,
					struct inode *inode, bool is_inode)
{
	block_t	valid_block_count;
	unsigned int valid_node_count;
	bool quota = inode && !is_inode;

	if (quota) {
		int ret = dquot_reserve_block(inode, 1);
		if (ret)
			return ret;
	}

	if (time_to_inject(sbi, FAULT_BLOCK)) {
		f2fs_show_injection_info(FAULT_BLOCK);
		goto enospc;
	}

	spin_lock(&sbi->stat_lock);

	valid_block_count = sbi->total_valid_block_count +
					sbi->current_reserved_blocks + 1;

	if (!__allow_reserved_blocks(sbi, inode, false))
		valid_block_count += F2FS_OPTION(sbi).root_reserved_blocks;

	if (unlikely(valid_block_count > sbi->user_block_count)) {
		spin_unlock(&sbi->stat_lock);
		goto enospc;
	}

	valid_node_count = sbi->total_valid_node_count + 1;
	if (unlikely(valid_node_count > sbi->total_node_count)) {
		spin_unlock(&sbi->stat_lock);
		goto enospc;
	}

	sbi->total_valid_node_count++;
	sbi->total_valid_block_count++;
	spin_unlock(&sbi->stat_lock);

	if (inode) {
		if (is_inode)
			f2fs_mark_inode_dirty_sync(inode, true);
		else
			f2fs_i_blocks_write(inode, 1, true, true);
	}

	percpu_counter_inc(&sbi->alloc_valid_block_count);
	return 0;

enospc:
	if (quota)
		dquot_release_reservation_block(inode, 1);
	return -ENOSPC;
}