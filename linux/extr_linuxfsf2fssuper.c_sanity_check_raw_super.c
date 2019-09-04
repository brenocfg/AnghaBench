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
struct super_block {int dummy; } ;
struct f2fs_super_block {int hot_ext_count; int /*<<< orphan*/  root_ino; int /*<<< orphan*/  meta_ino; int /*<<< orphan*/  node_ino; int /*<<< orphan*/  cp_payload; int /*<<< orphan*/  extension_count; int /*<<< orphan*/  block_count; int /*<<< orphan*/  log_blocks_per_seg; int /*<<< orphan*/  section_count; int /*<<< orphan*/  secs_per_zone; int /*<<< orphan*/  segs_per_sec; int /*<<< orphan*/  segment_count; int /*<<< orphan*/  log_sectorsize; int /*<<< orphan*/  log_sectors_per_block; int /*<<< orphan*/  log_blocksize; int /*<<< orphan*/  magic; } ;
struct f2fs_sb_info {struct super_block* sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int block_t ;

/* Variables and functions */
 unsigned int F2FS_BLKSIZE ; 
 int F2FS_CP_PACKS ; 
 int F2FS_MAX_EXTENSION ; 
 int F2FS_MAX_LOG_SECTOR_SIZE ; 
 int F2FS_MAX_SEGMENT ; 
 int F2FS_MIN_LOG_SECTOR_SIZE ; 
 int F2FS_MIN_SEGMENTS ; 
 int F2FS_SUPER_MAGIC ; 
 scalar_t__ F2FS_SUPER_OFFSET ; 
 int /*<<< orphan*/  KERN_INFO ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  f2fs_msg (struct super_block*,int /*<<< orphan*/ ,char*,int,...) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ sanity_check_area_boundary (struct f2fs_sb_info*,struct buffer_head*) ; 

__attribute__((used)) static int sanity_check_raw_super(struct f2fs_sb_info *sbi,
				struct buffer_head *bh)
{
	block_t segment_count, segs_per_sec, secs_per_zone;
	block_t total_sections, blocks_per_seg;
	struct f2fs_super_block *raw_super = (struct f2fs_super_block *)
					(bh->b_data + F2FS_SUPER_OFFSET);
	struct super_block *sb = sbi->sb;
	unsigned int blocksize;

	if (F2FS_SUPER_MAGIC != le32_to_cpu(raw_super->magic)) {
		f2fs_msg(sb, KERN_INFO,
			"Magic Mismatch, valid(0x%x) - read(0x%x)",
			F2FS_SUPER_MAGIC, le32_to_cpu(raw_super->magic));
		return 1;
	}

	/* Currently, support only 4KB page cache size */
	if (F2FS_BLKSIZE != PAGE_SIZE) {
		f2fs_msg(sb, KERN_INFO,
			"Invalid page_cache_size (%lu), supports only 4KB\n",
			PAGE_SIZE);
		return 1;
	}

	/* Currently, support only 4KB block size */
	blocksize = 1 << le32_to_cpu(raw_super->log_blocksize);
	if (blocksize != F2FS_BLKSIZE) {
		f2fs_msg(sb, KERN_INFO,
			"Invalid blocksize (%u), supports only 4KB\n",
			blocksize);
		return 1;
	}

	/* check log blocks per segment */
	if (le32_to_cpu(raw_super->log_blocks_per_seg) != 9) {
		f2fs_msg(sb, KERN_INFO,
			"Invalid log blocks per segment (%u)\n",
			le32_to_cpu(raw_super->log_blocks_per_seg));
		return 1;
	}

	/* Currently, support 512/1024/2048/4096 bytes sector size */
	if (le32_to_cpu(raw_super->log_sectorsize) >
				F2FS_MAX_LOG_SECTOR_SIZE ||
		le32_to_cpu(raw_super->log_sectorsize) <
				F2FS_MIN_LOG_SECTOR_SIZE) {
		f2fs_msg(sb, KERN_INFO, "Invalid log sectorsize (%u)",
			le32_to_cpu(raw_super->log_sectorsize));
		return 1;
	}
	if (le32_to_cpu(raw_super->log_sectors_per_block) +
		le32_to_cpu(raw_super->log_sectorsize) !=
			F2FS_MAX_LOG_SECTOR_SIZE) {
		f2fs_msg(sb, KERN_INFO,
			"Invalid log sectors per block(%u) log sectorsize(%u)",
			le32_to_cpu(raw_super->log_sectors_per_block),
			le32_to_cpu(raw_super->log_sectorsize));
		return 1;
	}

	segment_count = le32_to_cpu(raw_super->segment_count);
	segs_per_sec = le32_to_cpu(raw_super->segs_per_sec);
	secs_per_zone = le32_to_cpu(raw_super->secs_per_zone);
	total_sections = le32_to_cpu(raw_super->section_count);

	/* blocks_per_seg should be 512, given the above check */
	blocks_per_seg = 1 << le32_to_cpu(raw_super->log_blocks_per_seg);

	if (segment_count > F2FS_MAX_SEGMENT ||
				segment_count < F2FS_MIN_SEGMENTS) {
		f2fs_msg(sb, KERN_INFO,
			"Invalid segment count (%u)",
			segment_count);
		return 1;
	}

	if (total_sections > segment_count ||
			total_sections < F2FS_MIN_SEGMENTS ||
			segs_per_sec > segment_count || !segs_per_sec) {
		f2fs_msg(sb, KERN_INFO,
			"Invalid segment/section count (%u, %u x %u)",
			segment_count, total_sections, segs_per_sec);
		return 1;
	}

	if ((segment_count / segs_per_sec) < total_sections) {
		f2fs_msg(sb, KERN_INFO,
			"Small segment_count (%u < %u * %u)",
			segment_count, segs_per_sec, total_sections);
		return 1;
	}

	if (segment_count > (le64_to_cpu(raw_super->block_count) >> 9)) {
		f2fs_msg(sb, KERN_INFO,
			"Wrong segment_count / block_count (%u > %llu)",
			segment_count, le64_to_cpu(raw_super->block_count));
		return 1;
	}

	if (secs_per_zone > total_sections || !secs_per_zone) {
		f2fs_msg(sb, KERN_INFO,
			"Wrong secs_per_zone / total_sections (%u, %u)",
			secs_per_zone, total_sections);
		return 1;
	}
	if (le32_to_cpu(raw_super->extension_count) > F2FS_MAX_EXTENSION ||
			raw_super->hot_ext_count > F2FS_MAX_EXTENSION ||
			(le32_to_cpu(raw_super->extension_count) +
			raw_super->hot_ext_count) > F2FS_MAX_EXTENSION) {
		f2fs_msg(sb, KERN_INFO,
			"Corrupted extension count (%u + %u > %u)",
			le32_to_cpu(raw_super->extension_count),
			raw_super->hot_ext_count,
			F2FS_MAX_EXTENSION);
		return 1;
	}

	if (le32_to_cpu(raw_super->cp_payload) >
				(blocks_per_seg - F2FS_CP_PACKS)) {
		f2fs_msg(sb, KERN_INFO,
			"Insane cp_payload (%u > %u)",
			le32_to_cpu(raw_super->cp_payload),
			blocks_per_seg - F2FS_CP_PACKS);
		return 1;
	}

	/* check reserved ino info */
	if (le32_to_cpu(raw_super->node_ino) != 1 ||
		le32_to_cpu(raw_super->meta_ino) != 2 ||
		le32_to_cpu(raw_super->root_ino) != 3) {
		f2fs_msg(sb, KERN_INFO,
			"Invalid Fs Meta Ino: node(%u) meta(%u) root(%u)",
			le32_to_cpu(raw_super->node_ino),
			le32_to_cpu(raw_super->meta_ino),
			le32_to_cpu(raw_super->root_ino));
		return 1;
	}

	/* check CP/SIT/NAT/SSA/MAIN_AREA area boundary */
	if (sanity_check_area_boundary(sbi, bh))
		return 1;

	return 0;
}