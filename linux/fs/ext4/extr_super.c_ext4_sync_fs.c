#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tid_t ;
struct super_block {int /*<<< orphan*/  s_bdev; } ;
struct ext4_sb_info {TYPE_1__* s_journal; int /*<<< orphan*/  rsv_conversion_wq; } ;
struct TYPE_5__ {int j_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BARRIER ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int JBD2_BARRIER ; 
 int blkdev_issue_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dquot_writeback_dquots (struct super_block*,int) ; 
 int /*<<< orphan*/  ext4_forced_shutdown (struct ext4_sb_info*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd2_get_latest_transaction (TYPE_1__*) ; 
 scalar_t__ jbd2_journal_start_commit (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int jbd2_log_wait_commit (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd2_trans_will_send_data_barrier (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_opt (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ext4_sync_fs (struct super_block*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_sync_fs(struct super_block *sb, int wait)
{
	int ret = 0;
	tid_t target;
	bool needs_barrier = false;
	struct ext4_sb_info *sbi = EXT4_SB(sb);

	if (unlikely(ext4_forced_shutdown(sbi)))
		return 0;

	trace_ext4_sync_fs(sb, wait);
	flush_workqueue(sbi->rsv_conversion_wq);
	/*
	 * Writeback quota in non-journalled quota case - journalled quota has
	 * no dirty dquots
	 */
	dquot_writeback_dquots(sb, -1);
	/*
	 * Data writeback is possible w/o journal transaction, so barrier must
	 * being sent at the end of the function. But we can skip it if
	 * transaction_commit will do it for us.
	 */
	if (sbi->s_journal) {
		target = jbd2_get_latest_transaction(sbi->s_journal);
		if (wait && sbi->s_journal->j_flags & JBD2_BARRIER &&
		    !jbd2_trans_will_send_data_barrier(sbi->s_journal, target))
			needs_barrier = true;

		if (jbd2_journal_start_commit(sbi->s_journal, &target)) {
			if (wait)
				ret = jbd2_log_wait_commit(sbi->s_journal,
							   target);
		}
	} else if (wait && test_opt(sb, BARRIER))
		needs_barrier = true;
	if (needs_barrier) {
		int err;
		err = blkdev_issue_flush(sb->s_bdev, GFP_KERNEL, NULL);
		if (!ret)
			ret = err;
	}

	return ret;
}