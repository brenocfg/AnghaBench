#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * head; } ;
struct TYPE_6__ {int query_depth; int /*<<< orphan*/  firing_counter; TYPE_1__ events; } ;
typedef  int /*<<< orphan*/  CommandId ;
typedef  TYPE_1__ AfterTriggerEventList ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  GetTransactionSnapshot () ; 
 int /*<<< orphan*/  PopActiveSnapshot () ; 
 int /*<<< orphan*/  PushActiveSnapshot (int /*<<< orphan*/ ) ; 
 scalar_t__ afterTriggerInvokeEvents (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ afterTriggerMarkEvents (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 TYPE_2__ afterTriggers ; 

void
AfterTriggerFireDeferred(void)
{
	AfterTriggerEventList *events;
	bool		snap_pushed = false;

	/* Must not be inside a query */
	Assert(afterTriggers.query_depth == -1);

	/*
	 * If there are any triggers to fire, make sure we have set a snapshot for
	 * them to use.  (Since PortalRunUtility doesn't set a snap for COMMIT, we
	 * can't assume ActiveSnapshot is valid on entry.)
	 */
	events = &afterTriggers.events;
	if (events->head != NULL)
	{
		PushActiveSnapshot(GetTransactionSnapshot());
		snap_pushed = true;
	}

	/*
	 * Run all the remaining triggers.  Loop until they are all gone, in case
	 * some trigger queues more for us to do.
	 */
	while (afterTriggerMarkEvents(events, NULL, false))
	{
		CommandId	firing_id = afterTriggers.firing_counter++;

		if (afterTriggerInvokeEvents(events, firing_id, NULL, true))
			break;				/* all fired */
	}

	/*
	 * We don't bother freeing the event list, since it will go away anyway
	 * (and more efficiently than via pfree) in AfterTriggerEndXact.
	 */

	if (snap_pushed)
		PopActiveSnapshot();
}