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
struct super_block {int dummy; } ;
struct rb_root {int dummy; } ;
struct ext2_reserve_window_node {unsigned long rsv_goal_size; int rsv_start; int rsv_end; int rsv_alloc_hit; int /*<<< orphan*/  rsv_window; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  scalar_t__ ext2_grpblk_t ;
typedef  int ext2_fsblk_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_rsv_window_lock; struct rb_root s_rsv_window_root; } ;

/* Variables and functions */
 int EXT2_BLOCKS_PER_GROUP (struct super_block*) ; 
 unsigned long EXT2_MAX_RESERVE_BLOCKS ; 
 TYPE_1__* EXT2_SB (struct super_block*) ; 
 scalar_t__ bitmap_search_next_usable_block (int,struct buffer_head*,int) ; 
 int ext2_group_first_block_no (struct super_block*,unsigned int) ; 
 int find_next_reservable_window (struct ext2_reserve_window_node*,struct ext2_reserve_window_node*,struct super_block*,int,int) ; 
 int /*<<< orphan*/  rsv_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsv_window_remove (struct super_block*,struct ext2_reserve_window_node*) ; 
 struct ext2_reserve_window_node* search_reserve_window (struct rb_root*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int alloc_new_reservation(struct ext2_reserve_window_node *my_rsv,
		ext2_grpblk_t grp_goal, struct super_block *sb,
		unsigned int group, struct buffer_head *bitmap_bh)
{
	struct ext2_reserve_window_node *search_head;
	ext2_fsblk_t group_first_block, group_end_block, start_block;
	ext2_grpblk_t first_free_block;
	struct rb_root *fs_rsv_root = &EXT2_SB(sb)->s_rsv_window_root;
	unsigned long size;
	int ret;
	spinlock_t *rsv_lock = &EXT2_SB(sb)->s_rsv_window_lock;

	group_first_block = ext2_group_first_block_no(sb, group);
	group_end_block = group_first_block + (EXT2_BLOCKS_PER_GROUP(sb) - 1);

	if (grp_goal < 0)
		start_block = group_first_block;
	else
		start_block = grp_goal + group_first_block;

	size = my_rsv->rsv_goal_size;

	if (!rsv_is_empty(&my_rsv->rsv_window)) {
		/*
		 * if the old reservation is cross group boundary
		 * and if the goal is inside the old reservation window,
		 * we will come here when we just failed to allocate from
		 * the first part of the window. We still have another part
		 * that belongs to the next group. In this case, there is no
		 * point to discard our window and try to allocate a new one
		 * in this group(which will fail). we should
		 * keep the reservation window, just simply move on.
		 *
		 * Maybe we could shift the start block of the reservation
		 * window to the first block of next group.
		 */

		if ((my_rsv->rsv_start <= group_end_block) &&
				(my_rsv->rsv_end > group_end_block) &&
				(start_block >= my_rsv->rsv_start))
			return -1;

		if ((my_rsv->rsv_alloc_hit >
		     (my_rsv->rsv_end - my_rsv->rsv_start + 1) / 2)) {
			/*
			 * if the previously allocation hit ratio is
			 * greater than 1/2, then we double the size of
			 * the reservation window the next time,
			 * otherwise we keep the same size window
			 */
			size = size * 2;
			if (size > EXT2_MAX_RESERVE_BLOCKS)
				size = EXT2_MAX_RESERVE_BLOCKS;
			my_rsv->rsv_goal_size= size;
		}
	}

	spin_lock(rsv_lock);
	/*
	 * shift the search start to the window near the goal block
	 */
	search_head = search_reserve_window(fs_rsv_root, start_block);

	/*
	 * find_next_reservable_window() simply finds a reservable window
	 * inside the given range(start_block, group_end_block).
	 *
	 * To make sure the reservation window has a free bit inside it, we
	 * need to check the bitmap after we found a reservable window.
	 */
retry:
	ret = find_next_reservable_window(search_head, my_rsv, sb,
						start_block, group_end_block);

	if (ret == -1) {
		if (!rsv_is_empty(&my_rsv->rsv_window))
			rsv_window_remove(sb, my_rsv);
		spin_unlock(rsv_lock);
		return -1;
	}

	/*
	 * On success, find_next_reservable_window() returns the
	 * reservation window where there is a reservable space after it.
	 * Before we reserve this reservable space, we need
	 * to make sure there is at least a free block inside this region.
	 *
	 * Search the first free bit on the block bitmap.  Search starts from
	 * the start block of the reservable space we just found.
	 */
	spin_unlock(rsv_lock);
	first_free_block = bitmap_search_next_usable_block(
			my_rsv->rsv_start - group_first_block,
			bitmap_bh, group_end_block - group_first_block + 1);

	if (first_free_block < 0) {
		/*
		 * no free block left on the bitmap, no point
		 * to reserve the space. return failed.
		 */
		spin_lock(rsv_lock);
		if (!rsv_is_empty(&my_rsv->rsv_window))
			rsv_window_remove(sb, my_rsv);
		spin_unlock(rsv_lock);
		return -1;		/* failed */
	}

	start_block = first_free_block + group_first_block;
	/*
	 * check if the first free block is within the
	 * free space we just reserved
	 */
	if (start_block >= my_rsv->rsv_start && start_block <= my_rsv->rsv_end)
		return 0;		/* success */
	/*
	 * if the first free bit we found is out of the reservable space
	 * continue search for next reservable space,
	 * start from where the free block is,
	 * we also shift the list head to where we stopped last time
	 */
	search_head = my_rsv;
	spin_lock(rsv_lock);
	goto retry;
}