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
struct f2fs_sb_info {scalar_t__ user_block_count; } ;
typedef  scalar_t__ block_t ;

/* Variables and functions */
 scalar_t__ free_user_blocks (struct f2fs_sb_info*) ; 
 scalar_t__ limit_free_user_blocks (struct f2fs_sb_info*) ; 
 scalar_t__ limit_invalid_user_blocks (struct f2fs_sb_info*) ; 
 scalar_t__ written_block_count (struct f2fs_sb_info*) ; 

__attribute__((used)) static inline bool has_enough_invalid_blocks(struct f2fs_sb_info *sbi)
{
	block_t invalid_user_blocks = sbi->user_block_count -
					written_block_count(sbi);
	/*
	 * Background GC is triggered with the following conditions.
	 * 1. There are a number of invalid blocks.
	 * 2. There is not enough free space.
	 */
	if (invalid_user_blocks > limit_invalid_user_blocks(sbi) &&
			free_user_blocks(sbi) < limit_free_user_blocks(sbi))
		return true;
	return false;
}