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
struct TYPE_2__ {int in_sql_drop; int /*<<< orphan*/  SQLDropList; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  EventTriggerData ;

/* Variables and functions */
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  EVT_SQLDrop ; 
 int /*<<< orphan*/ * EventTriggerCommonSetup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EventTriggerInvoke (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsUnderPostmaster ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_FINALLY () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 TYPE_1__* currentEventTriggerState ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ *) ; 
 scalar_t__ slist_is_empty (int /*<<< orphan*/ *) ; 

void
EventTriggerSQLDrop(Node *parsetree)
{
	List	   *runlist;
	EventTriggerData trigdata;

	/*
	 * See EventTriggerDDLCommandStart for a discussion about why event
	 * triggers are disabled in single user mode.
	 */
	if (!IsUnderPostmaster)
		return;

	/*
	 * Use current state to determine whether this event fires at all.  If
	 * there are no triggers for the sql_drop event, then we don't have
	 * anything to do here.  Note that dropped object collection is disabled
	 * if this is the case, so even if we were to try to run, the list would
	 * be empty.
	 */
	if (!currentEventTriggerState ||
		slist_is_empty(&currentEventTriggerState->SQLDropList))
		return;

	runlist = EventTriggerCommonSetup(parsetree,
									  EVT_SQLDrop, "sql_drop",
									  &trigdata);

	/*
	 * Nothing to do if run list is empty.  Note this typically can't happen,
	 * because if there are no sql_drop events, then objects-to-drop wouldn't
	 * have been collected in the first place and we would have quit above.
	 * But it could occur if event triggers were dropped partway through.
	 */
	if (runlist == NIL)
		return;

	/*
	 * Make sure anything the main command did will be visible to the event
	 * triggers.
	 */
	CommandCounterIncrement();

	/*
	 * Make sure pg_event_trigger_dropped_objects only works when running
	 * these triggers.  Use PG_TRY to ensure in_sql_drop is reset even when
	 * one trigger fails.  (This is perhaps not necessary, as the currentState
	 * variable will be removed shortly by our caller, but it seems better to
	 * play safe.)
	 */
	currentEventTriggerState->in_sql_drop = true;

	/* Run the triggers. */
	PG_TRY();
	{
		EventTriggerInvoke(runlist, &trigdata);
	}
	PG_FINALLY();
	{
		currentEventTriggerState->in_sql_drop = false;
	}
	PG_END_TRY();

	/* Cleanup. */
	list_free(runlist);
}