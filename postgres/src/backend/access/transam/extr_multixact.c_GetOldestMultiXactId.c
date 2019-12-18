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
struct TYPE_2__ {scalar_t__ nextMXact; } ;
typedef  scalar_t__ MultiXactId ;

/* Variables and functions */
 scalar_t__ FirstMultiXactId ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int MaxOldestSlot ; 
 int /*<<< orphan*/  MultiXactGenLock ; 
 scalar_t__ MultiXactIdIsValid (scalar_t__) ; 
 scalar_t__ MultiXactIdPrecedes (scalar_t__,scalar_t__) ; 
 TYPE_1__* MultiXactState ; 
 scalar_t__* OldestMemberMXactId ; 
 scalar_t__* OldestVisibleMXactId ; 

MultiXactId
GetOldestMultiXactId(void)
{
	MultiXactId oldestMXact;
	MultiXactId nextMXact;
	int			i;

	/*
	 * This is the oldest valid value among all the OldestMemberMXactId[] and
	 * OldestVisibleMXactId[] entries, or nextMXact if none are valid.
	 */
	LWLockAcquire(MultiXactGenLock, LW_SHARED);

	/*
	 * We have to beware of the possibility that nextMXact is in the
	 * wrapped-around state.  We don't fix the counter itself here, but we
	 * must be sure to use a valid value in our calculation.
	 */
	nextMXact = MultiXactState->nextMXact;
	if (nextMXact < FirstMultiXactId)
		nextMXact = FirstMultiXactId;

	oldestMXact = nextMXact;
	for (i = 1; i <= MaxOldestSlot; i++)
	{
		MultiXactId thisoldest;

		thisoldest = OldestMemberMXactId[i];
		if (MultiXactIdIsValid(thisoldest) &&
			MultiXactIdPrecedes(thisoldest, oldestMXact))
			oldestMXact = thisoldest;
		thisoldest = OldestVisibleMXactId[i];
		if (MultiXactIdIsValid(thisoldest) &&
			MultiXactIdPrecedes(thisoldest, oldestMXact))
			oldestMXact = thisoldest;
	}

	LWLockRelease(MultiXactGenLock);

	return oldestMXact;
}