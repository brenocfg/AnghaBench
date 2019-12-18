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
typedef  scalar_t__ ext2_grpblk_t ;
typedef  scalar_t__ ext2_fsblk_t ;

/* Variables and functions */
 scalar_t__ EXT2_BLOCKS_PER_GROUP (struct super_block*) ; 
 scalar_t__ ext2_group_first_block_no (struct super_block*,unsigned int) ; 

__attribute__((used)) static int
goal_in_my_reservation(struct ext2_reserve_window *rsv, ext2_grpblk_t grp_goal,
			unsigned int group, struct super_block * sb)
{
	ext2_fsblk_t group_first_block, group_last_block;

	group_first_block = ext2_group_first_block_no(sb, group);
	group_last_block = group_first_block + EXT2_BLOCKS_PER_GROUP(sb) - 1;

	if ((rsv->_rsv_start > group_last_block) ||
	    (rsv->_rsv_end < group_first_block))
		return 0;
	if ((grp_goal >= 0) && ((grp_goal + group_first_block < rsv->_rsv_start)
		|| (grp_goal + group_first_block > rsv->_rsv_end)))
		return 0;
	return 1;
}