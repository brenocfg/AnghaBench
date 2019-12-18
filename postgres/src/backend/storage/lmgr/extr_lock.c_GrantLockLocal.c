#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int numLockOwners; int maxLockOwners; int /*<<< orphan*/  nLocks; TYPE_1__* lockOwners; } ;
struct TYPE_5__ {int nLocks; int /*<<< orphan*/ * owner; } ;
typedef  int /*<<< orphan*/ * ResourceOwner ;
typedef  TYPE_1__ LOCALLOCKOWNER ;
typedef  TYPE_2__ LOCALLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ResourceOwnerRememberLock (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void
GrantLockLocal(LOCALLOCK *locallock, ResourceOwner owner)
{
	LOCALLOCKOWNER *lockOwners = locallock->lockOwners;
	int			i;

	Assert(locallock->numLockOwners < locallock->maxLockOwners);
	/* Count the total */
	locallock->nLocks++;
	/* Count the per-owner lock */
	for (i = 0; i < locallock->numLockOwners; i++)
	{
		if (lockOwners[i].owner == owner)
		{
			lockOwners[i].nLocks++;
			return;
		}
	}
	lockOwners[i].owner = owner;
	lockOwners[i].nLocks = 1;
	locallock->numLockOwners++;
	if (owner != NULL)
		ResourceOwnerRememberLock(owner, locallock);
}