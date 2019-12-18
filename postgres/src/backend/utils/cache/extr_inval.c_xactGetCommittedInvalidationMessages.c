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
struct TYPE_2__ {int my_level; int RelcacheInitFileInval; int /*<<< orphan*/  PriorCmdInvalidMsgs; int /*<<< orphan*/  CurrentCmdInvalidMsgs; int /*<<< orphan*/ * parent; } ;
typedef  int /*<<< orphan*/  SharedInvalidationMessage ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CurTransactionContext ; 
 int /*<<< orphan*/  MakeSharedInvalidMessagesArray ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcessInvalidationMessagesMulti (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SharedInvalidMessagesArray ; 
 scalar_t__ numSharedInvalidMessagesArray ; 
 TYPE_1__* transInvalInfo ; 

int
xactGetCommittedInvalidationMessages(SharedInvalidationMessage **msgs,
									 bool *RelcacheInitFileInval)
{
	MemoryContext oldcontext;

	/* Quick exit if we haven't done anything with invalidation messages. */
	if (transInvalInfo == NULL)
	{
		*RelcacheInitFileInval = false;
		*msgs = NULL;
		return 0;
	}

	/* Must be at top of stack */
	Assert(transInvalInfo->my_level == 1 && transInvalInfo->parent == NULL);

	/*
	 * Relcache init file invalidation requires processing both before and
	 * after we send the SI messages.  However, we need not do anything unless
	 * we committed.
	 */
	*RelcacheInitFileInval = transInvalInfo->RelcacheInitFileInval;

	/*
	 * Walk through TransInvalidationInfo to collect all the messages into a
	 * single contiguous array of invalidation messages. It must be contiguous
	 * so we can copy directly into WAL message. Maintain the order that they
	 * would be processed in by AtEOXact_Inval(), to ensure emulated behaviour
	 * in redo is as similar as possible to original. We want the same bugs,
	 * if any, not new ones.
	 */
	oldcontext = MemoryContextSwitchTo(CurTransactionContext);

	ProcessInvalidationMessagesMulti(&transInvalInfo->CurrentCmdInvalidMsgs,
									 MakeSharedInvalidMessagesArray);
	ProcessInvalidationMessagesMulti(&transInvalInfo->PriorCmdInvalidMsgs,
									 MakeSharedInvalidMessagesArray);
	MemoryContextSwitchTo(oldcontext);

	Assert(!(numSharedInvalidMessagesArray > 0 &&
			 SharedInvalidMessagesArray == NULL));

	*msgs = SharedInvalidMessagesArray;

	return numSharedInvalidMessagesArray;
}