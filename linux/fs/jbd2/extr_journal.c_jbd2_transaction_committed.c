#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tid_t ;
struct TYPE_7__ {int /*<<< orphan*/  j_state_lock; TYPE_2__* j_committing_transaction; TYPE_1__* j_running_transaction; } ;
typedef  TYPE_3__ journal_t ;
struct TYPE_6__ {scalar_t__ t_tid; } ;
struct TYPE_5__ {scalar_t__ t_tid; } ;

/* Variables and functions */
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

int jbd2_transaction_committed(journal_t *journal, tid_t tid)
{
	int ret = 1;

	read_lock(&journal->j_state_lock);
	if (journal->j_running_transaction &&
	    journal->j_running_transaction->t_tid == tid)
		ret = 0;
	if (journal->j_committing_transaction &&
	    journal->j_committing_transaction->t_tid == tid)
		ret = 0;
	read_unlock(&journal->j_state_lock);
	return ret;
}