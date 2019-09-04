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
struct f2fs_sb_info {scalar_t__ last_valid_block_count; scalar_t__ user_block_count; int /*<<< orphan*/  alloc_valid_block_count; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 scalar_t__ percpu_counter_sum_positive (int /*<<< orphan*/ *) ; 

bool f2fs_space_for_roll_forward(struct f2fs_sb_info *sbi)
{
	s64 nalloc = percpu_counter_sum_positive(&sbi->alloc_valid_block_count);

	if (sbi->last_valid_block_count + nalloc > sbi->user_block_count)
		return false;
	return true;
}