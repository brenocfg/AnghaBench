#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  localTransactionId; int /*<<< orphan*/  backendId; } ;
typedef  TYPE_1__ VirtualTransactionId ;
struct TYPE_6__ {scalar_t__ backendId; int fpVXIDLock; int /*<<< orphan*/  backendLock; int /*<<< orphan*/  fpLocalTransactionId; } ;
typedef  int /*<<< orphan*/  LocalTransactionId ;
typedef  int /*<<< orphan*/  LOCKTAG ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 size_t DEFAULT_LOCKMETHOD ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 scalar_t__ InvalidBackendId ; 
 int /*<<< orphan*/  InvalidLocalTransactionId ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 scalar_t__ LocalTransactionIdIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * LockMethods ; 
 int /*<<< orphan*/  LockRefindAndRelease (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MyBackendId ; 
 TYPE_3__* MyProc ; 
 int /*<<< orphan*/  SET_LOCKTAG_VIRTUALTRANSACTION (int /*<<< orphan*/ ,TYPE_1__) ; 

void
VirtualXactLockTableCleanup(void)
{
	bool		fastpath;
	LocalTransactionId lxid;

	Assert(MyProc->backendId != InvalidBackendId);

	/*
	 * Clean up shared memory state.
	 */
	LWLockAcquire(&MyProc->backendLock, LW_EXCLUSIVE);

	fastpath = MyProc->fpVXIDLock;
	lxid = MyProc->fpLocalTransactionId;
	MyProc->fpVXIDLock = false;
	MyProc->fpLocalTransactionId = InvalidLocalTransactionId;

	LWLockRelease(&MyProc->backendLock);

	/*
	 * If fpVXIDLock has been cleared without touching fpLocalTransactionId,
	 * that means someone transferred the lock to the main lock table.
	 */
	if (!fastpath && LocalTransactionIdIsValid(lxid))
	{
		VirtualTransactionId vxid;
		LOCKTAG		locktag;

		vxid.backendId = MyBackendId;
		vxid.localTransactionId = lxid;
		SET_LOCKTAG_VIRTUALTRANSACTION(locktag, vxid);

		LockRefindAndRelease(LockMethods[DEFAULT_LOCKMETHOD], MyProc,
							 &locktag, ExclusiveLock, false);
	}
}