#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  t_handle_lock; int /*<<< orphan*/  t_updates; } ;
typedef  TYPE_1__ transaction_t ;
struct TYPE_6__ {int /*<<< orphan*/  j_barrier; int /*<<< orphan*/  j_state_lock; int /*<<< orphan*/  j_wait_updates; TYPE_1__* j_running_transaction; int /*<<< orphan*/  j_reserved_credits; int /*<<< orphan*/  j_wait_reserved; int /*<<< orphan*/  j_barrier_count; } ;
typedef  TYPE_2__ journal_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd2_might_wait_for_commit (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void jbd2_journal_lock_updates(journal_t *journal)
{
	DEFINE_WAIT(wait);

	jbd2_might_wait_for_commit(journal);

	write_lock(&journal->j_state_lock);
	++journal->j_barrier_count;

	/* Wait until there are no reserved handles */
	if (atomic_read(&journal->j_reserved_credits)) {
		write_unlock(&journal->j_state_lock);
		wait_event(journal->j_wait_reserved,
			   atomic_read(&journal->j_reserved_credits) == 0);
		write_lock(&journal->j_state_lock);
	}

	/* Wait until there are no running updates */
	while (1) {
		transaction_t *transaction = journal->j_running_transaction;

		if (!transaction)
			break;

		spin_lock(&transaction->t_handle_lock);
		prepare_to_wait(&journal->j_wait_updates, &wait,
				TASK_UNINTERRUPTIBLE);
		if (!atomic_read(&transaction->t_updates)) {
			spin_unlock(&transaction->t_handle_lock);
			finish_wait(&journal->j_wait_updates, &wait);
			break;
		}
		spin_unlock(&transaction->t_handle_lock);
		write_unlock(&journal->j_state_lock);
		schedule();
		finish_wait(&journal->j_wait_updates, &wait);
		write_lock(&journal->j_state_lock);
	}
	write_unlock(&journal->j_state_lock);

	/*
	 * We have now established a barrier against other normal updates, but
	 * we also need to barrier against other jbd2_journal_lock_updates() calls
	 * to make sure that we serialise special journal-locked operations
	 * too.
	 */
	mutex_lock(&journal->j_barrier);
}