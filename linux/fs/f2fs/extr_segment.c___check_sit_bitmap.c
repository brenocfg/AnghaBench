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
struct seg_entry {scalar_t__ cur_valid_map; } ;
struct f2fs_sb_info {unsigned long blocks_per_seg; } ;
typedef  scalar_t__ block_t ;

/* Variables and functions */
 unsigned long GET_BLKOFF_FROM_SEG0 (struct f2fs_sb_info*,scalar_t__) ; 
 unsigned int GET_SEGNO (struct f2fs_sb_info*,scalar_t__) ; 
 scalar_t__ START_BLOCK (struct f2fs_sb_info*,unsigned int) ; 
 unsigned long __find_rev_next_bit (unsigned long*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int) ; 
 struct seg_entry* get_seg_entry (struct f2fs_sb_info*,unsigned int) ; 

__attribute__((used)) static void __check_sit_bitmap(struct f2fs_sb_info *sbi,
				block_t start, block_t end)
{
#ifdef CONFIG_F2FS_CHECK_FS
	struct seg_entry *sentry;
	unsigned int segno;
	block_t blk = start;
	unsigned long offset, size, max_blocks = sbi->blocks_per_seg;
	unsigned long *map;

	while (blk < end) {
		segno = GET_SEGNO(sbi, blk);
		sentry = get_seg_entry(sbi, segno);
		offset = GET_BLKOFF_FROM_SEG0(sbi, blk);

		if (end < START_BLOCK(sbi, segno + 1))
			size = GET_BLKOFF_FROM_SEG0(sbi, end);
		else
			size = max_blocks;
		map = (unsigned long *)(sentry->cur_valid_map);
		offset = __find_rev_next_bit(map, size, offset);
		f2fs_bug_on(sbi, offset != size);
		blk = START_BLOCK(sbi, segno + 1);
	}
#endif
}