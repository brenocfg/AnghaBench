#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ backendId; scalar_t__ localTransactionId; } ;
typedef  TYPE_1__ VirtualTransactionId ;
struct TYPE_6__ {scalar_t__ backendId; scalar_t__ fpLocalTransactionId; int fpVXIDLock; int /*<<< orphan*/  backendLock; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ InvalidLocalTransactionId ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 TYPE_4__* MyProc ; 
 int VirtualTransactionIdIsValid (TYPE_1__) ; 

void
VirtualXactLockTableInsert(VirtualTransactionId vxid)
{
	Assert(VirtualTransactionIdIsValid(vxid));

	LWLockAcquire(&MyProc->backendLock, LW_EXCLUSIVE);

	Assert(MyProc->backendId == vxid.backendId);
	Assert(MyProc->fpLocalTransactionId == InvalidLocalTransactionId);
	Assert(MyProc->fpVXIDLock == false);

	MyProc->fpVXIDLock = true;
	MyProc->fpLocalTransactionId = vxid.localTransactionId;

	LWLockRelease(&MyProc->backendLock);
}