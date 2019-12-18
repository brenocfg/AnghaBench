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
struct TYPE_10__ {TYPE_3__* currentCommand; int /*<<< orphan*/  commandList; scalar_t__ commandCollectionInhibited; } ;
struct TYPE_7__ {int /*<<< orphan*/  subcmds; } ;
struct TYPE_8__ {TYPE_1__ alterTable; } ;
struct TYPE_9__ {TYPE_2__ d; struct TYPE_9__* parent; } ;
typedef  TYPE_3__ CollectedCommand ;

/* Variables and functions */
 TYPE_6__* currentEventTriggerState ; 
 int /*<<< orphan*/  lappend (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_3__*) ; 

void
EventTriggerAlterTableEnd(void)
{
	CollectedCommand *parent;

	/* ignore if event trigger context not set, or collection disabled */
	if (!currentEventTriggerState ||
		currentEventTriggerState->commandCollectionInhibited)
		return;

	parent = currentEventTriggerState->currentCommand->parent;

	/* If no subcommands, don't collect */
	if (list_length(currentEventTriggerState->currentCommand->d.alterTable.subcmds) != 0)
	{
		currentEventTriggerState->commandList =
			lappend(currentEventTriggerState->commandList,
					currentEventTriggerState->currentCommand);
	}
	else
		pfree(currentEventTriggerState->currentCommand);

	currentEventTriggerState->currentCommand = parent;
}