#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * curTransactionContext; int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CurTransactionContext ; 
 TYPE_1__* CurrentTransactionState ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemoryContextResetAndDeleteChildren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/ * TopTransactionContext ; 
 int /*<<< orphan*/ * TransactionAbortContext ; 

__attribute__((used)) static void
AtCleanup_Memory(void)
{
	Assert(CurrentTransactionState->parent == NULL);

	/*
	 * Now that we're "out" of a transaction, have the system allocate things
	 * in the top memory context instead of per-transaction contexts.
	 */
	MemoryContextSwitchTo(TopMemoryContext);

	/*
	 * Clear the special abort context for next time.
	 */
	if (TransactionAbortContext != NULL)
		MemoryContextResetAndDeleteChildren(TransactionAbortContext);

	/*
	 * Release all transaction-local memory.
	 */
	if (TopTransactionContext != NULL)
		MemoryContextDelete(TopTransactionContext);
	TopTransactionContext = NULL;
	CurTransactionContext = NULL;
	CurrentTransactionState->curTransactionContext = NULL;
}