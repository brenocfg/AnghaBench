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
struct f2fs_super_block {int /*<<< orphan*/  meta_ino; int /*<<< orphan*/  node_ino; int /*<<< orphan*/  root_ino; int /*<<< orphan*/  segment_count_nat; int /*<<< orphan*/  section_count; int /*<<< orphan*/  secs_per_zone; int /*<<< orphan*/  segs_per_sec; int /*<<< orphan*/  log_blocks_per_seg; int /*<<< orphan*/  log_blocksize; int /*<<< orphan*/  log_sectors_per_block; } ;
struct f2fs_sb_info {int log_sectors_per_block; int log_blocksize; int blocksize; int log_blocks_per_seg; int blocks_per_seg; int segs_per_sec; int secs_per_zone; int total_sections; int total_node_count; int root_ino_num; int node_ino_num; int meta_ino_num; int migration_granularity; int /*<<< orphan*/  sb_lock; int /*<<< orphan*/  dev_lock; scalar_t__ dirty_device; int /*<<< orphan*/  cp_lock; int /*<<< orphan*/  io_order_lock; int /*<<< orphan*/  umount_mutex; int /*<<< orphan*/  s_list; int /*<<< orphan*/ * wb_sync_req; int /*<<< orphan*/ * nr_pages; void** interval_time; int /*<<< orphan*/  dir_level; int /*<<< orphan*/  max_victim_search; void** next_victim_seg; int /*<<< orphan*/  cur_victim_sec; struct f2fs_super_block* raw_super; } ;

/* Variables and functions */
 size_t BG_GC ; 
 size_t CP_TIME ; 
 void* DEF_CP_INTERVAL ; 
 int /*<<< orphan*/  DEF_DIR_LEVEL ; 
 void* DEF_DISABLE_INTERVAL ; 
 void* DEF_IDLE_INTERVAL ; 
 int /*<<< orphan*/  DEF_MAX_VICTIM_SEARCH ; 
 void* DEF_UMOUNT_DISCARD_TIMEOUT ; 
 size_t DISABLE_TIME ; 
 size_t DISCARD_TIME ; 
 size_t FG_GC ; 
 size_t GC_TIME ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int META ; 
 int NAT_ENTRY_PER_BLOCK ; 
 int NR_COUNT_TYPE ; 
 int /*<<< orphan*/  NULL_SECNO ; 
 void* NULL_SEGNO ; 
 size_t REQ_TIME ; 
 int /*<<< orphan*/  SBI_NEED_FSCK ; 
 size_t UMOUNT_DISCARD_TIMEOUT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_sbi_flag (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_sb_info(struct f2fs_sb_info *sbi)
{
	struct f2fs_super_block *raw_super = sbi->raw_super;
	int i;

	sbi->log_sectors_per_block =
		le32_to_cpu(raw_super->log_sectors_per_block);
	sbi->log_blocksize = le32_to_cpu(raw_super->log_blocksize);
	sbi->blocksize = 1 << sbi->log_blocksize;
	sbi->log_blocks_per_seg = le32_to_cpu(raw_super->log_blocks_per_seg);
	sbi->blocks_per_seg = 1 << sbi->log_blocks_per_seg;
	sbi->segs_per_sec = le32_to_cpu(raw_super->segs_per_sec);
	sbi->secs_per_zone = le32_to_cpu(raw_super->secs_per_zone);
	sbi->total_sections = le32_to_cpu(raw_super->section_count);
	sbi->total_node_count =
		(le32_to_cpu(raw_super->segment_count_nat) / 2)
			* sbi->blocks_per_seg * NAT_ENTRY_PER_BLOCK;
	sbi->root_ino_num = le32_to_cpu(raw_super->root_ino);
	sbi->node_ino_num = le32_to_cpu(raw_super->node_ino);
	sbi->meta_ino_num = le32_to_cpu(raw_super->meta_ino);
	sbi->cur_victim_sec = NULL_SECNO;
	sbi->next_victim_seg[BG_GC] = NULL_SEGNO;
	sbi->next_victim_seg[FG_GC] = NULL_SEGNO;
	sbi->max_victim_search = DEF_MAX_VICTIM_SEARCH;
	sbi->migration_granularity = sbi->segs_per_sec;

	sbi->dir_level = DEF_DIR_LEVEL;
	sbi->interval_time[CP_TIME] = DEF_CP_INTERVAL;
	sbi->interval_time[REQ_TIME] = DEF_IDLE_INTERVAL;
	sbi->interval_time[DISCARD_TIME] = DEF_IDLE_INTERVAL;
	sbi->interval_time[GC_TIME] = DEF_IDLE_INTERVAL;
	sbi->interval_time[DISABLE_TIME] = DEF_DISABLE_INTERVAL;
	sbi->interval_time[UMOUNT_DISCARD_TIMEOUT] =
				DEF_UMOUNT_DISCARD_TIMEOUT;
	clear_sbi_flag(sbi, SBI_NEED_FSCK);

	for (i = 0; i < NR_COUNT_TYPE; i++)
		atomic_set(&sbi->nr_pages[i], 0);

	for (i = 0; i < META; i++)
		atomic_set(&sbi->wb_sync_req[i], 0);

	INIT_LIST_HEAD(&sbi->s_list);
	mutex_init(&sbi->umount_mutex);
	init_rwsem(&sbi->io_order_lock);
	spin_lock_init(&sbi->cp_lock);

	sbi->dirty_device = 0;
	spin_lock_init(&sbi->dev_lock);

	init_rwsem(&sbi->sb_lock);
}