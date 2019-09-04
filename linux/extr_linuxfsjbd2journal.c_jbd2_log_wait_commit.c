#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tid_t ;
struct TYPE_4__ {int /*<<< orphan*/  j_state_lock; int /*<<< orphan*/  j_commit_sequence; int /*<<< orphan*/  j_wait_done_commit; int /*<<< orphan*/  j_wait_commit; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  is_journal_aborted (TYPE_1__*) ; 
 int /*<<< orphan*/  jbd_debug (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ tid_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int jbd2_log_wait_commit(journal_t *journal, tid_t tid)
{
	int err = 0;

	read_lock(&journal->j_state_lock);
#ifdef CONFIG_PROVE_LOCKING
	/*
	 * Some callers make sure transaction is already committing and in that
	 * case we cannot block on open handles anymore. So don't warn in that
	 * case.
	 */
	if (tid_gt(tid, journal->j_commit_sequence) &&
	    (!journal->j_committing_transaction ||
	     journal->j_committing_transaction->t_tid != tid)) {
		read_unlock(&journal->j_state_lock);
		jbd2_might_wait_for_commit(journal);
		read_lock(&journal->j_state_lock);
	}
#endif
#ifdef CONFIG_JBD2_DEBUG
	if (!tid_geq(journal->j_commit_request, tid)) {
		printk(KERN_ERR
		       "%s: error: j_commit_request=%d, tid=%d\n",
		       __func__, journal->j_commit_request, tid);
	}
#endif
	while (tid_gt(tid, journal->j_commit_sequence)) {
		jbd_debug(1, "JBD2: want %d, j_commit_sequence=%d\n",
				  tid, journal->j_commit_sequence);
		read_unlock(&journal->j_state_lock);
		wake_up(&journal->j_wait_commit);
		wait_event(journal->j_wait_done_commit,
				!tid_gt(tid, journal->j_commit_sequence));
		read_lock(&journal->j_state_lock);
	}
	read_unlock(&journal->j_state_lock);

	if (unlikely(is_journal_aborted(journal)))
		err = -EIO;
	return err;
}