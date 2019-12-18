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
struct writeback_control {scalar_t__ sync_mode; int /*<<< orphan*/  pages_skipped; int /*<<< orphan*/  nr_to_write; } ;
struct f2fs_sb_info {int /*<<< orphan*/ * wb_sync_req; } ;
struct blk_plug {int dummy; } ;
struct address_space {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  F2FS_DIRTY_NODES ; 
 struct f2fs_sb_info* F2FS_M_SB (struct address_space*) ; 
 int /*<<< orphan*/  FS_NODE_IO ; 
 size_t NODE ; 
 int /*<<< orphan*/  SBI_POR_DOING ; 
 scalar_t__ WB_SYNC_ALL ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_finish_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  blk_start_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  f2fs_balance_fs_bg (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_sync_node_pages (struct f2fs_sb_info*,struct writeback_control*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ get_pages (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (long,int /*<<< orphan*/ ) ; 
 scalar_t__ nr_pages_to_skip (struct f2fs_sb_info*,size_t) ; 
 long nr_pages_to_write (struct f2fs_sb_info*,size_t,struct writeback_control*) ; 
 int /*<<< orphan*/  trace_f2fs_writepages (int /*<<< orphan*/ ,struct writeback_control*,size_t) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int f2fs_write_node_pages(struct address_space *mapping,
			    struct writeback_control *wbc)
{
	struct f2fs_sb_info *sbi = F2FS_M_SB(mapping);
	struct blk_plug plug;
	long diff;

	if (unlikely(is_sbi_flag_set(sbi, SBI_POR_DOING)))
		goto skip_write;

	/* balancing f2fs's metadata in background */
	f2fs_balance_fs_bg(sbi);

	/* collect a number of dirty node pages and write together */
	if (wbc->sync_mode != WB_SYNC_ALL &&
			get_pages(sbi, F2FS_DIRTY_NODES) <
					nr_pages_to_skip(sbi, NODE))
		goto skip_write;

	if (wbc->sync_mode == WB_SYNC_ALL)
		atomic_inc(&sbi->wb_sync_req[NODE]);
	else if (atomic_read(&sbi->wb_sync_req[NODE]))
		goto skip_write;

	trace_f2fs_writepages(mapping->host, wbc, NODE);

	diff = nr_pages_to_write(sbi, NODE, wbc);
	blk_start_plug(&plug);
	f2fs_sync_node_pages(sbi, wbc, true, FS_NODE_IO);
	blk_finish_plug(&plug);
	wbc->nr_to_write = max((long)0, wbc->nr_to_write - diff);

	if (wbc->sync_mode == WB_SYNC_ALL)
		atomic_dec(&sbi->wb_sync_req[NODE]);
	return 0;

skip_write:
	wbc->pages_skipped += get_pages(sbi, F2FS_DIRTY_NODES);
	trace_f2fs_writepages(mapping->host, wbc, NODE);
	return 0;
}