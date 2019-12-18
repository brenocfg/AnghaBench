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
struct wb_writeback_work {int for_sync; int /*<<< orphan*/  reason; int /*<<< orphan*/ * done; int /*<<< orphan*/  range_cyclic; int /*<<< orphan*/  nr_pages; int /*<<< orphan*/  sync_mode; struct super_block* sb; } ;
struct super_block {int /*<<< orphan*/  s_umount; struct backing_dev_info* s_bdi; } ;
struct backing_dev_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WB_COMPLETION (int /*<<< orphan*/ ,struct backing_dev_info*) ; 
 int /*<<< orphan*/  LONG_MAX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WB_REASON_SYNC ; 
 int /*<<< orphan*/  WB_SYNC_ALL ; 
 int /*<<< orphan*/  bdi_down_write_wb_switch_rwsem (struct backing_dev_info*) ; 
 int /*<<< orphan*/  bdi_split_work_to_wbs (struct backing_dev_info*,struct wb_writeback_work*,int) ; 
 int /*<<< orphan*/  bdi_up_write_wb_switch_rwsem (struct backing_dev_info*) ; 
 int /*<<< orphan*/  done ; 
 struct backing_dev_info noop_backing_dev_info ; 
 int /*<<< orphan*/  rwsem_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_sb_inodes (struct super_block*) ; 
 int /*<<< orphan*/  wb_wait_for_completion (int /*<<< orphan*/ *) ; 

void sync_inodes_sb(struct super_block *sb)
{
	struct backing_dev_info *bdi = sb->s_bdi;
	DEFINE_WB_COMPLETION(done, bdi);
	struct wb_writeback_work work = {
		.sb		= sb,
		.sync_mode	= WB_SYNC_ALL,
		.nr_pages	= LONG_MAX,
		.range_cyclic	= 0,
		.done		= &done,
		.reason		= WB_REASON_SYNC,
		.for_sync	= 1,
	};

	/*
	 * Can't skip on !bdi_has_dirty() because we should wait for !dirty
	 * inodes under writeback and I_DIRTY_TIME inodes ignored by
	 * bdi_has_dirty() need to be written out too.
	 */
	if (bdi == &noop_backing_dev_info)
		return;
	WARN_ON(!rwsem_is_locked(&sb->s_umount));

	/* protect against inode wb switch, see inode_switch_wbs_work_fn() */
	bdi_down_write_wb_switch_rwsem(bdi);
	bdi_split_work_to_wbs(bdi, &work, false);
	wb_wait_for_completion(&done);
	bdi_up_write_wb_switch_rwsem(bdi);

	wait_sb_inodes(sb);
}