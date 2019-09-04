#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tid_t ;
struct TYPE_6__ {int j_flags; int /*<<< orphan*/  j_fs_dev; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int JBD2_BARRIER ; 
 int /*<<< orphan*/  J_ASSERT (int) ; 
 int __jbd2_update_log_tail (TYPE_1__*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  blkdev_issue_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ is_journal_aborted (TYPE_1__*) ; 
 int /*<<< orphan*/  jbd2_journal_get_log_tail (TYPE_1__*,int /*<<< orphan*/ *,unsigned long*) ; 

int jbd2_cleanup_journal_tail(journal_t *journal)
{
	tid_t		first_tid;
	unsigned long	blocknr;

	if (is_journal_aborted(journal))
		return -EIO;

	if (!jbd2_journal_get_log_tail(journal, &first_tid, &blocknr))
		return 1;
	J_ASSERT(blocknr != 0);

	/*
	 * We need to make sure that any blocks that were recently written out
	 * --- perhaps by jbd2_log_do_checkpoint() --- are flushed out before
	 * we drop the transactions from the journal. It's unlikely this will
	 * be necessary, especially with an appropriately sized journal, but we
	 * need this to guarantee correctness.  Fortunately
	 * jbd2_cleanup_journal_tail() doesn't get called all that often.
	 */
	if (journal->j_flags & JBD2_BARRIER)
		blkdev_issue_flush(journal->j_fs_dev, GFP_NOFS, NULL);

	return __jbd2_update_log_tail(journal, first_tid, blocknr);
}