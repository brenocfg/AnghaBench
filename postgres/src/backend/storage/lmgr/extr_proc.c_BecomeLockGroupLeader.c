#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lockGroupLink; int /*<<< orphan*/  lockGroupMembers; struct TYPE_3__* lockGroupLeader; } ;
typedef  int /*<<< orphan*/  LWLock ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/ * LockHashPartitionLockByProc (TYPE_1__*) ; 
 TYPE_1__* MyProc ; 
 int /*<<< orphan*/  dlist_push_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
BecomeLockGroupLeader(void)
{
	LWLock	   *leader_lwlock;

	/* If we already did it, we don't need to do it again. */
	if (MyProc->lockGroupLeader == MyProc)
		return;

	/* We had better not be a follower. */
	Assert(MyProc->lockGroupLeader == NULL);

	/* Create single-member group, containing only ourselves. */
	leader_lwlock = LockHashPartitionLockByProc(MyProc);
	LWLockAcquire(leader_lwlock, LW_EXCLUSIVE);
	MyProc->lockGroupLeader = MyProc;
	dlist_push_head(&MyProc->lockGroupMembers, &MyProc->lockGroupLink);
	LWLockRelease(leader_lwlock);
}