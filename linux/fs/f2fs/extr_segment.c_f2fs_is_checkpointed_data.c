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
struct sit_info {int /*<<< orphan*/  sentry_lock; } ;
struct seg_entry {int /*<<< orphan*/  ckpt_valid_map; } ;
struct f2fs_sb_info {int dummy; } ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 unsigned int GET_BLKOFF_FROM_SEG0 (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 unsigned int GET_SEGNO (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 struct sit_info* SIT_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  __is_valid_data_blkaddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ f2fs_test_bit (unsigned int,int /*<<< orphan*/ ) ; 
 struct seg_entry* get_seg_entry (struct f2fs_sb_info*,unsigned int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

bool f2fs_is_checkpointed_data(struct f2fs_sb_info *sbi, block_t blkaddr)
{
	struct sit_info *sit_i = SIT_I(sbi);
	unsigned int segno, offset;
	struct seg_entry *se;
	bool is_cp = false;

	if (!__is_valid_data_blkaddr(blkaddr))
		return true;

	down_read(&sit_i->sentry_lock);

	segno = GET_SEGNO(sbi, blkaddr);
	se = get_seg_entry(sbi, segno);
	offset = GET_BLKOFF_FROM_SEG0(sbi, blkaddr);

	if (f2fs_test_bit(offset, se->ckpt_valid_map))
		is_cp = true;

	up_read(&sit_i->sentry_lock);

	return is_cp;
}