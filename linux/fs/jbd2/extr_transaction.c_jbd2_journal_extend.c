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
struct TYPE_10__ {scalar_t__ t_state; int /*<<< orphan*/  t_handle_lock; int /*<<< orphan*/  t_tid; int /*<<< orphan*/  t_outstanding_credits; TYPE_3__* t_journal; } ;
typedef  TYPE_2__ transaction_t ;
struct TYPE_11__ {int j_max_transaction_buffers; int /*<<< orphan*/  j_state_lock; TYPE_1__* j_fs_dev; } ;
typedef  TYPE_3__ journal_t ;
struct TYPE_12__ {int h_buffer_credits; int h_requested_credits; int /*<<< orphan*/  h_line_no; int /*<<< orphan*/  h_type; TYPE_2__* h_transaction; } ;
typedef  TYPE_4__ handle_t ;
struct TYPE_9__ {int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 int EROFS ; 
 int JBD2_CONTROL_BLOCKS_SHIFT ; 
 scalar_t__ T_RUNNING ; 
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 scalar_t__ is_handle_aborted (TYPE_4__*) ; 
 int jbd2_log_space_left (TYPE_3__*) ; 
 int /*<<< orphan*/  jbd_debug (int,char*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_jbd2_handle_extend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

int jbd2_journal_extend(handle_t *handle, int nblocks)
{
	transaction_t *transaction = handle->h_transaction;
	journal_t *journal;
	int result;
	int wanted;

	if (is_handle_aborted(handle))
		return -EROFS;
	journal = transaction->t_journal;

	result = 1;

	read_lock(&journal->j_state_lock);

	/* Don't extend a locked-down transaction! */
	if (transaction->t_state != T_RUNNING) {
		jbd_debug(3, "denied handle %p %d blocks: "
			  "transaction not running\n", handle, nblocks);
		goto error_out;
	}

	spin_lock(&transaction->t_handle_lock);
	wanted = atomic_add_return(nblocks,
				   &transaction->t_outstanding_credits);

	if (wanted > journal->j_max_transaction_buffers) {
		jbd_debug(3, "denied handle %p %d blocks: "
			  "transaction too large\n", handle, nblocks);
		atomic_sub(nblocks, &transaction->t_outstanding_credits);
		goto unlock;
	}

	if (wanted + (wanted >> JBD2_CONTROL_BLOCKS_SHIFT) >
	    jbd2_log_space_left(journal)) {
		jbd_debug(3, "denied handle %p %d blocks: "
			  "insufficient log space\n", handle, nblocks);
		atomic_sub(nblocks, &transaction->t_outstanding_credits);
		goto unlock;
	}

	trace_jbd2_handle_extend(journal->j_fs_dev->bd_dev,
				 transaction->t_tid,
				 handle->h_type, handle->h_line_no,
				 handle->h_buffer_credits,
				 nblocks);

	handle->h_buffer_credits += nblocks;
	handle->h_requested_credits += nblocks;
	result = 0;

	jbd_debug(3, "extended handle %p by %d\n", handle, nblocks);
unlock:
	spin_unlock(&transaction->t_handle_lock);
error_out:
	read_unlock(&journal->j_state_lock);
	return result;
}