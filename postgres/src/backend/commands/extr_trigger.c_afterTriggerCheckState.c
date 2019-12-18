#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* state; } ;
struct TYPE_8__ {scalar_t__ ats_tgoid; int ats_event; } ;
struct TYPE_7__ {int numstates; int all_isdeferred; scalar_t__ all_isset; TYPE_1__* trigstates; } ;
struct TYPE_6__ {scalar_t__ sct_tgoid; int sct_tgisdeferred; } ;
typedef  TYPE_2__* SetConstraintState ;
typedef  scalar_t__ Oid ;
typedef  TYPE_3__* AfterTriggerShared ;

/* Variables and functions */
 int AFTER_TRIGGER_DEFERRABLE ; 
 int AFTER_TRIGGER_INITDEFERRED ; 
 TYPE_4__ afterTriggers ; 

__attribute__((used)) static bool
afterTriggerCheckState(AfterTriggerShared evtshared)
{
	Oid			tgoid = evtshared->ats_tgoid;
	SetConstraintState state = afterTriggers.state;
	int			i;

	/*
	 * For not-deferrable triggers (i.e. normal AFTER ROW triggers and
	 * constraints declared NOT DEFERRABLE), the state is always false.
	 */
	if ((evtshared->ats_event & AFTER_TRIGGER_DEFERRABLE) == 0)
		return false;

	/*
	 * If constraint state exists, SET CONSTRAINTS might have been executed
	 * either for this trigger or for all triggers.
	 */
	if (state != NULL)
	{
		/* Check for SET CONSTRAINTS for this specific trigger. */
		for (i = 0; i < state->numstates; i++)
		{
			if (state->trigstates[i].sct_tgoid == tgoid)
				return state->trigstates[i].sct_tgisdeferred;
		}

		/* Check for SET CONSTRAINTS ALL. */
		if (state->all_isset)
			return state->all_isdeferred;
	}

	/*
	 * Otherwise return the default state for the trigger.
	 */
	return ((evtshared->ats_event & AFTER_TRIGGER_INITDEFERRED) != 0);
}