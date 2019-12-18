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
struct f2fs_super_block {int /*<<< orphan*/  block_count; void* segment_count_main; void* segment_count; void* section_count; } ;
struct f2fs_sb_info {int segs_per_sec; long long blocks_per_seg; } ;

/* Variables and functions */
 struct f2fs_super_block* F2FS_RAW_SUPER (struct f2fs_sb_info*) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (long long) ; 
 int le32_to_cpu (void*) ; 
 long long le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_sb_metadata(struct f2fs_sb_info *sbi, int secs)
{
	struct f2fs_super_block *raw_sb = F2FS_RAW_SUPER(sbi);
	int section_count = le32_to_cpu(raw_sb->section_count);
	int segment_count = le32_to_cpu(raw_sb->segment_count);
	int segment_count_main = le32_to_cpu(raw_sb->segment_count_main);
	long long block_count = le64_to_cpu(raw_sb->block_count);
	int segs = secs * sbi->segs_per_sec;

	raw_sb->section_count = cpu_to_le32(section_count + secs);
	raw_sb->segment_count = cpu_to_le32(segment_count + segs);
	raw_sb->segment_count_main = cpu_to_le32(segment_count_main + segs);
	raw_sb->block_count = cpu_to_le64(block_count +
					(long long)segs * sbi->blocks_per_seg);
}