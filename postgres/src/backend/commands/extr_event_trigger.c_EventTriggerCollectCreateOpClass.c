#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  commandList; int /*<<< orphan*/  cxt; scalar_t__ commandCollectionInhibited; } ;
struct TYPE_7__ {int /*<<< orphan*/ * procedures; int /*<<< orphan*/ * operators; int /*<<< orphan*/  address; } ;
struct TYPE_8__ {TYPE_1__ createopc; } ;
struct TYPE_9__ {int /*<<< orphan*/ * parsetree; TYPE_2__ d; int /*<<< orphan*/  in_extension; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  CreateOpClassStmt ;
typedef  TYPE_3__ CollectedCommand ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectAddressSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OperatorClassRelationId ; 
 int /*<<< orphan*/  SCT_CreateOpClass ; 
 scalar_t__ copyObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  creating_extension ; 
 TYPE_6__* currentEventTriggerState ; 
 int /*<<< orphan*/  lappend (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_3__* palloc0 (int) ; 

void
EventTriggerCollectCreateOpClass(CreateOpClassStmt *stmt, Oid opcoid,
								 List *operators, List *procedures)
{
	MemoryContext oldcxt;
	CollectedCommand *command;

	/* ignore if event trigger context not set, or collection disabled */
	if (!currentEventTriggerState ||
		currentEventTriggerState->commandCollectionInhibited)
		return;

	oldcxt = MemoryContextSwitchTo(currentEventTriggerState->cxt);

	command = palloc0(sizeof(CollectedCommand));
	command->type = SCT_CreateOpClass;
	command->in_extension = creating_extension;
	ObjectAddressSet(command->d.createopc.address,
					 OperatorClassRelationId, opcoid);
	command->d.createopc.operators = operators;
	command->d.createopc.procedures = procedures;
	command->parsetree = (Node *) copyObject(stmt);

	currentEventTriggerState->commandList =
		lappend(currentEventTriggerState->commandList, command);

	MemoryContextSwitchTo(oldcxt);
}