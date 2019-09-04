#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
typedef  int ext4_group_t ;
struct TYPE_3__ {int /*<<< orphan*/  s_es; } ;

/* Variables and functions */
 unsigned int EXT4_BLOCKS_PER_GROUP (struct super_block*) ; 
 unsigned int EXT4_NUM_B2C (TYPE_1__*,unsigned int) ; 
 TYPE_1__* EXT4_SB (struct super_block*) ; 
 unsigned int ext4_blocks_count (int /*<<< orphan*/ ) ; 
 int ext4_get_groups_count (struct super_block*) ; 
 unsigned int ext4_group_first_block_no (struct super_block*,int) ; 

__attribute__((used)) static unsigned int num_clusters_in_group(struct super_block *sb,
					  ext4_group_t block_group)
{
	unsigned int blocks;

	if (block_group == ext4_get_groups_count(sb) - 1) {
		/*
		 * Even though mke2fs always initializes the first and
		 * last group, just in case some other tool was used,
		 * we need to make sure we calculate the right free
		 * blocks.
		 */
		blocks = ext4_blocks_count(EXT4_SB(sb)->s_es) -
			ext4_group_first_block_no(sb, block_group);
	} else
		blocks = EXT4_BLOCKS_PER_GROUP(sb);
	return EXT4_NUM_B2C(EXT4_SB(sb), blocks);
}