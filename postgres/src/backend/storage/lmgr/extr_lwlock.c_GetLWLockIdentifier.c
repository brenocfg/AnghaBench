#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint32 ;
typedef  size_t uint16 ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 char const** LWLockTrancheArray ; 
 size_t LWLockTranchesAllocated ; 
 scalar_t__ PG_WAIT_LWLOCK ; 

const char *
GetLWLockIdentifier(uint32 classId, uint16 eventId)
{
	Assert(classId == PG_WAIT_LWLOCK);

	/*
	 * It is quite possible that user has registered tranche in one of the
	 * backends (e.g. by allocating lwlocks in dynamic shared memory) but not
	 * all of them, so we can't assume the tranche is registered here.
	 */
	if (eventId >= LWLockTranchesAllocated ||
		LWLockTrancheArray[eventId] == NULL)
		return "extension";

	return LWLockTrancheArray[eventId];
}