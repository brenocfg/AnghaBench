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
struct TYPE_3__ {int /*<<< orphan*/ * curTransactionContext; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 void* AllocSetContextCreate (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CurTransactionContext ; 
 TYPE_1__* CurrentTransactionState ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/ * TopTransactionContext ; 
 int /*<<< orphan*/ * TransactionAbortContext ; 

__attribute__((used)) static void
AtStart_Memory(void)
{
	TransactionState s = CurrentTransactionState;

	/*
	 * If this is the first time through, create a private context for
	 * AbortTransaction to work in.  By reserving some space now, we can
	 * insulate AbortTransaction from out-of-memory scenarios.  Like
	 * ErrorContext, we set it up with slow growth rate and a nonzero minimum
	 * size, so that space will be reserved immediately.
	 */
	if (TransactionAbortContext == NULL)
		TransactionAbortContext =
			AllocSetContextCreate(TopMemoryContext,
								  "TransactionAbortContext",
								  32 * 1024,
								  32 * 1024,
								  32 * 1024);

	/*
	 * We shouldn't have a transaction context already.
	 */
	Assert(TopTransactionContext == NULL);

	/*
	 * Create a toplevel context for the transaction.
	 */
	TopTransactionContext =
		AllocSetContextCreate(TopMemoryContext,
							  "TopTransactionContext",
							  ALLOCSET_DEFAULT_SIZES);

	/*
	 * In a top-level transaction, CurTransactionContext is the same as
	 * TopTransactionContext.
	 */
	CurTransactionContext = TopTransactionContext;
	s->curTransactionContext = CurTransactionContext;

	/* Make the CurTransactionContext active. */
	MemoryContextSwitchTo(CurTransactionContext);
}