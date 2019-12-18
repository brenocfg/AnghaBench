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
struct ext2_sb_info {unsigned int s_sb_block; TYPE_1__* s_es; } ;
typedef  unsigned int ext2_fsblk_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_blocks_count; int /*<<< orphan*/  s_first_data_block; } ;

/* Variables and functions */
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 

int ext2_data_block_valid(struct ext2_sb_info *sbi, ext2_fsblk_t start_blk,
			  unsigned int count)
{
	if ((start_blk <= le32_to_cpu(sbi->s_es->s_first_data_block)) ||
	    (start_blk + count - 1 < start_blk) ||
	    (start_blk + count - 1 >= le32_to_cpu(sbi->s_es->s_blocks_count)))
		return 0;

	/* Ensure we do not step over superblock */
	if ((start_blk <= sbi->s_sb_block) &&
	    (start_blk + count - 1 >= sbi->s_sb_block))
		return 0;

	return 1;
}