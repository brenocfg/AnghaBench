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
struct TYPE_2__ {int num_child_flags; scalar_t__* PMChildFlags; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_1__* PMSignalState ; 
 scalar_t__ PM_CHILD_ASSIGNED ; 
 scalar_t__ PM_CHILD_UNUSED ; 

bool
ReleasePostmasterChildSlot(int slot)
{
	bool		result;

	Assert(slot > 0 && slot <= PMSignalState->num_child_flags);
	slot--;

	/*
	 * Note: the slot state might already be unused, because the logic in
	 * postmaster.c is such that this might get called twice when a child
	 * crashes.  So we don't try to Assert anything about the state.
	 */
	result = (PMSignalState->PMChildFlags[slot] == PM_CHILD_ASSIGNED);
	PMSignalState->PMChildFlags[slot] = PM_CHILD_UNUSED;
	return result;
}