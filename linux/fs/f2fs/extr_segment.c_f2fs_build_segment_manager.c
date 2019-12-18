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
struct f2fs_super_block {int /*<<< orphan*/  ssa_blkaddr; int /*<<< orphan*/  segment_count_main; int /*<<< orphan*/  segment_count; int /*<<< orphan*/  main_blkaddr; int /*<<< orphan*/  segment0_blkaddr; } ;
struct f2fs_sm_info {int main_segments; int rec_prefree_segments; int ipu_policy; int min_seq_blocks; int /*<<< orphan*/  curseg_lock; int /*<<< orphan*/  sit_entry_set; int /*<<< orphan*/  min_ssr_sections; int /*<<< orphan*/  min_hot_blocks; int /*<<< orphan*/  min_fsync_blocks; int /*<<< orphan*/  min_ipu_util; void* ssa_blkaddr; void* ovp_segments; void* reserved_segments; void* segment_count; void* main_blkaddr; void* seg0_blkaddr; } ;
struct f2fs_sb_info {int blocks_per_seg; int segs_per_sec; int /*<<< orphan*/  sb; struct f2fs_sm_info* sm_info; } ;
struct f2fs_checkpoint {int /*<<< orphan*/  overprov_segment_count; int /*<<< orphan*/  rsvd_segment_count; } ;

/* Variables and functions */
 int DEF_MAX_RECLAIM_PREFREE_SEGMENTS ; 
 int /*<<< orphan*/  DEF_MIN_FSYNC_BLOCKS ; 
 int /*<<< orphan*/  DEF_MIN_HOT_BLOCKS ; 
 int /*<<< orphan*/  DEF_MIN_IPU_UTIL ; 
 int DEF_RECLAIM_PREFREE_SEGMENTS ; 
 int ENOMEM ; 
 struct f2fs_checkpoint* F2FS_CKPT (struct f2fs_sb_info*) ; 
 int F2FS_IPU_FSYNC ; 
 struct f2fs_super_block* F2FS_RAW_SUPER (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LFS ; 
 int build_curseg (struct f2fs_sb_info*) ; 
 int build_dirty_segmap (struct f2fs_sb_info*) ; 
 int build_free_segmap (struct f2fs_sb_info*) ; 
 int build_sit_entries (struct f2fs_sb_info*) ; 
 int build_sit_info (struct f2fs_sb_info*) ; 
 int create_discard_cmd_control (struct f2fs_sb_info*) ; 
 int f2fs_create_flush_cmd_control (struct f2fs_sb_info*) ; 
 struct f2fs_sm_info* f2fs_kzalloc (struct f2fs_sb_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_readonly (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_free_segmap (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  init_min_max_mtime (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reserved_sections (struct f2fs_sb_info*) ; 
 int sanity_check_curseg (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  test_opt (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 

int f2fs_build_segment_manager(struct f2fs_sb_info *sbi)
{
	struct f2fs_super_block *raw_super = F2FS_RAW_SUPER(sbi);
	struct f2fs_checkpoint *ckpt = F2FS_CKPT(sbi);
	struct f2fs_sm_info *sm_info;
	int err;

	sm_info = f2fs_kzalloc(sbi, sizeof(struct f2fs_sm_info), GFP_KERNEL);
	if (!sm_info)
		return -ENOMEM;

	/* init sm info */
	sbi->sm_info = sm_info;
	sm_info->seg0_blkaddr = le32_to_cpu(raw_super->segment0_blkaddr);
	sm_info->main_blkaddr = le32_to_cpu(raw_super->main_blkaddr);
	sm_info->segment_count = le32_to_cpu(raw_super->segment_count);
	sm_info->reserved_segments = le32_to_cpu(ckpt->rsvd_segment_count);
	sm_info->ovp_segments = le32_to_cpu(ckpt->overprov_segment_count);
	sm_info->main_segments = le32_to_cpu(raw_super->segment_count_main);
	sm_info->ssa_blkaddr = le32_to_cpu(raw_super->ssa_blkaddr);
	sm_info->rec_prefree_segments = sm_info->main_segments *
					DEF_RECLAIM_PREFREE_SEGMENTS / 100;
	if (sm_info->rec_prefree_segments > DEF_MAX_RECLAIM_PREFREE_SEGMENTS)
		sm_info->rec_prefree_segments = DEF_MAX_RECLAIM_PREFREE_SEGMENTS;

	if (!test_opt(sbi, LFS))
		sm_info->ipu_policy = 1 << F2FS_IPU_FSYNC;
	sm_info->min_ipu_util = DEF_MIN_IPU_UTIL;
	sm_info->min_fsync_blocks = DEF_MIN_FSYNC_BLOCKS;
	sm_info->min_seq_blocks = sbi->blocks_per_seg * sbi->segs_per_sec;
	sm_info->min_hot_blocks = DEF_MIN_HOT_BLOCKS;
	sm_info->min_ssr_sections = reserved_sections(sbi);

	INIT_LIST_HEAD(&sm_info->sit_entry_set);

	init_rwsem(&sm_info->curseg_lock);

	if (!f2fs_readonly(sbi->sb)) {
		err = f2fs_create_flush_cmd_control(sbi);
		if (err)
			return err;
	}

	err = create_discard_cmd_control(sbi);
	if (err)
		return err;

	err = build_sit_info(sbi);
	if (err)
		return err;
	err = build_free_segmap(sbi);
	if (err)
		return err;
	err = build_curseg(sbi);
	if (err)
		return err;

	/* reinit free segmap based on SIT */
	err = build_sit_entries(sbi);
	if (err)
		return err;

	init_free_segmap(sbi);
	err = build_dirty_segmap(sbi);
	if (err)
		return err;

	err = sanity_check_curseg(sbi);
	if (err)
		return err;

	init_min_max_mtime(sbi);
	return 0;
}