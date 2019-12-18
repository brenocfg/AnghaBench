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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct super_block {int /*<<< orphan*/  s_bdev; } ;
struct f2fs_super_block {int /*<<< orphan*/  segment_count; int /*<<< orphan*/  log_blocks_per_seg; int /*<<< orphan*/  segment_count_main; int /*<<< orphan*/  segment_count_ssa; int /*<<< orphan*/  segment_count_nat; int /*<<< orphan*/  segment_count_sit; int /*<<< orphan*/  segment_count_ckpt; int /*<<< orphan*/  main_blkaddr; int /*<<< orphan*/  ssa_blkaddr; int /*<<< orphan*/  nat_blkaddr; int /*<<< orphan*/  sit_blkaddr; int /*<<< orphan*/  cp_blkaddr; int /*<<< orphan*/  segment0_blkaddr; } ;
struct f2fs_sb_info {struct super_block* sb; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 scalar_t__ F2FS_SUPER_OFFSET ; 
 int /*<<< orphan*/  SBI_NEED_SB_WRITE ; 
 int __f2fs_commit_super (struct buffer_head*,int /*<<< orphan*/ *) ; 
 scalar_t__ bdev_read_only (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  f2fs_info (struct f2fs_sb_info*,char*,char*,scalar_t__,...) ; 
 scalar_t__ f2fs_readonly (struct super_block*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sbi_flag (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool sanity_check_area_boundary(struct f2fs_sb_info *sbi,
					struct buffer_head *bh)
{
	struct f2fs_super_block *raw_super = (struct f2fs_super_block *)
					(bh->b_data + F2FS_SUPER_OFFSET);
	struct super_block *sb = sbi->sb;
	u32 segment0_blkaddr = le32_to_cpu(raw_super->segment0_blkaddr);
	u32 cp_blkaddr = le32_to_cpu(raw_super->cp_blkaddr);
	u32 sit_blkaddr = le32_to_cpu(raw_super->sit_blkaddr);
	u32 nat_blkaddr = le32_to_cpu(raw_super->nat_blkaddr);
	u32 ssa_blkaddr = le32_to_cpu(raw_super->ssa_blkaddr);
	u32 main_blkaddr = le32_to_cpu(raw_super->main_blkaddr);
	u32 segment_count_ckpt = le32_to_cpu(raw_super->segment_count_ckpt);
	u32 segment_count_sit = le32_to_cpu(raw_super->segment_count_sit);
	u32 segment_count_nat = le32_to_cpu(raw_super->segment_count_nat);
	u32 segment_count_ssa = le32_to_cpu(raw_super->segment_count_ssa);
	u32 segment_count_main = le32_to_cpu(raw_super->segment_count_main);
	u32 segment_count = le32_to_cpu(raw_super->segment_count);
	u32 log_blocks_per_seg = le32_to_cpu(raw_super->log_blocks_per_seg);
	u64 main_end_blkaddr = main_blkaddr +
				(segment_count_main << log_blocks_per_seg);
	u64 seg_end_blkaddr = segment0_blkaddr +
				(segment_count << log_blocks_per_seg);

	if (segment0_blkaddr != cp_blkaddr) {
		f2fs_info(sbi, "Mismatch start address, segment0(%u) cp_blkaddr(%u)",
			  segment0_blkaddr, cp_blkaddr);
		return true;
	}

	if (cp_blkaddr + (segment_count_ckpt << log_blocks_per_seg) !=
							sit_blkaddr) {
		f2fs_info(sbi, "Wrong CP boundary, start(%u) end(%u) blocks(%u)",
			  cp_blkaddr, sit_blkaddr,
			  segment_count_ckpt << log_blocks_per_seg);
		return true;
	}

	if (sit_blkaddr + (segment_count_sit << log_blocks_per_seg) !=
							nat_blkaddr) {
		f2fs_info(sbi, "Wrong SIT boundary, start(%u) end(%u) blocks(%u)",
			  sit_blkaddr, nat_blkaddr,
			  segment_count_sit << log_blocks_per_seg);
		return true;
	}

	if (nat_blkaddr + (segment_count_nat << log_blocks_per_seg) !=
							ssa_blkaddr) {
		f2fs_info(sbi, "Wrong NAT boundary, start(%u) end(%u) blocks(%u)",
			  nat_blkaddr, ssa_blkaddr,
			  segment_count_nat << log_blocks_per_seg);
		return true;
	}

	if (ssa_blkaddr + (segment_count_ssa << log_blocks_per_seg) !=
							main_blkaddr) {
		f2fs_info(sbi, "Wrong SSA boundary, start(%u) end(%u) blocks(%u)",
			  ssa_blkaddr, main_blkaddr,
			  segment_count_ssa << log_blocks_per_seg);
		return true;
	}

	if (main_end_blkaddr > seg_end_blkaddr) {
		f2fs_info(sbi, "Wrong MAIN_AREA boundary, start(%u) end(%u) block(%u)",
			  main_blkaddr,
			  segment0_blkaddr +
			  (segment_count << log_blocks_per_seg),
			  segment_count_main << log_blocks_per_seg);
		return true;
	} else if (main_end_blkaddr < seg_end_blkaddr) {
		int err = 0;
		char *res;

		/* fix in-memory information all the time */
		raw_super->segment_count = cpu_to_le32((main_end_blkaddr -
				segment0_blkaddr) >> log_blocks_per_seg);

		if (f2fs_readonly(sb) || bdev_read_only(sb->s_bdev)) {
			set_sbi_flag(sbi, SBI_NEED_SB_WRITE);
			res = "internally";
		} else {
			err = __f2fs_commit_super(bh, NULL);
			res = err ? "failed" : "done";
		}
		f2fs_info(sbi, "Fix alignment : %s, start(%u) end(%u) block(%u)",
			  res, main_blkaddr,
			  segment0_blkaddr +
			  (segment_count << log_blocks_per_seg),
			  segment_count_main << log_blocks_per_seg);
		if (err)
			return true;
	}
	return false;
}