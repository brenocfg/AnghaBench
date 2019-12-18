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
struct f2fs_sb_info {int /*<<< orphan*/  stat_info; int /*<<< orphan*/  sb; int /*<<< orphan*/  flush_lock; } ;
struct blk_plug {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_TIME ; 
 int /*<<< orphan*/  DATA_FLUSH ; 
 int /*<<< orphan*/  EXTENT_CACHE ; 
 int /*<<< orphan*/  EXTENT_CACHE_SHRINK_NUMBER ; 
 int /*<<< orphan*/  FILE_INODE ; 
 int /*<<< orphan*/  FREE_NIDS ; 
 int /*<<< orphan*/  INO_ENTRIES ; 
 int /*<<< orphan*/  MAX_FREE_NIDS ; 
 int /*<<< orphan*/  NAT_ENTRIES ; 
 int /*<<< orphan*/  NAT_ENTRY_PER_BLOCK ; 
 int /*<<< orphan*/  REQ_TIME ; 
 int /*<<< orphan*/  SBI_POR_DOING ; 
 int /*<<< orphan*/  blk_finish_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  blk_start_plug (struct blk_plug*) ; 
 scalar_t__ excess_dirty_nats (struct f2fs_sb_info*) ; 
 scalar_t__ excess_dirty_nodes (struct f2fs_sb_info*) ; 
 scalar_t__ excess_prefree_segs (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_available_free_memory (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_build_free_nids (struct f2fs_sb_info*,int,int) ; 
 int /*<<< orphan*/  f2fs_shrink_extent_tree (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_sync_dirty_inodes (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_sync_fs (int /*<<< orphan*/ ,int) ; 
 scalar_t__ f2fs_time_over (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_try_to_free_nats (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_try_to_free_nids (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_idle (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stat_inc_bg_cp_count (int /*<<< orphan*/ ) ; 
 scalar_t__ test_opt (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void f2fs_balance_fs_bg(struct f2fs_sb_info *sbi)
{
	if (unlikely(is_sbi_flag_set(sbi, SBI_POR_DOING)))
		return;

	/* try to shrink extent cache when there is no enough memory */
	if (!f2fs_available_free_memory(sbi, EXTENT_CACHE))
		f2fs_shrink_extent_tree(sbi, EXTENT_CACHE_SHRINK_NUMBER);

	/* check the # of cached NAT entries */
	if (!f2fs_available_free_memory(sbi, NAT_ENTRIES))
		f2fs_try_to_free_nats(sbi, NAT_ENTRY_PER_BLOCK);

	if (!f2fs_available_free_memory(sbi, FREE_NIDS))
		f2fs_try_to_free_nids(sbi, MAX_FREE_NIDS);
	else
		f2fs_build_free_nids(sbi, false, false);

	if (!is_idle(sbi, REQ_TIME) &&
		(!excess_dirty_nats(sbi) && !excess_dirty_nodes(sbi)))
		return;

	/* checkpoint is the only way to shrink partial cached entries */
	if (!f2fs_available_free_memory(sbi, NAT_ENTRIES) ||
			!f2fs_available_free_memory(sbi, INO_ENTRIES) ||
			excess_prefree_segs(sbi) ||
			excess_dirty_nats(sbi) ||
			excess_dirty_nodes(sbi) ||
			f2fs_time_over(sbi, CP_TIME)) {
		if (test_opt(sbi, DATA_FLUSH)) {
			struct blk_plug plug;

			mutex_lock(&sbi->flush_lock);

			blk_start_plug(&plug);
			f2fs_sync_dirty_inodes(sbi, FILE_INODE);
			blk_finish_plug(&plug);

			mutex_unlock(&sbi->flush_lock);
		}
		f2fs_sync_fs(sbi->sb, true);
		stat_inc_bg_cp_count(sbi->stat_info);
	}
}