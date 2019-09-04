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
struct sit_info {scalar_t__ sit_base_addr; scalar_t__ sit_blocks; } ;
struct f2fs_sb_info {int dummy; } ;
typedef  scalar_t__ pgoff_t ;

/* Variables and functions */
 struct sit_info* SIT_I (struct f2fs_sb_info*) ; 

__attribute__((used)) static inline pgoff_t next_sit_addr(struct f2fs_sb_info *sbi,
						pgoff_t block_addr)
{
	struct sit_info *sit_i = SIT_I(sbi);
	block_addr -= sit_i->sit_base_addr;
	if (block_addr < sit_i->sit_blocks)
		block_addr += sit_i->sit_blocks;
	else
		block_addr -= sit_i->sit_blocks;

	return block_addr + sit_i->sit_base_addr;
}