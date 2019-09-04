#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long t_log_start; int /*<<< orphan*/  t_tid; } ;
typedef  TYPE_1__ transaction_t ;
typedef  int /*<<< orphan*/  tid_t ;
struct TYPE_5__ {unsigned long j_head; int /*<<< orphan*/  j_state_lock; int /*<<< orphan*/  j_list_lock; int /*<<< orphan*/  j_tail_sequence; int /*<<< orphan*/  j_transaction_sequence; TYPE_1__* j_running_transaction; TYPE_1__* j_committing_transaction; TYPE_1__* j_checkpoint_transactions; } ;
typedef  TYPE_2__ journal_t ;

/* Variables and functions */
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int tid_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int jbd2_journal_get_log_tail(journal_t *journal, tid_t *tid,
			      unsigned long *block)
{
	transaction_t *transaction;
	int ret;

	read_lock(&journal->j_state_lock);
	spin_lock(&journal->j_list_lock);
	transaction = journal->j_checkpoint_transactions;
	if (transaction) {
		*tid = transaction->t_tid;
		*block = transaction->t_log_start;
	} else if ((transaction = journal->j_committing_transaction) != NULL) {
		*tid = transaction->t_tid;
		*block = transaction->t_log_start;
	} else if ((transaction = journal->j_running_transaction) != NULL) {
		*tid = transaction->t_tid;
		*block = journal->j_head;
	} else {
		*tid = journal->j_transaction_sequence;
		*block = journal->j_head;
	}
	ret = tid_gt(*tid, journal->j_tail_sequence);
	spin_unlock(&journal->j_list_lock);
	read_unlock(&journal->j_state_lock);

	return ret;
}