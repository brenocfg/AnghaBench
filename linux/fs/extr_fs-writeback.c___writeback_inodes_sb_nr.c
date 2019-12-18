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
struct wb_writeback_work {int tagged_writepages; unsigned long nr_pages; int reason; int /*<<< orphan*/ * done; int /*<<< orphan*/  sync_mode; struct super_block* sb; } ;
struct super_block {struct backing_dev_info* s_bdi; int /*<<< orphan*/  s_umount; } ;
struct backing_dev_info {int dummy; } ;
typedef  enum wb_reason { ____Placeholder_wb_reason } wb_reason ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WB_COMPLETION (int /*<<< orphan*/ ,struct backing_dev_info*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WB_SYNC_NONE ; 
 int /*<<< orphan*/  bdi_has_dirty_io (struct backing_dev_info*) ; 
 int /*<<< orphan*/  bdi_split_work_to_wbs (struct backing_dev_info*,struct wb_writeback_work*,int) ; 
 int /*<<< orphan*/  done ; 
 struct backing_dev_info noop_backing_dev_info ; 
 int /*<<< orphan*/  rwsem_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wb_wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __writeback_inodes_sb_nr(struct super_block *sb, unsigned long nr,
				     enum wb_reason reason, bool skip_if_busy)
{
	struct backing_dev_info *bdi = sb->s_bdi;
	DEFINE_WB_COMPLETION(done, bdi);
	struct wb_writeback_work work = {
		.sb			= sb,
		.sync_mode		= WB_SYNC_NONE,
		.tagged_writepages	= 1,
		.done			= &done,
		.nr_pages		= nr,
		.reason			= reason,
	};

	if (!bdi_has_dirty_io(bdi) || bdi == &noop_backing_dev_info)
		return;
	WARN_ON(!rwsem_is_locked(&sb->s_umount));

	bdi_split_work_to_wbs(sb->s_bdi, &work, skip_if_busy);
	wb_wait_for_completion(&done);
}