#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  transaction_t ;
struct journal_head {scalar_t__ b_modified; int /*<<< orphan*/ * b_next_transaction; int /*<<< orphan*/  b_cp_transaction; int /*<<< orphan*/ * b_transaction; } ;
struct buffer_head {int /*<<< orphan*/ * b_bdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  j_state_lock; int /*<<< orphan*/  j_list_lock; int /*<<< orphan*/ * j_running_transaction; int /*<<< orphan*/ * j_committing_transaction; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int EBUSY ; 
 int /*<<< orphan*/  JBUFFER_TRACE (struct journal_head*,char*) ; 
 int /*<<< orphan*/  J_ASSERT_BH (struct buffer_head*,int) ; 
 int /*<<< orphan*/  J_ASSERT_JH (struct journal_head*,int) ; 
 int __dispose_buffer (struct journal_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __jbd2_journal_remove_checkpoint (struct journal_head*) ; 
 int /*<<< orphan*/  buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_jbd (struct buffer_head*) ; 
 scalar_t__ buffer_jbddirty (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_delay (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_jbddirty (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_new (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_req (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_unwritten (struct buffer_head*) ; 
 struct journal_head* jbd2_journal_grab_journal_head (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd2_journal_put_journal_head (struct journal_head*) ; 
 int /*<<< orphan*/  jbd_lock_bh_state (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_unlock_bh_state (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_freed (struct buffer_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int journal_unmap_buffer(journal_t *journal, struct buffer_head *bh,
				int partial_page)
{
	transaction_t *transaction;
	struct journal_head *jh;
	int may_free = 1;

	BUFFER_TRACE(bh, "entry");

	/*
	 * It is safe to proceed here without the j_list_lock because the
	 * buffers cannot be stolen by try_to_free_buffers as long as we are
	 * holding the page lock. --sct
	 */

	if (!buffer_jbd(bh))
		goto zap_buffer_unlocked;

	/* OK, we have data buffer in journaled mode */
	write_lock(&journal->j_state_lock);
	jbd_lock_bh_state(bh);
	spin_lock(&journal->j_list_lock);

	jh = jbd2_journal_grab_journal_head(bh);
	if (!jh)
		goto zap_buffer_no_jh;

	/*
	 * We cannot remove the buffer from checkpoint lists until the
	 * transaction adding inode to orphan list (let's call it T)
	 * is committed.  Otherwise if the transaction changing the
	 * buffer would be cleaned from the journal before T is
	 * committed, a crash will cause that the correct contents of
	 * the buffer will be lost.  On the other hand we have to
	 * clear the buffer dirty bit at latest at the moment when the
	 * transaction marking the buffer as freed in the filesystem
	 * structures is committed because from that moment on the
	 * block can be reallocated and used by a different page.
	 * Since the block hasn't been freed yet but the inode has
	 * already been added to orphan list, it is safe for us to add
	 * the buffer to BJ_Forget list of the newest transaction.
	 *
	 * Also we have to clear buffer_mapped flag of a truncated buffer
	 * because the buffer_head may be attached to the page straddling
	 * i_size (can happen only when blocksize < pagesize) and thus the
	 * buffer_head can be reused when the file is extended again. So we end
	 * up keeping around invalidated buffers attached to transactions'
	 * BJ_Forget list just to stop checkpointing code from cleaning up
	 * the transaction this buffer was modified in.
	 */
	transaction = jh->b_transaction;
	if (transaction == NULL) {
		/* First case: not on any transaction.  If it
		 * has no checkpoint link, then we can zap it:
		 * it's a writeback-mode buffer so we don't care
		 * if it hits disk safely. */
		if (!jh->b_cp_transaction) {
			JBUFFER_TRACE(jh, "not on any transaction: zap");
			goto zap_buffer;
		}

		if (!buffer_dirty(bh)) {
			/* bdflush has written it.  We can drop it now */
			__jbd2_journal_remove_checkpoint(jh);
			goto zap_buffer;
		}

		/* OK, it must be in the journal but still not
		 * written fully to disk: it's metadata or
		 * journaled data... */

		if (journal->j_running_transaction) {
			/* ... and once the current transaction has
			 * committed, the buffer won't be needed any
			 * longer. */
			JBUFFER_TRACE(jh, "checkpointed: add to BJ_Forget");
			may_free = __dispose_buffer(jh,
					journal->j_running_transaction);
			goto zap_buffer;
		} else {
			/* There is no currently-running transaction. So the
			 * orphan record which we wrote for this file must have
			 * passed into commit.  We must attach this buffer to
			 * the committing transaction, if it exists. */
			if (journal->j_committing_transaction) {
				JBUFFER_TRACE(jh, "give to committing trans");
				may_free = __dispose_buffer(jh,
					journal->j_committing_transaction);
				goto zap_buffer;
			} else {
				/* The orphan record's transaction has
				 * committed.  We can cleanse this buffer */
				clear_buffer_jbddirty(bh);
				__jbd2_journal_remove_checkpoint(jh);
				goto zap_buffer;
			}
		}
	} else if (transaction == journal->j_committing_transaction) {
		JBUFFER_TRACE(jh, "on committing transaction");
		/*
		 * The buffer is committing, we simply cannot touch
		 * it. If the page is straddling i_size we have to wait
		 * for commit and try again.
		 */
		if (partial_page) {
			jbd2_journal_put_journal_head(jh);
			spin_unlock(&journal->j_list_lock);
			jbd_unlock_bh_state(bh);
			write_unlock(&journal->j_state_lock);
			return -EBUSY;
		}
		/*
		 * OK, buffer won't be reachable after truncate. We just set
		 * j_next_transaction to the running transaction (if there is
		 * one) and mark buffer as freed so that commit code knows it
		 * should clear dirty bits when it is done with the buffer.
		 */
		set_buffer_freed(bh);
		if (journal->j_running_transaction && buffer_jbddirty(bh))
			jh->b_next_transaction = journal->j_running_transaction;
		jbd2_journal_put_journal_head(jh);
		spin_unlock(&journal->j_list_lock);
		jbd_unlock_bh_state(bh);
		write_unlock(&journal->j_state_lock);
		return 0;
	} else {
		/* Good, the buffer belongs to the running transaction.
		 * We are writing our own transaction's data, not any
		 * previous one's, so it is safe to throw it away
		 * (remember that we expect the filesystem to have set
		 * i_size already for this truncate so recovery will not
		 * expose the disk blocks we are discarding here.) */
		J_ASSERT_JH(jh, transaction == journal->j_running_transaction);
		JBUFFER_TRACE(jh, "on running transaction");
		may_free = __dispose_buffer(jh, transaction);
	}

zap_buffer:
	/*
	 * This is tricky. Although the buffer is truncated, it may be reused
	 * if blocksize < pagesize and it is attached to the page straddling
	 * EOF. Since the buffer might have been added to BJ_Forget list of the
	 * running transaction, journal_get_write_access() won't clear
	 * b_modified and credit accounting gets confused. So clear b_modified
	 * here.
	 */
	jh->b_modified = 0;
	jbd2_journal_put_journal_head(jh);
zap_buffer_no_jh:
	spin_unlock(&journal->j_list_lock);
	jbd_unlock_bh_state(bh);
	write_unlock(&journal->j_state_lock);
zap_buffer_unlocked:
	clear_buffer_dirty(bh);
	J_ASSERT_BH(bh, !buffer_jbddirty(bh));
	clear_buffer_mapped(bh);
	clear_buffer_req(bh);
	clear_buffer_new(bh);
	clear_buffer_delay(bh);
	clear_buffer_unwritten(bh);
	bh->b_bdev = NULL;
	return may_free;
}