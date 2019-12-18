#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nestingLevel; struct TYPE_6__* upper; } ;
typedef  TYPE_1__ NotificationList ;
typedef  TYPE_1__ ActionList ;

/* Variables and functions */
 int GetCurrentTransactionNestLevel () ; 
 TYPE_1__* pendingActions ; 
 TYPE_1__* pendingNotifies ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

void
AtSubAbort_Notify(void)
{
	int			my_level = GetCurrentTransactionNestLevel();

	/*
	 * All we have to do is pop the stack --- the actions/notifies made in
	 * this subxact are no longer interesting, and the space will be freed
	 * when CurTransactionContext is recycled. We still have to free the
	 * ActionList and NotificationList objects themselves, though, because
	 * those are allocated in TopTransactionContext.
	 *
	 * Note that there might be no entries at all, or no entries for the
	 * current subtransaction level, either because none were ever created,
	 * or because we reentered this routine due to trouble during subxact
	 * abort.
	 */
	while (pendingActions != NULL &&
		   pendingActions->nestingLevel >= my_level)
	{
		ActionList *childPendingActions = pendingActions;

		pendingActions = pendingActions->upper;
		pfree(childPendingActions);
	}

	while (pendingNotifies != NULL &&
		   pendingNotifies->nestingLevel >= my_level)
	{
		NotificationList *childPendingNotifies = pendingNotifies;

		pendingNotifies = pendingNotifies->upper;
		pfree(childPendingNotifies);
	}
}