#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int numstates; int numalloc; TYPE_1__* trigstates; } ;
struct TYPE_6__ {int sct_tgisdeferred; int /*<<< orphan*/  sct_tgoid; } ;
typedef  int /*<<< orphan*/  SetConstraintTriggerData ;
typedef  TYPE_2__* SetConstraintState ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int Max (int,int) ; 
 int /*<<< orphan*/  SetConstraintStateData ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ repalloc (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  trigstates ; 

__attribute__((used)) static SetConstraintState
SetConstraintStateAddItem(SetConstraintState state,
						  Oid tgoid, bool tgisdeferred)
{
	if (state->numstates >= state->numalloc)
	{
		int			newalloc = state->numalloc * 2;

		newalloc = Max(newalloc, 8);	/* in case original has size 0 */
		state = (SetConstraintState)
			repalloc(state,
					 offsetof(SetConstraintStateData, trigstates) +
					 newalloc * sizeof(SetConstraintTriggerData));
		state->numalloc = newalloc;
		Assert(state->numstates < state->numalloc);
	}

	state->trigstates[state->numstates].sct_tgoid = tgoid;
	state->trigstates[state->numstates].sct_tgisdeferred = tgisdeferred;
	state->numstates++;

	return state;
}