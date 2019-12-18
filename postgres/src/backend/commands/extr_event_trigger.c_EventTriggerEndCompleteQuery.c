#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cxt; struct TYPE_3__* previous; } ;
typedef  TYPE_1__ EventTriggerQueryState ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 TYPE_1__* currentEventTriggerState ; 

void
EventTriggerEndCompleteQuery(void)
{
	EventTriggerQueryState *prevstate;

	prevstate = currentEventTriggerState->previous;

	/* this avoids the need for retail pfree of SQLDropList items: */
	MemoryContextDelete(currentEventTriggerState->cxt);

	currentEventTriggerState = prevstate;
}