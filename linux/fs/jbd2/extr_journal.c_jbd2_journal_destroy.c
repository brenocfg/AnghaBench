#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {struct TYPE_12__* j_wbuf; scalar_t__ j_chksum_driver; scalar_t__ j_revoke; int /*<<< orphan*/  j_inode; scalar_t__ j_proc_entry; scalar_t__ j_sb_buffer; int /*<<< orphan*/  j_checkpoint_mutex; int /*<<< orphan*/  j_state_lock; scalar_t__ j_transaction_sequence; scalar_t__ j_tail_sequence; int /*<<< orphan*/  j_list_lock; int /*<<< orphan*/ * j_checkpoint_transactions; int /*<<< orphan*/ * j_committing_transaction; int /*<<< orphan*/ * j_running_transaction; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  J_ASSERT (int /*<<< orphan*/ ) ; 
 int REQ_FUA ; 
 int REQ_PREFLUSH ; 
 int REQ_SYNC ; 
 int /*<<< orphan*/  brelse (scalar_t__) ; 
 int /*<<< orphan*/  crypto_free_shash (scalar_t__) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_journal_aborted (TYPE_1__*) ; 
 int /*<<< orphan*/  jbd2_journal_commit_transaction (TYPE_1__*) ; 
 int /*<<< orphan*/  jbd2_journal_destroy_checkpoint (TYPE_1__*) ; 
 int /*<<< orphan*/  jbd2_journal_destroy_revoke (TYPE_1__*) ; 
 int jbd2_log_do_checkpoint (TYPE_1__*) ; 
 int /*<<< orphan*/  jbd2_mark_journal_empty (TYPE_1__*,int) ; 
 int /*<<< orphan*/  jbd2_stats_proc_exit (TYPE_1__*) ; 
 int /*<<< orphan*/  journal_kill_thread (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock_io (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

int jbd2_journal_destroy(journal_t *journal)
{
	int err = 0;

	/* Wait for the commit thread to wake up and die. */
	journal_kill_thread(journal);

	/* Force a final log commit */
	if (journal->j_running_transaction)
		jbd2_journal_commit_transaction(journal);

	/* Force any old transactions to disk */

	/* Totally anal locking here... */
	spin_lock(&journal->j_list_lock);
	while (journal->j_checkpoint_transactions != NULL) {
		spin_unlock(&journal->j_list_lock);
		mutex_lock_io(&journal->j_checkpoint_mutex);
		err = jbd2_log_do_checkpoint(journal);
		mutex_unlock(&journal->j_checkpoint_mutex);
		/*
		 * If checkpointing failed, just free the buffers to avoid
		 * looping forever
		 */
		if (err) {
			jbd2_journal_destroy_checkpoint(journal);
			spin_lock(&journal->j_list_lock);
			break;
		}
		spin_lock(&journal->j_list_lock);
	}

	J_ASSERT(journal->j_running_transaction == NULL);
	J_ASSERT(journal->j_committing_transaction == NULL);
	J_ASSERT(journal->j_checkpoint_transactions == NULL);
	spin_unlock(&journal->j_list_lock);

	if (journal->j_sb_buffer) {
		if (!is_journal_aborted(journal)) {
			mutex_lock_io(&journal->j_checkpoint_mutex);

			write_lock(&journal->j_state_lock);
			journal->j_tail_sequence =
				++journal->j_transaction_sequence;
			write_unlock(&journal->j_state_lock);

			jbd2_mark_journal_empty(journal,
					REQ_SYNC | REQ_PREFLUSH | REQ_FUA);
			mutex_unlock(&journal->j_checkpoint_mutex);
		} else
			err = -EIO;
		brelse(journal->j_sb_buffer);
	}

	if (journal->j_proc_entry)
		jbd2_stats_proc_exit(journal);
	iput(journal->j_inode);
	if (journal->j_revoke)
		jbd2_journal_destroy_revoke(journal);
	if (journal->j_chksum_driver)
		crypto_free_shash(journal->j_chksum_driver);
	kfree(journal->j_wbuf);
	kfree(journal);

	return err;
}