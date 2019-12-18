#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  t_handle_lock; int /*<<< orphan*/  t_tid; int /*<<< orphan*/  t_updates; int /*<<< orphan*/  t_outstanding_credits; TYPE_3__* t_journal; } ;
typedef  TYPE_2__ transaction_t ;
typedef  int /*<<< orphan*/  tid_t ;
struct TYPE_17__ {int /*<<< orphan*/  j_trans_commit_map; int /*<<< orphan*/  j_state_lock; int /*<<< orphan*/  j_commit_request; int /*<<< orphan*/  j_wait_updates; } ;
typedef  TYPE_3__ journal_t ;
struct TYPE_18__ {int h_buffer_credits; int /*<<< orphan*/  saved_alloc_context; TYPE_2__* h_transaction; TYPE_1__* h_rsv_handle; } ;
typedef  TYPE_4__ handle_t ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_15__ {int /*<<< orphan*/  h_buffer_credits; } ;
struct TYPE_14__ {int /*<<< orphan*/ * journal_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  J_ASSERT (int) ; 
 int /*<<< orphan*/  _THIS_IP_ ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 TYPE_13__* current ; 
 scalar_t__ is_handle_aborted (TYPE_4__*) ; 
 int /*<<< orphan*/  jbd2_log_start_commit (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd_debug (int,char*,TYPE_4__*) ; 
 TYPE_4__* journal_current_handle () ; 
 int /*<<< orphan*/  memalloc_nofs_restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwsem_release (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int start_this_handle (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sub_reserved_credits (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tid_geq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int jbd2__journal_restart(handle_t *handle, int nblocks, gfp_t gfp_mask)
{
	transaction_t *transaction = handle->h_transaction;
	journal_t *journal;
	tid_t		tid;
	int		need_to_start, ret;

	/* If we've had an abort of any type, don't even think about
	 * actually doing the restart! */
	if (is_handle_aborted(handle))
		return 0;
	journal = transaction->t_journal;

	/*
	 * First unlink the handle from its current transaction, and start the
	 * commit on that.
	 */
	J_ASSERT(atomic_read(&transaction->t_updates) > 0);
	J_ASSERT(journal_current_handle() == handle);

	read_lock(&journal->j_state_lock);
	spin_lock(&transaction->t_handle_lock);
	atomic_sub(handle->h_buffer_credits,
		   &transaction->t_outstanding_credits);
	if (handle->h_rsv_handle) {
		sub_reserved_credits(journal,
				     handle->h_rsv_handle->h_buffer_credits);
	}
	if (atomic_dec_and_test(&transaction->t_updates))
		wake_up(&journal->j_wait_updates);
	tid = transaction->t_tid;
	spin_unlock(&transaction->t_handle_lock);
	handle->h_transaction = NULL;
	current->journal_info = NULL;

	jbd_debug(2, "restarting handle %p\n", handle);
	need_to_start = !tid_geq(journal->j_commit_request, tid);
	read_unlock(&journal->j_state_lock);
	if (need_to_start)
		jbd2_log_start_commit(journal, tid);

	rwsem_release(&journal->j_trans_commit_map, 1, _THIS_IP_);
	handle->h_buffer_credits = nblocks;
	/*
	 * Restore the original nofs context because the journal restart
	 * is basically the same thing as journal stop and start.
	 * start_this_handle will start a new nofs context.
	 */
	memalloc_nofs_restore(handle->saved_alloc_context);
	ret = start_this_handle(journal, handle, gfp_mask);
	return ret;
}