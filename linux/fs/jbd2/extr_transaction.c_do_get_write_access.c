#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* t_journal; } ;
typedef  TYPE_2__ transaction_t ;
struct journal_head {char* b_frozen_data; scalar_t__ b_jlist; TYPE_2__* b_next_transaction; TYPE_2__* b_transaction; scalar_t__ b_modified; } ;
struct buffer_head {int /*<<< orphan*/  b_size; int /*<<< orphan*/  b_state; TYPE_1__* b_bdev; } ;
struct TYPE_11__ {TYPE_2__* j_committing_transaction; int /*<<< orphan*/  j_list_lock; } ;
typedef  TYPE_3__ journal_t ;
struct TYPE_12__ {TYPE_2__* h_transaction; } ;
typedef  TYPE_4__ handle_t ;
struct TYPE_9__ {int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BH_Shadow ; 
 scalar_t__ BJ_Metadata ; 
 int /*<<< orphan*/  BJ_Reserved ; 
 int EROFS ; 
 int GFP_NOFS ; 
 int HZ ; 
 int /*<<< orphan*/  JBUFFER_TRACE (struct journal_head*,char*) ; 
 int /*<<< orphan*/  J_ASSERT_JH (struct journal_head*,int) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int __GFP_NOFAIL ; 
 int /*<<< orphan*/  __jbd2_journal_file_buffer (struct journal_head*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 scalar_t__ buffer_shadow (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 scalar_t__ is_handle_aborted (TYPE_4__*) ; 
 char* jbd2_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jbd2_free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd2_freeze_jh_data (struct journal_head*) ; 
 int /*<<< orphan*/  jbd2_journal_cancel_revoke (TYPE_4__*,struct journal_head*) ; 
 unsigned long jbd2_time_diff (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  jbd_debug (int,char*,struct journal_head*,int) ; 
 int /*<<< orphan*/  jbd_lock_bh_state (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_unlock_bh_state (struct buffer_head*) ; 
 struct buffer_head* jh2bh (struct journal_head*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (unsigned long) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_jbddirty (struct buffer_head*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_jbd2_lock_buffer_stall (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (char*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  wait_on_bit_io (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn_dirty_buffer (struct buffer_head*) ; 

__attribute__((used)) static int
do_get_write_access(handle_t *handle, struct journal_head *jh,
			int force_copy)
{
	struct buffer_head *bh;
	transaction_t *transaction = handle->h_transaction;
	journal_t *journal;
	int error;
	char *frozen_buffer = NULL;
	unsigned long start_lock, time_lock;

	if (is_handle_aborted(handle))
		return -EROFS;
	journal = transaction->t_journal;

	jbd_debug(5, "journal_head %p, force_copy %d\n", jh, force_copy);

	JBUFFER_TRACE(jh, "entry");
repeat:
	bh = jh2bh(jh);

	/* @@@ Need to check for errors here at some point. */

 	start_lock = jiffies;
	lock_buffer(bh);
	jbd_lock_bh_state(bh);

	/* If it takes too long to lock the buffer, trace it */
	time_lock = jbd2_time_diff(start_lock, jiffies);
	if (time_lock > HZ/10)
		trace_jbd2_lock_buffer_stall(bh->b_bdev->bd_dev,
			jiffies_to_msecs(time_lock));

	/* We now hold the buffer lock so it is safe to query the buffer
	 * state.  Is the buffer dirty?
	 *
	 * If so, there are two possibilities.  The buffer may be
	 * non-journaled, and undergoing a quite legitimate writeback.
	 * Otherwise, it is journaled, and we don't expect dirty buffers
	 * in that state (the buffers should be marked JBD_Dirty
	 * instead.)  So either the IO is being done under our own
	 * control and this is a bug, or it's a third party IO such as
	 * dump(8) (which may leave the buffer scheduled for read ---
	 * ie. locked but not dirty) or tune2fs (which may actually have
	 * the buffer dirtied, ugh.)  */

	if (buffer_dirty(bh)) {
		/*
		 * First question: is this buffer already part of the current
		 * transaction or the existing committing transaction?
		 */
		if (jh->b_transaction) {
			J_ASSERT_JH(jh,
				jh->b_transaction == transaction ||
				jh->b_transaction ==
					journal->j_committing_transaction);
			if (jh->b_next_transaction)
				J_ASSERT_JH(jh, jh->b_next_transaction ==
							transaction);
			warn_dirty_buffer(bh);
		}
		/*
		 * In any case we need to clean the dirty flag and we must
		 * do it under the buffer lock to be sure we don't race
		 * with running write-out.
		 */
		JBUFFER_TRACE(jh, "Journalling dirty buffer");
		clear_buffer_dirty(bh);
		set_buffer_jbddirty(bh);
	}

	unlock_buffer(bh);

	error = -EROFS;
	if (is_handle_aborted(handle)) {
		jbd_unlock_bh_state(bh);
		goto out;
	}
	error = 0;

	/*
	 * The buffer is already part of this transaction if b_transaction or
	 * b_next_transaction points to it
	 */
	if (jh->b_transaction == transaction ||
	    jh->b_next_transaction == transaction)
		goto done;

	/*
	 * this is the first time this transaction is touching this buffer,
	 * reset the modified flag
	 */
	jh->b_modified = 0;

	/*
	 * If the buffer is not journaled right now, we need to make sure it
	 * doesn't get written to disk before the caller actually commits the
	 * new data
	 */
	if (!jh->b_transaction) {
		JBUFFER_TRACE(jh, "no transaction");
		J_ASSERT_JH(jh, !jh->b_next_transaction);
		JBUFFER_TRACE(jh, "file as BJ_Reserved");
		/*
		 * Make sure all stores to jh (b_modified, b_frozen_data) are
		 * visible before attaching it to the running transaction.
		 * Paired with barrier in jbd2_write_access_granted()
		 */
		smp_wmb();
		spin_lock(&journal->j_list_lock);
		__jbd2_journal_file_buffer(jh, transaction, BJ_Reserved);
		spin_unlock(&journal->j_list_lock);
		goto done;
	}
	/*
	 * If there is already a copy-out version of this buffer, then we don't
	 * need to make another one
	 */
	if (jh->b_frozen_data) {
		JBUFFER_TRACE(jh, "has frozen data");
		J_ASSERT_JH(jh, jh->b_next_transaction == NULL);
		goto attach_next;
	}

	JBUFFER_TRACE(jh, "owned by older transaction");
	J_ASSERT_JH(jh, jh->b_next_transaction == NULL);
	J_ASSERT_JH(jh, jh->b_transaction == journal->j_committing_transaction);

	/*
	 * There is one case we have to be very careful about.  If the
	 * committing transaction is currently writing this buffer out to disk
	 * and has NOT made a copy-out, then we cannot modify the buffer
	 * contents at all right now.  The essence of copy-out is that it is
	 * the extra copy, not the primary copy, which gets journaled.  If the
	 * primary copy is already going to disk then we cannot do copy-out
	 * here.
	 */
	if (buffer_shadow(bh)) {
		JBUFFER_TRACE(jh, "on shadow: sleep");
		jbd_unlock_bh_state(bh);
		wait_on_bit_io(&bh->b_state, BH_Shadow, TASK_UNINTERRUPTIBLE);
		goto repeat;
	}

	/*
	 * Only do the copy if the currently-owning transaction still needs it.
	 * If buffer isn't on BJ_Metadata list, the committing transaction is
	 * past that stage (here we use the fact that BH_Shadow is set under
	 * bh_state lock together with refiling to BJ_Shadow list and at this
	 * point we know the buffer doesn't have BH_Shadow set).
	 *
	 * Subtle point, though: if this is a get_undo_access, then we will be
	 * relying on the frozen_data to contain the new value of the
	 * committed_data record after the transaction, so we HAVE to force the
	 * frozen_data copy in that case.
	 */
	if (jh->b_jlist == BJ_Metadata || force_copy) {
		JBUFFER_TRACE(jh, "generate frozen data");
		if (!frozen_buffer) {
			JBUFFER_TRACE(jh, "allocate memory for buffer");
			jbd_unlock_bh_state(bh);
			frozen_buffer = jbd2_alloc(jh2bh(jh)->b_size,
						   GFP_NOFS | __GFP_NOFAIL);
			goto repeat;
		}
		jh->b_frozen_data = frozen_buffer;
		frozen_buffer = NULL;
		jbd2_freeze_jh_data(jh);
	}
attach_next:
	/*
	 * Make sure all stores to jh (b_modified, b_frozen_data) are visible
	 * before attaching it to the running transaction. Paired with barrier
	 * in jbd2_write_access_granted()
	 */
	smp_wmb();
	jh->b_next_transaction = transaction;

done:
	jbd_unlock_bh_state(bh);

	/*
	 * If we are about to journal a buffer, then any revoke pending on it is
	 * no longer valid
	 */
	jbd2_journal_cancel_revoke(handle, jh);

out:
	if (unlikely(frozen_buffer))	/* It's usually NULL */
		jbd2_free(frozen_buffer, bh->b_size);

	JBUFFER_TRACE(jh, "exit");
	return error;
}