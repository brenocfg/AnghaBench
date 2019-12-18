#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  lock; } ;
struct TYPE_8__ {int numLockOwners; int nLocks; TYPE_1__ tag; TYPE_2__* lockOwners; } ;
struct TYPE_7__ {int nLocks; int /*<<< orphan*/ * owner; } ;
typedef  int /*<<< orphan*/ * ResourceOwner ;
typedef  TYPE_2__ LOCALLOCKOWNER ;
typedef  TYPE_3__ LOCALLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * CurrentResourceOwner ; 
 int /*<<< orphan*/  LockRelease (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ResourceOwnerForgetLock (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ReleaseLockIfHeld(LOCALLOCK *locallock, bool sessionLock)
{
	ResourceOwner owner;
	LOCALLOCKOWNER *lockOwners;
	int			i;

	/* Identify owner for lock (must match LockRelease!) */
	if (sessionLock)
		owner = NULL;
	else
		owner = CurrentResourceOwner;

	/* Scan to see if there are any locks belonging to the target owner */
	lockOwners = locallock->lockOwners;
	for (i = locallock->numLockOwners - 1; i >= 0; i--)
	{
		if (lockOwners[i].owner == owner)
		{
			Assert(lockOwners[i].nLocks > 0);
			if (lockOwners[i].nLocks < locallock->nLocks)
			{
				/*
				 * We will still hold this lock after forgetting this
				 * ResourceOwner.
				 */
				locallock->nLocks -= lockOwners[i].nLocks;
				/* compact out unused slot */
				locallock->numLockOwners--;
				if (owner != NULL)
					ResourceOwnerForgetLock(owner, locallock);
				if (i < locallock->numLockOwners)
					lockOwners[i] = lockOwners[locallock->numLockOwners];
			}
			else
			{
				Assert(lockOwners[i].nLocks == locallock->nLocks);
				/* We want to call LockRelease just once */
				lockOwners[i].nLocks = 1;
				locallock->nLocks = 1;
				if (!LockRelease(&locallock->tag.lock,
								 locallock->tag.mode,
								 sessionLock))
					elog(WARNING, "ReleaseLockIfHeld: failed??");
			}
			break;
		}
	}
}