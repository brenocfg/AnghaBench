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
struct super_block {int dummy; } ;
struct ext2_reserve_window {scalar_t__ _rsv_start; scalar_t__ _rsv_end; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
typedef  scalar_t__ ext2_grpblk_t ;
typedef  scalar_t__ ext2_fsblk_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ EXT2_BLOCKS_PER_GROUP (struct super_block*) ; 
 int /*<<< orphan*/  EXT2_SB (struct super_block*) ; 
 scalar_t__ ext2_group_first_block_no (struct super_block*,int) ; 
 scalar_t__ ext2_set_bit_atomic (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2_test_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ find_next_usable_block (scalar_t__,struct buffer_head*,scalar_t__) ; 
 int /*<<< orphan*/  sb_bgl_lock (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ext2_try_to_allocate(struct super_block *sb, int group,
			struct buffer_head *bitmap_bh, ext2_grpblk_t grp_goal,
			unsigned long *count,
			struct ext2_reserve_window *my_rsv)
{
	ext2_fsblk_t group_first_block;
       	ext2_grpblk_t start, end;
	unsigned long num = 0;

	/* we do allocation within the reservation window if we have a window */
	if (my_rsv) {
		group_first_block = ext2_group_first_block_no(sb, group);
		if (my_rsv->_rsv_start >= group_first_block)
			start = my_rsv->_rsv_start - group_first_block;
		else
			/* reservation window cross group boundary */
			start = 0;
		end = my_rsv->_rsv_end - group_first_block + 1;
		if (end > EXT2_BLOCKS_PER_GROUP(sb))
			/* reservation window crosses group boundary */
			end = EXT2_BLOCKS_PER_GROUP(sb);
		if ((start <= grp_goal) && (grp_goal < end))
			start = grp_goal;
		else
			grp_goal = -1;
	} else {
		if (grp_goal > 0)
			start = grp_goal;
		else
			start = 0;
		end = EXT2_BLOCKS_PER_GROUP(sb);
	}

	BUG_ON(start > EXT2_BLOCKS_PER_GROUP(sb));

repeat:
	if (grp_goal < 0) {
		grp_goal = find_next_usable_block(start, bitmap_bh, end);
		if (grp_goal < 0)
			goto fail_access;
		if (!my_rsv) {
			int i;

			for (i = 0; i < 7 && grp_goal > start &&
					!ext2_test_bit(grp_goal - 1,
					     		bitmap_bh->b_data);
			     		i++, grp_goal--)
				;
		}
	}
	start = grp_goal;

	if (ext2_set_bit_atomic(sb_bgl_lock(EXT2_SB(sb), group), grp_goal,
			       				bitmap_bh->b_data)) {
		/*
		 * The block was allocated by another thread, or it was
		 * allocated and then freed by another thread
		 */
		start++;
		grp_goal++;
		if (start >= end)
			goto fail_access;
		goto repeat;
	}
	num++;
	grp_goal++;
	while (num < *count && grp_goal < end
		&& !ext2_set_bit_atomic(sb_bgl_lock(EXT2_SB(sb), group),
					grp_goal, bitmap_bh->b_data)) {
		num++;
		grp_goal++;
	}
	*count = num;
	return grp_goal - num;
fail_access:
	*count = num;
	return -1;
}