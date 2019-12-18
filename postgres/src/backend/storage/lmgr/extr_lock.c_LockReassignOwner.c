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
struct TYPE_7__ {int numLockOwners; TYPE_1__* lockOwners; } ;
struct TYPE_6__ {scalar_t__ owner; scalar_t__ nLocks; } ;
typedef  scalar_t__ ResourceOwner ;
typedef  TYPE_1__ LOCALLOCKOWNER ;
typedef  TYPE_2__ LOCALLOCK ;

/* Variables and functions */
 scalar_t__ CurrentResourceOwner ; 
 int /*<<< orphan*/  ResourceOwnerForgetLock (scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  ResourceOwnerRememberLock (scalar_t__,TYPE_2__*) ; 

__attribute__((used)) static void
LockReassignOwner(LOCALLOCK *locallock, ResourceOwner parent)
{
	LOCALLOCKOWNER *lockOwners;
	int			i;
	int			ic = -1;
	int			ip = -1;

	/*
	 * Scan to see if there are any locks belonging to current owner or its
	 * parent
	 */
	lockOwners = locallock->lockOwners;
	for (i = locallock->numLockOwners - 1; i >= 0; i--)
	{
		if (lockOwners[i].owner == CurrentResourceOwner)
			ic = i;
		else if (lockOwners[i].owner == parent)
			ip = i;
	}

	if (ic < 0)
		return;					/* no current locks */

	if (ip < 0)
	{
		/* Parent has no slot, so just give it the child's slot */
		lockOwners[ic].owner = parent;
		ResourceOwnerRememberLock(parent, locallock);
	}
	else
	{
		/* Merge child's count with parent's */
		lockOwners[ip].nLocks += lockOwners[ic].nLocks;
		/* compact out unused slot */
		locallock->numLockOwners--;
		if (ic < locallock->numLockOwners)
			lockOwners[ic] = lockOwners[locallock->numLockOwners];
	}
	ResourceOwnerForgetLock(CurrentResourceOwner, locallock);
}