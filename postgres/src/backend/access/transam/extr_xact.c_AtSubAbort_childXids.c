#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TransactionState ;
struct TYPE_3__ {scalar_t__ maxChildXids; scalar_t__ nChildXids; int /*<<< orphan*/ * childXids; } ;

/* Variables and functions */
 TYPE_1__* CurrentTransactionState ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
AtSubAbort_childXids(void)
{
	TransactionState s = CurrentTransactionState;

	/*
	 * We keep the child-XID arrays in TopTransactionContext (see
	 * AtSubCommit_childXids).  This means we'd better free the array
	 * explicitly at abort to avoid leakage.
	 */
	if (s->childXids != NULL)
		pfree(s->childXids);
	s->childXids = NULL;
	s->nChildXids = 0;
	s->maxChildXids = 0;

	/*
	 * We could prune the unreportedXids array here. But we don't bother. That
	 * would potentially reduce number of XLOG_XACT_ASSIGNMENT records but it
	 * would likely introduce more CPU time into the more common paths, so we
	 * choose not to do that.
	 */
}