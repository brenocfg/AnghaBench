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
struct seg_entry {int valid_blocks; scalar_t__ mtime; scalar_t__ ckpt_valid_blocks; int /*<<< orphan*/  ckpt_valid_map; int /*<<< orphan*/  discard_map; int /*<<< orphan*/  cur_valid_map; int /*<<< orphan*/  type; } ;
struct f2fs_sb_info {long blocks_per_seg; int segs_per_sec; int /*<<< orphan*/  discard_blks; int /*<<< orphan*/  sb; } ;
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_4__ {scalar_t__ max_mtime; int written_valid_blocks; } ;
struct TYPE_3__ {int valid_blocks; } ;

/* Variables and functions */
 unsigned int GET_BLKOFF_FROM_SEG0 (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 unsigned int GET_SEGNO (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_NODESEG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 TYPE_2__* SIT_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  __mark_sit_entry_dirty (struct f2fs_sb_info*,unsigned int) ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  f2fs_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int f2fs_test_and_clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int f2fs_test_and_set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_test_bit (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ get_mtime (struct f2fs_sb_info*,int) ; 
 TYPE_1__* get_sec_entry (struct f2fs_sb_info*,unsigned int) ; 
 struct seg_entry* get_seg_entry (struct f2fs_sb_info*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void update_sit_entry(struct f2fs_sb_info *sbi, block_t blkaddr, int del)
{
	struct seg_entry *se;
	unsigned int segno, offset;
	long int new_vblocks;
	bool exist;
#ifdef CONFIG_F2FS_CHECK_FS
	bool mir_exist;
#endif

	segno = GET_SEGNO(sbi, blkaddr);

	se = get_seg_entry(sbi, segno);
	new_vblocks = se->valid_blocks + del;
	offset = GET_BLKOFF_FROM_SEG0(sbi, blkaddr);

	f2fs_bug_on(sbi, (new_vblocks >> (sizeof(unsigned short) << 3) ||
				(new_vblocks > sbi->blocks_per_seg)));

	se->valid_blocks = new_vblocks;
	se->mtime = get_mtime(sbi, false);
	if (se->mtime > SIT_I(sbi)->max_mtime)
		SIT_I(sbi)->max_mtime = se->mtime;

	/* Update valid block bitmap */
	if (del > 0) {
		exist = f2fs_test_and_set_bit(offset, se->cur_valid_map);
#ifdef CONFIG_F2FS_CHECK_FS
		mir_exist = f2fs_test_and_set_bit(offset,
						se->cur_valid_map_mir);
		if (unlikely(exist != mir_exist)) {
			f2fs_msg(sbi->sb, KERN_ERR, "Inconsistent error "
				"when setting bitmap, blk:%u, old bit:%d",
				blkaddr, exist);
			f2fs_bug_on(sbi, 1);
		}
#endif
		if (unlikely(exist)) {
			f2fs_msg(sbi->sb, KERN_ERR,
				"Bitmap was wrongly set, blk:%u", blkaddr);
			f2fs_bug_on(sbi, 1);
			se->valid_blocks--;
			del = 0;
		}

		if (!f2fs_test_and_set_bit(offset, se->discard_map))
			sbi->discard_blks--;

		/* don't overwrite by SSR to keep node chain */
		if (IS_NODESEG(se->type)) {
			if (!f2fs_test_and_set_bit(offset, se->ckpt_valid_map))
				se->ckpt_valid_blocks++;
		}
	} else {
		exist = f2fs_test_and_clear_bit(offset, se->cur_valid_map);
#ifdef CONFIG_F2FS_CHECK_FS
		mir_exist = f2fs_test_and_clear_bit(offset,
						se->cur_valid_map_mir);
		if (unlikely(exist != mir_exist)) {
			f2fs_msg(sbi->sb, KERN_ERR, "Inconsistent error "
				"when clearing bitmap, blk:%u, old bit:%d",
				blkaddr, exist);
			f2fs_bug_on(sbi, 1);
		}
#endif
		if (unlikely(!exist)) {
			f2fs_msg(sbi->sb, KERN_ERR,
				"Bitmap was wrongly cleared, blk:%u", blkaddr);
			f2fs_bug_on(sbi, 1);
			se->valid_blocks++;
			del = 0;
		}

		if (f2fs_test_and_clear_bit(offset, se->discard_map))
			sbi->discard_blks++;
	}
	if (!f2fs_test_bit(offset, se->ckpt_valid_map))
		se->ckpt_valid_blocks += del;

	__mark_sit_entry_dirty(sbi, segno);

	/* update total number of valid blocks to be written in ckpt area */
	SIT_I(sbi)->written_valid_blocks += del;

	if (sbi->segs_per_sec > 1)
		get_sec_entry(sbi, segno)->valid_blocks += del;
}