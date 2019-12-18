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
struct f2fs_sb_info {unsigned short blocks_per_seg; } ;
struct dirty_seglist_info {int /*<<< orphan*/  seglist_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIRTY ; 
 struct dirty_seglist_info* DIRTY_I (struct f2fs_sb_info*) ; 
 scalar_t__ IS_CURSEG (struct f2fs_sb_info*,unsigned int) ; 
 unsigned int NULL_SEGNO ; 
 int /*<<< orphan*/  PRE ; 
 int /*<<< orphan*/  SBI_CP_DISABLED ; 
 int /*<<< orphan*/  __locate_dirty_segment (struct f2fs_sb_info*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __remove_dirty_segment (struct f2fs_sb_info*,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned short get_ckpt_valid_blocks (struct f2fs_sb_info*,unsigned int) ; 
 unsigned short get_valid_blocks (struct f2fs_sb_info*,unsigned int,int) ; 
 int /*<<< orphan*/  is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void locate_dirty_segment(struct f2fs_sb_info *sbi, unsigned int segno)
{
	struct dirty_seglist_info *dirty_i = DIRTY_I(sbi);
	unsigned short valid_blocks, ckpt_valid_blocks;

	if (segno == NULL_SEGNO || IS_CURSEG(sbi, segno))
		return;

	mutex_lock(&dirty_i->seglist_lock);

	valid_blocks = get_valid_blocks(sbi, segno, false);
	ckpt_valid_blocks = get_ckpt_valid_blocks(sbi, segno);

	if (valid_blocks == 0 && (!is_sbi_flag_set(sbi, SBI_CP_DISABLED) ||
				ckpt_valid_blocks == sbi->blocks_per_seg)) {
		__locate_dirty_segment(sbi, segno, PRE);
		__remove_dirty_segment(sbi, segno, DIRTY);
	} else if (valid_blocks < sbi->blocks_per_seg) {
		__locate_dirty_segment(sbi, segno, DIRTY);
	} else {
		/* Recovery routine with SSR needs this */
		__remove_dirty_segment(sbi, segno, DIRTY);
	}

	mutex_unlock(&dirty_i->seglist_lock);
}