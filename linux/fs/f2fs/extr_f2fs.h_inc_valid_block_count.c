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
struct f2fs_sb_info {scalar_t__ total_valid_block_count; scalar_t__ user_block_count; scalar_t__ current_reserved_blocks; scalar_t__ unusable_block_count; int /*<<< orphan*/  alloc_valid_block_count; int /*<<< orphan*/  stat_lock; } ;
typedef  scalar_t__ block_t ;
typedef  scalar_t__ blkcnt_t ;
struct TYPE_2__ {scalar_t__ root_reserved_blocks; } ;

/* Variables and functions */
 int ENOSPC ; 
 TYPE_1__ F2FS_OPTION (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  FAULT_BLOCK ; 
 int /*<<< orphan*/  SBI_CP_DISABLED ; 
 int /*<<< orphan*/  __allow_reserved_blocks (struct f2fs_sb_info*,struct inode*,int) ; 
 int /*<<< orphan*/  dquot_release_reservation_block (struct inode*,scalar_t__) ; 
 int dquot_reserve_block (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  f2fs_i_blocks_write (struct inode*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  f2fs_show_injection_info (int /*<<< orphan*/ ) ; 
 scalar_t__ is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  percpu_counter_add (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  percpu_counter_sub (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_to_inject (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (scalar_t__) ; 

__attribute__((used)) static inline int inc_valid_block_count(struct f2fs_sb_info *sbi,
				 struct inode *inode, blkcnt_t *count)
{
	blkcnt_t diff = 0, release = 0;
	block_t avail_user_block_count;
	int ret;

	ret = dquot_reserve_block(inode, *count);
	if (ret)
		return ret;

	if (time_to_inject(sbi, FAULT_BLOCK)) {
		f2fs_show_injection_info(FAULT_BLOCK);
		release = *count;
		goto release_quota;
	}

	/*
	 * let's increase this in prior to actual block count change in order
	 * for f2fs_sync_file to avoid data races when deciding checkpoint.
	 */
	percpu_counter_add(&sbi->alloc_valid_block_count, (*count));

	spin_lock(&sbi->stat_lock);
	sbi->total_valid_block_count += (block_t)(*count);
	avail_user_block_count = sbi->user_block_count -
					sbi->current_reserved_blocks;

	if (!__allow_reserved_blocks(sbi, inode, true))
		avail_user_block_count -= F2FS_OPTION(sbi).root_reserved_blocks;
	if (unlikely(is_sbi_flag_set(sbi, SBI_CP_DISABLED))) {
		if (avail_user_block_count > sbi->unusable_block_count)
			avail_user_block_count -= sbi->unusable_block_count;
		else
			avail_user_block_count = 0;
	}
	if (unlikely(sbi->total_valid_block_count > avail_user_block_count)) {
		diff = sbi->total_valid_block_count - avail_user_block_count;
		if (diff > *count)
			diff = *count;
		*count -= diff;
		release = diff;
		sbi->total_valid_block_count -= diff;
		if (!*count) {
			spin_unlock(&sbi->stat_lock);
			goto enospc;
		}
	}
	spin_unlock(&sbi->stat_lock);

	if (unlikely(release)) {
		percpu_counter_sub(&sbi->alloc_valid_block_count, release);
		dquot_release_reservation_block(inode, release);
	}
	f2fs_i_blocks_write(inode, *count, true, true);
	return 0;

enospc:
	percpu_counter_sub(&sbi->alloc_valid_block_count, release);
release_quota:
	dquot_release_reservation_block(inode, release);
	return -ENOSPC;
}