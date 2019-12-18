#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int numstates; int /*<<< orphan*/  trigstates; int /*<<< orphan*/  all_isdeferred; int /*<<< orphan*/  all_isset; } ;
typedef  int /*<<< orphan*/  SetConstraintTriggerData ;
typedef  TYPE_1__* SetConstraintState ;

/* Variables and functions */
 TYPE_1__* SetConstraintStateCreate (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static SetConstraintState
SetConstraintStateCopy(SetConstraintState origstate)
{
	SetConstraintState state;

	state = SetConstraintStateCreate(origstate->numstates);

	state->all_isset = origstate->all_isset;
	state->all_isdeferred = origstate->all_isdeferred;
	state->numstates = origstate->numstates;
	memcpy(state->trigstates, origstate->trigstates,
		   origstate->numstates * sizeof(SetConstraintTriggerData));

	return state;
}