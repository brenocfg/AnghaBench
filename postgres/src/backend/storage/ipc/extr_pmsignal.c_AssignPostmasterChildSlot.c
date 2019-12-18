#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int next_child_flag; int num_child_flags; scalar_t__* PMChildFlags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL ; 
 TYPE_1__* PMSignalState ; 
 scalar_t__ PM_CHILD_ASSIGNED ; 
 scalar_t__ PM_CHILD_UNUSED ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

int
AssignPostmasterChildSlot(void)
{
	int			slot = PMSignalState->next_child_flag;
	int			n;

	/*
	 * Scan for a free slot.  We track the last slot assigned so as not to
	 * waste time repeatedly rescanning low-numbered slots.
	 */
	for (n = PMSignalState->num_child_flags; n > 0; n--)
	{
		if (--slot < 0)
			slot = PMSignalState->num_child_flags - 1;
		if (PMSignalState->PMChildFlags[slot] == PM_CHILD_UNUSED)
		{
			PMSignalState->PMChildFlags[slot] = PM_CHILD_ASSIGNED;
			PMSignalState->next_child_flag = slot;
			return slot + 1;
		}
	}

	/* Out of slots ... should never happen, else postmaster.c messed up */
	elog(FATAL, "no free slots in PMChildFlags array");
	return 0;					/* keep compiler quiet */
}