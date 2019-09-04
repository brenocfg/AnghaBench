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
struct f2fs_sit_entry {int dummy; } ;
struct f2fs_sb_info {scalar_t__ blocks_per_seg; int /*<<< orphan*/  sb; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ GET_SIT_VBLOCKS (struct f2fs_sit_entry*) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  SBI_NEED_FSCK ; 
 int TOTAL_SEGS (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  set_sbi_flag (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int check_block_count(struct f2fs_sb_info *sbi,
		int segno, struct f2fs_sit_entry *raw_sit)
{
#ifdef CONFIG_F2FS_CHECK_FS
	bool is_valid  = test_bit_le(0, raw_sit->valid_map) ? true : false;
	int valid_blocks = 0;
	int cur_pos = 0, next_pos;

	/* check bitmap with valid block count */
	do {
		if (is_valid) {
			next_pos = find_next_zero_bit_le(&raw_sit->valid_map,
					sbi->blocks_per_seg,
					cur_pos);
			valid_blocks += next_pos - cur_pos;
		} else
			next_pos = find_next_bit_le(&raw_sit->valid_map,
					sbi->blocks_per_seg,
					cur_pos);
		cur_pos = next_pos;
		is_valid = !is_valid;
	} while (cur_pos < sbi->blocks_per_seg);

	if (unlikely(GET_SIT_VBLOCKS(raw_sit) != valid_blocks)) {
		f2fs_msg(sbi->sb, KERN_ERR,
				"Mismatch valid blocks %d vs. %d",
					GET_SIT_VBLOCKS(raw_sit), valid_blocks);
		set_sbi_flag(sbi, SBI_NEED_FSCK);
		return -EINVAL;
	}
#endif
	/* check segment usage, and check boundary of a given segment number */
	if (unlikely(GET_SIT_VBLOCKS(raw_sit) > sbi->blocks_per_seg
					|| segno > TOTAL_SEGS(sbi) - 1)) {
		f2fs_msg(sbi->sb, KERN_ERR,
				"Wrong valid blocks %d or segno %u",
					GET_SIT_VBLOCKS(raw_sit), segno);
		set_sbi_flag(sbi, SBI_NEED_FSCK);
		return -EINVAL;
	}
	return 0;
}