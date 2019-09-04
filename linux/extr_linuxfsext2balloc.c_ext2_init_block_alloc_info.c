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
struct inode {struct super_block* i_sb; } ;
struct ext2_reserve_window_node {scalar_t__ rsv_alloc_hit; scalar_t__ rsv_goal_size; void* rsv_end; void* rsv_start; } ;
struct ext2_inode_info {struct ext2_block_alloc_info* i_block_alloc_info; } ;
struct ext2_block_alloc_info {scalar_t__ last_alloc_physical_block; scalar_t__ last_alloc_logical_block; struct ext2_reserve_window_node rsv_window_node; } ;

/* Variables and functions */
 scalar_t__ EXT2_DEFAULT_RESERVE_BLOCKS ; 
 struct ext2_inode_info* EXT2_I (struct inode*) ; 
 void* EXT2_RESERVE_WINDOW_NOT_ALLOCATED ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  RESERVATION ; 
 struct ext2_block_alloc_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_opt (struct super_block*,int /*<<< orphan*/ ) ; 

void ext2_init_block_alloc_info(struct inode *inode)
{
	struct ext2_inode_info *ei = EXT2_I(inode);
	struct ext2_block_alloc_info *block_i;
	struct super_block *sb = inode->i_sb;

	block_i = kmalloc(sizeof(*block_i), GFP_NOFS);
	if (block_i) {
		struct ext2_reserve_window_node *rsv = &block_i->rsv_window_node;

		rsv->rsv_start = EXT2_RESERVE_WINDOW_NOT_ALLOCATED;
		rsv->rsv_end = EXT2_RESERVE_WINDOW_NOT_ALLOCATED;

	 	/*
		 * if filesystem is mounted with NORESERVATION, the goal
		 * reservation window size is set to zero to indicate
		 * block reservation is off
		 */
		if (!test_opt(sb, RESERVATION))
			rsv->rsv_goal_size = 0;
		else
			rsv->rsv_goal_size = EXT2_DEFAULT_RESERVE_BLOCKS;
		rsv->rsv_alloc_hit = 0;
		block_i->last_alloc_logical_block = 0;
		block_i->last_alloc_physical_block = 0;
	}
	ei->i_block_alloc_info = block_i;
}