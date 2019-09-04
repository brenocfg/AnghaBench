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
struct f2fs_sb_info {int /*<<< orphan*/  total_valid_block_count; } ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */

__attribute__((used)) static inline block_t valid_user_blocks(struct f2fs_sb_info *sbi)
{
	return sbi->total_valid_block_count;
}