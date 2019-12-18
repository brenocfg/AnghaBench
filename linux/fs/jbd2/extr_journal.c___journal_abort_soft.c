#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int j_errno; int j_flags; int /*<<< orphan*/  j_state_lock; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 int ESHUTDOWN ; 
 int JBD2_ABORT ; 
 int JBD2_REC_ERR ; 
 int /*<<< orphan*/  __jbd2_journal_abort_hard (TYPE_1__*) ; 
 int /*<<< orphan*/  jbd2_journal_update_sb_errno (TYPE_1__*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __journal_abort_soft (journal_t *journal, int errno)
{
	int old_errno;

	write_lock(&journal->j_state_lock);
	old_errno = journal->j_errno;
	if (!journal->j_errno || errno == -ESHUTDOWN)
		journal->j_errno = errno;

	if (journal->j_flags & JBD2_ABORT) {
		write_unlock(&journal->j_state_lock);
		if (!old_errno && old_errno != -ESHUTDOWN &&
		    errno == -ESHUTDOWN)
			jbd2_journal_update_sb_errno(journal);
		return;
	}
	write_unlock(&journal->j_state_lock);

	__jbd2_journal_abort_hard(journal);

	if (errno) {
		jbd2_journal_update_sb_errno(journal);
		write_lock(&journal->j_state_lock);
		journal->j_flags |= JBD2_REC_ERR;
		write_unlock(&journal->j_state_lock);
	}
}