#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct f2fs_sb_info {int segs_per_sec; } ;
struct TYPE_4__ {unsigned int valid_blocks; } ;
struct TYPE_3__ {unsigned int valid_blocks; } ;

/* Variables and functions */
 TYPE_2__* get_sec_entry (struct f2fs_sb_info*,unsigned int) ; 
 TYPE_1__* get_seg_entry (struct f2fs_sb_info*,unsigned int) ; 

__attribute__((used)) static inline unsigned int get_valid_blocks(struct f2fs_sb_info *sbi,
				unsigned int segno, bool use_section)
{
	/*
	 * In order to get # of valid blocks in a section instantly from many
	 * segments, f2fs manages two counting structures separately.
	 */
	if (use_section && sbi->segs_per_sec > 1)
		return get_sec_entry(sbi, segno)->valid_blocks;
	else
		return get_seg_entry(sbi, segno)->valid_blocks;
}