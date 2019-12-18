#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  EventTriggerData ;

/* Variables and functions */
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  EVT_DDLCommandStart ; 
 int /*<<< orphan*/ * EventTriggerCommonSetup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EventTriggerInvoke (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsUnderPostmaster ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ *) ; 

void
EventTriggerDDLCommandStart(Node *parsetree)
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

	runlist = EventTriggerCommonSetup(parsetree,
									  EVT_DDLCommandStart,
									  "ddl_command_start",
									  &trigdata);
	if (runlist == NIL)
		return;

	/* Run the triggers. */
	EventTriggerInvoke(runlist, &trigdata);

	/* Cleanup. */
	list_free(runlist);

	/*
	 * Make sure anything the event triggers did will be visible to the main
	 * command.
	 */
	CommandCounterIncrement();
}