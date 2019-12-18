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
struct TYPE_2__ {int table_rewrite_reason; int /*<<< orphan*/  table_rewrite_oid; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  EventTriggerData ;

/* Variables and functions */
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  EVT_TableRewrite ; 
 int /*<<< orphan*/ * EventTriggerCommonSetup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EventTriggerInvoke (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  IsUnderPostmaster ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_FINALLY () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 TYPE_1__* currentEventTriggerState ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ *) ; 

void
EventTriggerTableRewrite(Node *parsetree, Oid tableOid, int reason)
{
	List	   *runlist;
	EventTriggerData trigdata;

	/*
	 * Event Triggers are completely disabled in standalone mode.  There are
	 * (at least) two reasons for this:
	 *
	 * 1. A sufficiently broken event trigger might not only render the
	 * database unusable, but prevent disabling itself to fix the situation.
	 * In this scenario, restarting in standalone mode provides an escape
	 * hatch.
	 *
	 * 2. BuildEventTriggerCache relies on systable_beginscan_ordered, and
	 * therefore will malfunction if pg_event_trigger's indexes are damaged.
	 * To allow recovery from a damaged index, we need some operating mode
	 * wherein event triggers are disabled.  (Or we could implement
	 * heapscan-and-sort logic for that case, but having disaster recovery
	 * scenarios depend on code that's otherwise untested isn't appetizing.)
	 */
	if (!IsUnderPostmaster)
		return;

	/*
	 * Also do nothing if our state isn't set up, which it won't be if there
	 * weren't any relevant event triggers at the start of the current DDL
	 * command.  This test might therefore seem optional, but it's
	 * *necessary*, because EventTriggerCommonSetup might find triggers that
	 * didn't exist at the time the command started.
	 */
	if (!currentEventTriggerState)
		return;

	runlist = EventTriggerCommonSetup(parsetree,
									  EVT_TableRewrite,
									  "table_rewrite",
									  &trigdata);
	if (runlist == NIL)
		return;

	/*
	 * Make sure pg_event_trigger_table_rewrite_oid only works when running
	 * these triggers. Use PG_TRY to ensure table_rewrite_oid is reset even
	 * when one trigger fails. (This is perhaps not necessary, as the
	 * currentState variable will be removed shortly by our caller, but it
	 * seems better to play safe.)
	 */
	currentEventTriggerState->table_rewrite_oid = tableOid;
	currentEventTriggerState->table_rewrite_reason = reason;

	/* Run the triggers. */
	PG_TRY();
	{
		EventTriggerInvoke(runlist, &trigdata);
	}
	PG_FINALLY();
	{
		currentEventTriggerState->table_rewrite_oid = InvalidOid;
		currentEventTriggerState->table_rewrite_reason = 0;
	}
	PG_END_TRY();

	/* Cleanup. */
	list_free(runlist);

	/*
	 * Make sure anything the event triggers did will be visible to the main
	 * command.
	 */
	CommandCounterIncrement();
}