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
struct TYPE_4__ {int /*<<< orphan*/  j_list_lock; int /*<<< orphan*/  j_checkpoint_transactions; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 int /*<<< orphan*/  __jbd2_journal_clean_checkpoint_list (TYPE_1__*,int) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void jbd2_journal_destroy_checkpoint(journal_t *journal)
{
	/*
	 * We loop because __jbd2_journal_clean_checkpoint_list() may abort
	 * early due to a need of rescheduling.
	 */
	while (1) {
		spin_lock(&journal->j_list_lock);
		if (!journal->j_checkpoint_transactions) {
			spin_unlock(&journal->j_list_lock);
			break;
		}
		__jbd2_journal_clean_checkpoint_list(journal, true);
		spin_unlock(&journal->j_list_lock);
		cond_resched();
	}
}