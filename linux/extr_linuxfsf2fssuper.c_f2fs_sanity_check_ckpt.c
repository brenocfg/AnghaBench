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
struct f2fs_super_block {int /*<<< orphan*/  segment_count_main; int /*<<< orphan*/  log_blocks_per_seg; int /*<<< orphan*/  segment_count_ssa; int /*<<< orphan*/  segment_count_nat; int /*<<< orphan*/  segment_count_sit; int /*<<< orphan*/  segment_count_ckpt; int /*<<< orphan*/  segment_count; } ;
struct f2fs_sb_info {unsigned int blocks_per_seg; int /*<<< orphan*/  sb; } ;
struct f2fs_checkpoint {int /*<<< orphan*/  nat_ver_bitmap_bytesize; int /*<<< orphan*/  sit_ver_bitmap_bytesize; int /*<<< orphan*/ * cur_node_segno; int /*<<< orphan*/ * cur_data_segno; int /*<<< orphan*/ * cur_data_blkoff; int /*<<< orphan*/ * cur_node_blkoff; int /*<<< orphan*/  user_block_count; int /*<<< orphan*/  rsvd_segment_count; int /*<<< orphan*/  overprov_segment_count; } ;
typedef  unsigned int block_t ;

/* Variables and functions */
 struct f2fs_checkpoint* F2FS_CKPT (struct f2fs_sb_info*) ; 
 unsigned int F2FS_MIN_SEGMENTS ; 
 struct f2fs_super_block* F2FS_RAW_SUPER (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int NR_CURSEG_DATA_TYPE ; 
 int NR_CURSEG_NODE_TYPE ; 
 unsigned int NR_CURSEG_TYPE ; 
 unsigned int __cp_payload (struct f2fs_sb_info*) ; 
 unsigned int __start_sum_addr (struct f2fs_sb_info*) ; 
 int f2fs_cp_error (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int le64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int f2fs_sanity_check_ckpt(struct f2fs_sb_info *sbi)
{
	unsigned int total, fsmeta;
	struct f2fs_super_block *raw_super = F2FS_RAW_SUPER(sbi);
	struct f2fs_checkpoint *ckpt = F2FS_CKPT(sbi);
	unsigned int ovp_segments, reserved_segments;
	unsigned int main_segs, blocks_per_seg;
	unsigned int sit_segs, nat_segs;
	unsigned int sit_bitmap_size, nat_bitmap_size;
	unsigned int log_blocks_per_seg;
	unsigned int segment_count_main;
	unsigned int cp_pack_start_sum, cp_payload;
	block_t user_block_count;
	int i, j;

	total = le32_to_cpu(raw_super->segment_count);
	fsmeta = le32_to_cpu(raw_super->segment_count_ckpt);
	sit_segs = le32_to_cpu(raw_super->segment_count_sit);
	fsmeta += sit_segs;
	nat_segs = le32_to_cpu(raw_super->segment_count_nat);
	fsmeta += nat_segs;
	fsmeta += le32_to_cpu(ckpt->rsvd_segment_count);
	fsmeta += le32_to_cpu(raw_super->segment_count_ssa);

	if (unlikely(fsmeta >= total))
		return 1;

	ovp_segments = le32_to_cpu(ckpt->overprov_segment_count);
	reserved_segments = le32_to_cpu(ckpt->rsvd_segment_count);

	if (unlikely(fsmeta < F2FS_MIN_SEGMENTS ||
			ovp_segments == 0 || reserved_segments == 0)) {
		f2fs_msg(sbi->sb, KERN_ERR,
			"Wrong layout: check mkfs.f2fs version");
		return 1;
	}

	user_block_count = le64_to_cpu(ckpt->user_block_count);
	segment_count_main = le32_to_cpu(raw_super->segment_count_main);
	log_blocks_per_seg = le32_to_cpu(raw_super->log_blocks_per_seg);
	if (!user_block_count || user_block_count >=
			segment_count_main << log_blocks_per_seg) {
		f2fs_msg(sbi->sb, KERN_ERR,
			"Wrong user_block_count: %u", user_block_count);
		return 1;
	}

	main_segs = le32_to_cpu(raw_super->segment_count_main);
	blocks_per_seg = sbi->blocks_per_seg;

	for (i = 0; i < NR_CURSEG_NODE_TYPE; i++) {
		if (le32_to_cpu(ckpt->cur_node_segno[i]) >= main_segs ||
			le16_to_cpu(ckpt->cur_node_blkoff[i]) >= blocks_per_seg)
			return 1;
		for (j = i + 1; j < NR_CURSEG_NODE_TYPE; j++) {
			if (le32_to_cpu(ckpt->cur_node_segno[i]) ==
				le32_to_cpu(ckpt->cur_node_segno[j])) {
				f2fs_msg(sbi->sb, KERN_ERR,
					"Node segment (%u, %u) has the same "
					"segno: %u", i, j,
					le32_to_cpu(ckpt->cur_node_segno[i]));
				return 1;
			}
		}
	}
	for (i = 0; i < NR_CURSEG_DATA_TYPE; i++) {
		if (le32_to_cpu(ckpt->cur_data_segno[i]) >= main_segs ||
			le16_to_cpu(ckpt->cur_data_blkoff[i]) >= blocks_per_seg)
			return 1;
		for (j = i + 1; j < NR_CURSEG_DATA_TYPE; j++) {
			if (le32_to_cpu(ckpt->cur_data_segno[i]) ==
				le32_to_cpu(ckpt->cur_data_segno[j])) {
				f2fs_msg(sbi->sb, KERN_ERR,
					"Data segment (%u, %u) has the same "
					"segno: %u", i, j,
					le32_to_cpu(ckpt->cur_data_segno[i]));
				return 1;
			}
		}
	}
	for (i = 0; i < NR_CURSEG_NODE_TYPE; i++) {
		for (j = i; j < NR_CURSEG_DATA_TYPE; j++) {
			if (le32_to_cpu(ckpt->cur_node_segno[i]) ==
				le32_to_cpu(ckpt->cur_data_segno[j])) {
				f2fs_msg(sbi->sb, KERN_ERR,
					"Data segment (%u) and Data segment (%u)"
					" has the same segno: %u", i, j,
					le32_to_cpu(ckpt->cur_node_segno[i]));
				return 1;
			}
		}
	}

	sit_bitmap_size = le32_to_cpu(ckpt->sit_ver_bitmap_bytesize);
	nat_bitmap_size = le32_to_cpu(ckpt->nat_ver_bitmap_bytesize);

	if (sit_bitmap_size != ((sit_segs / 2) << log_blocks_per_seg) / 8 ||
		nat_bitmap_size != ((nat_segs / 2) << log_blocks_per_seg) / 8) {
		f2fs_msg(sbi->sb, KERN_ERR,
			"Wrong bitmap size: sit: %u, nat:%u",
			sit_bitmap_size, nat_bitmap_size);
		return 1;
	}

	cp_pack_start_sum = __start_sum_addr(sbi);
	cp_payload = __cp_payload(sbi);
	if (cp_pack_start_sum < cp_payload + 1 ||
		cp_pack_start_sum > blocks_per_seg - 1 -
			NR_CURSEG_TYPE) {
		f2fs_msg(sbi->sb, KERN_ERR,
			"Wrong cp_pack_start_sum: %u",
			cp_pack_start_sum);
		return 1;
	}

	if (unlikely(f2fs_cp_error(sbi))) {
		f2fs_msg(sbi->sb, KERN_ERR, "A bug case: need to run fsck");
		return 1;
	}
	return 0;
}