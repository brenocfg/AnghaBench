#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* currentCommand; int /*<<< orphan*/  cxt; scalar_t__ commandCollectionInhibited; } ;
struct TYPE_6__ {int /*<<< orphan*/  subcmds; int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
struct TYPE_7__ {TYPE_1__ alterTable; } ;
struct TYPE_8__ {struct TYPE_8__* parent; int /*<<< orphan*/  parsetree; TYPE_2__ d; int /*<<< orphan*/  in_extension; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_3__ CollectedCommand ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  SCT_AlterTable ; 
 int /*<<< orphan*/  copyObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  creating_extension ; 
 TYPE_5__* currentEventTriggerState ; 
 TYPE_3__* palloc (int) ; 

void
EventTriggerAlterTableStart(Node *parsetree)
{
	MemoryContext oldcxt;
	CollectedCommand *command;

	/* ignore if event trigger context not set, or collection disabled */
	if (!currentEventTriggerState ||
		currentEventTriggerState->commandCollectionInhibited)
		return;

	oldcxt = MemoryContextSwitchTo(currentEventTriggerState->cxt);

	command = palloc(sizeof(CollectedCommand));

	command->type = SCT_AlterTable;
	command->in_extension = creating_extension;

	command->d.alterTable.classId = RelationRelationId;
	command->d.alterTable.objectId = InvalidOid;
	command->d.alterTable.subcmds = NIL;
	command->parsetree = copyObject(parsetree);

	command->parent = currentEventTriggerState->currentCommand;
	currentEventTriggerState->currentCommand = command;

	MemoryContextSwitchTo(oldcxt);
}