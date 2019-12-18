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
struct ext2_block_alloc_info {int last_alloc_logical_block; scalar_t__ last_alloc_physical_block; } ;
typedef  scalar_t__ ext2_fsblk_t ;
struct TYPE_2__ {struct ext2_block_alloc_info* i_block_alloc_info; } ;
typedef  int /*<<< orphan*/  Indirect ;

/* Variables and functions */
 TYPE_1__* EXT2_I (struct inode*) ; 
 scalar_t__ ext2_find_near (struct inode*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline ext2_fsblk_t ext2_find_goal(struct inode *inode, long block,
					  Indirect *partial)
{
	struct ext2_block_alloc_info *block_i;

	block_i = EXT2_I(inode)->i_block_alloc_info;

	/*
	 * try the heuristic for sequential allocation,
	 * failing that at least try to get decent locality.
	 */
	if (block_i && (block == block_i->last_alloc_logical_block + 1)
		&& (block_i->last_alloc_physical_block != 0)) {
		return block_i->last_alloc_physical_block + 1;
	}

	return ext2_find_near(inode, partial);
}