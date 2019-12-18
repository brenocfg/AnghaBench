#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_3__* currentCommand; int /*<<< orphan*/  cxt; scalar_t__ commandCollectionInhibited; } ;
struct TYPE_11__ {int /*<<< orphan*/  parsetree; int /*<<< orphan*/  address; } ;
struct TYPE_8__ {int /*<<< orphan*/  subcmds; int /*<<< orphan*/  objectId; } ;
struct TYPE_9__ {TYPE_1__ alterTable; } ;
struct TYPE_10__ {TYPE_2__ d; } ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_4__ CollectedATSubcmd ;

/* Variables and functions */
 int /*<<< orphan*/  AlterTableCmd ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copyObject (int /*<<< orphan*/ *) ; 
 TYPE_7__* currentEventTriggerState ; 
 int /*<<< orphan*/  lappend (int /*<<< orphan*/ ,TYPE_4__*) ; 
 TYPE_4__* palloc (int) ; 

void
EventTriggerCollectAlterTableSubcmd(Node *subcmd, ObjectAddress address)
{
	MemoryContext oldcxt;
	CollectedATSubcmd *newsub;

	/* ignore if event trigger context not set, or collection disabled */
	if (!currentEventTriggerState ||
		currentEventTriggerState->commandCollectionInhibited)
		return;

	Assert(IsA(subcmd, AlterTableCmd));
	Assert(currentEventTriggerState->currentCommand != NULL);
	Assert(OidIsValid(currentEventTriggerState->currentCommand->d.alterTable.objectId));

	oldcxt = MemoryContextSwitchTo(currentEventTriggerState->cxt);

	newsub = palloc(sizeof(CollectedATSubcmd));
	newsub->address = address;
	newsub->parsetree = copyObject(subcmd);

	currentEventTriggerState->currentCommand->d.alterTable.subcmds =
		lappend(currentEventTriggerState->currentCommand->d.alterTable.subcmds, newsub);

	MemoryContextSwitchTo(oldcxt);
}