#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int in_sql_drop; int commandCollectionInhibited; struct TYPE_4__* previous; int /*<<< orphan*/  commandList; int /*<<< orphan*/ * currentCommand; int /*<<< orphan*/  table_rewrite_oid; int /*<<< orphan*/  SQLDropList; int /*<<< orphan*/  cxt; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ EventTriggerQueryState ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 TYPE_1__* MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 TYPE_1__* currentEventTriggerState ; 
 int /*<<< orphan*/  slist_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trackDroppedObjectsNeeded () ; 

bool
EventTriggerBeginCompleteQuery(void)
{
	EventTriggerQueryState *state;
	MemoryContext cxt;

	/*
	 * Currently, sql_drop, table_rewrite, ddl_command_end events are the only
	 * reason to have event trigger state at all; so if there are none, don't
	 * install one.
	 */
	if (!trackDroppedObjectsNeeded())
		return false;

	cxt = AllocSetContextCreate(TopMemoryContext,
								"event trigger state",
								ALLOCSET_DEFAULT_SIZES);
	state = MemoryContextAlloc(cxt, sizeof(EventTriggerQueryState));
	state->cxt = cxt;
	slist_init(&(state->SQLDropList));
	state->in_sql_drop = false;
	state->table_rewrite_oid = InvalidOid;

	state->commandCollectionInhibited = currentEventTriggerState ?
		currentEventTriggerState->commandCollectionInhibited : false;
	state->currentCommand = NULL;
	state->commandList = NIL;
	state->previous = currentEventTriggerState;
	currentEventTriggerState = state;

	return true;
}