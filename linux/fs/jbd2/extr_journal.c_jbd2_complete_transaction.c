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
typedef  scalar_t__ tid_t ;
struct TYPE_9__ {scalar_t__ j_commit_request; int /*<<< orphan*/  j_state_lock; TYPE_1__* j_committing_transaction; TYPE_2__* j_running_transaction; } ;
typedef  TYPE_3__ journal_t ;
struct TYPE_8__ {scalar_t__ t_tid; } ;
struct TYPE_7__ {scalar_t__ t_tid; } ;

/* Variables and functions */
 int /*<<< orphan*/  jbd2_log_start_commit (TYPE_3__*,scalar_t__) ; 
 int jbd2_log_wait_commit (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

int jbd2_complete_transaction(journal_t *journal, tid_t tid)
{
	int	need_to_wait = 1;

	read_lock(&journal->j_state_lock);
	if (journal->j_running_transaction &&
	    journal->j_running_transaction->t_tid == tid) {
		if (journal->j_commit_request != tid) {
			/* transaction not yet started, so request it */
			read_unlock(&journal->j_state_lock);
			jbd2_log_start_commit(journal, tid);
			goto wait_commit;
		}
	} else if (!(journal->j_committing_transaction &&
		     journal->j_committing_transaction->t_tid == tid))
		need_to_wait = 0;
	read_unlock(&journal->j_state_lock);
	if (!need_to_wait)
		return 0;
wait_commit:
	return jbd2_log_wait_commit(journal, tid);
}