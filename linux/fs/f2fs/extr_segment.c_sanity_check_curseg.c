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
struct seg_entry {int /*<<< orphan*/  cur_valid_map; } ;
struct f2fs_sb_info {unsigned int blocks_per_seg; } ;
struct curseg_info {unsigned int next_blkoff; scalar_t__ alloc_type; int /*<<< orphan*/  segno; } ;

/* Variables and functions */
 struct curseg_info* CURSEG_I (struct f2fs_sb_info*,int) ; 
 int EFSCORRUPTED ; 
 int NO_CHECK_TYPE ; 
 scalar_t__ SSR ; 
 int /*<<< orphan*/  f2fs_err (struct f2fs_sb_info*,char*,int,int /*<<< orphan*/ ,scalar_t__,unsigned int,unsigned int) ; 
 scalar_t__ f2fs_test_bit (unsigned int,int /*<<< orphan*/ ) ; 
 struct seg_entry* get_seg_entry (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sanity_check_curseg(struct f2fs_sb_info *sbi)
{
	int i;

	/*
	 * In LFS/SSR curseg, .next_blkoff should point to an unused blkaddr;
	 * In LFS curseg, all blkaddr after .next_blkoff should be unused.
	 */
	for (i = 0; i < NO_CHECK_TYPE; i++) {
		struct curseg_info *curseg = CURSEG_I(sbi, i);
		struct seg_entry *se = get_seg_entry(sbi, curseg->segno);
		unsigned int blkofs = curseg->next_blkoff;

		if (f2fs_test_bit(blkofs, se->cur_valid_map))
			goto out;

		if (curseg->alloc_type == SSR)
			continue;

		for (blkofs += 1; blkofs < sbi->blocks_per_seg; blkofs++) {
			if (!f2fs_test_bit(blkofs, se->cur_valid_map))
				continue;
out:
			f2fs_err(sbi,
				 "Current segment's next free block offset is inconsistent with bitmap, logtype:%u, segno:%u, type:%u, next_blkoff:%u, blkofs:%u",
				 i, curseg->segno, curseg->alloc_type,
				 curseg->next_blkoff, blkofs);
			return -EFSCORRUPTED;
		}
	}
	return 0;
}