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
struct TYPE_2__ {int my_level; int /*<<< orphan*/  PriorCmdInvalidMsgs; scalar_t__ RelcacheInitFileInval; int /*<<< orphan*/  CurrentCmdInvalidMsgs; int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  AppendInvalidationMessages (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  LocalExecuteInvalidationMessage ; 
 int /*<<< orphan*/  ProcessInvalidationMessages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcessInvalidationMessagesMulti (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationCacheInitFilePostInvalidate () ; 
 int /*<<< orphan*/  RelationCacheInitFilePreInvalidate () ; 
 int /*<<< orphan*/  SendSharedInvalidMessages ; 
 int /*<<< orphan*/ * SharedInvalidMessagesArray ; 
 scalar_t__ numSharedInvalidMessagesArray ; 
 TYPE_1__* transInvalInfo ; 

void
AtEOXact_Inval(bool isCommit)
{
	/* Quick exit if no messages */
	if (transInvalInfo == NULL)
		return;

	/* Must be at top of stack */
	Assert(transInvalInfo->my_level == 1 && transInvalInfo->parent == NULL);

	if (isCommit)
	{
		/*
		 * Relcache init file invalidation requires processing both before and
		 * after we send the SI messages.  However, we need not do anything
		 * unless we committed.
		 */
		if (transInvalInfo->RelcacheInitFileInval)
			RelationCacheInitFilePreInvalidate();

		AppendInvalidationMessages(&transInvalInfo->PriorCmdInvalidMsgs,
								   &transInvalInfo->CurrentCmdInvalidMsgs);

		ProcessInvalidationMessagesMulti(&transInvalInfo->PriorCmdInvalidMsgs,
										 SendSharedInvalidMessages);

		if (transInvalInfo->RelcacheInitFileInval)
			RelationCacheInitFilePostInvalidate();
	}
	else
	{
		ProcessInvalidationMessages(&transInvalInfo->PriorCmdInvalidMsgs,
									LocalExecuteInvalidationMessage);
	}

	/* Need not free anything explicitly */
	transInvalInfo = NULL;
	SharedInvalidMessagesArray = NULL;
	numSharedInvalidMessagesArray = 0;
}