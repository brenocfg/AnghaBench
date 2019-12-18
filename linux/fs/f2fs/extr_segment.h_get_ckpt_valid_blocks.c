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
struct f2fs_sb_info {int dummy; } ;
struct TYPE_2__ {unsigned int ckpt_valid_blocks; } ;

/* Variables and functions */
 TYPE_1__* get_seg_entry (struct f2fs_sb_info*,unsigned int) ; 

__attribute__((used)) static inline unsigned int get_ckpt_valid_blocks(struct f2fs_sb_info *sbi,
				unsigned int segno)
{
	return get_seg_entry(sbi, segno)->ckpt_valid_blocks;
}