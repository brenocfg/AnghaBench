#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct transaction_chp_stats_s {scalar_t__ cs_chp_time; } ;
struct TYPE_8__ {scalar_t__ t_state; int /*<<< orphan*/  t_tid; struct transaction_chp_stats_s t_chp_stats; int /*<<< orphan*/ * t_checkpoint_io_list; int /*<<< orphan*/ * t_checkpoint_list; TYPE_3__* t_journal; } ;
typedef  TYPE_2__ transaction_t ;
struct journal_head {TYPE_2__* b_cp_transaction; } ;
struct TYPE_9__ {TYPE_1__* j_fs_dev; } ;
typedef  TYPE_3__ journal_t ;
struct TYPE_7__ {int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  JBUFFER_TRACE (struct journal_head*,char*) ; 
 scalar_t__ T_FINISHED ; 
 int /*<<< orphan*/  __buffer_unlink (struct journal_head*) ; 
 int /*<<< orphan*/  __jbd2_journal_drop_transaction (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  jbd2_journal_free_transaction (TYPE_2__*) ; 
 int /*<<< orphan*/  jbd2_journal_put_journal_head (struct journal_head*) ; 
 scalar_t__ jbd2_time_diff (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  trace_jbd2_checkpoint_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct transaction_chp_stats_s*) ; 

int __jbd2_journal_remove_checkpoint(struct journal_head *jh)
{
	struct transaction_chp_stats_s *stats;
	transaction_t *transaction;
	journal_t *journal;
	int ret = 0;

	JBUFFER_TRACE(jh, "entry");

	if ((transaction = jh->b_cp_transaction) == NULL) {
		JBUFFER_TRACE(jh, "not on transaction");
		goto out;
	}
	journal = transaction->t_journal;

	JBUFFER_TRACE(jh, "removing from transaction");
	__buffer_unlink(jh);
	jh->b_cp_transaction = NULL;
	jbd2_journal_put_journal_head(jh);

	if (transaction->t_checkpoint_list != NULL ||
	    transaction->t_checkpoint_io_list != NULL)
		goto out;

	/*
	 * There is one special case to worry about: if we have just pulled the
	 * buffer off a running or committing transaction's checkpoing list,
	 * then even if the checkpoint list is empty, the transaction obviously
	 * cannot be dropped!
	 *
	 * The locking here around t_state is a bit sleazy.
	 * See the comment at the end of jbd2_journal_commit_transaction().
	 */
	if (transaction->t_state != T_FINISHED)
		goto out;

	/* OK, that was the last buffer for the transaction: we can now
	   safely remove this transaction from the log */
	stats = &transaction->t_chp_stats;
	if (stats->cs_chp_time)
		stats->cs_chp_time = jbd2_time_diff(stats->cs_chp_time,
						    jiffies);
	trace_jbd2_checkpoint_stats(journal->j_fs_dev->bd_dev,
				    transaction->t_tid, stats);

	__jbd2_journal_drop_transaction(journal, transaction);
	jbd2_journal_free_transaction(transaction);
	ret = 1;
out:
	return ret;
}