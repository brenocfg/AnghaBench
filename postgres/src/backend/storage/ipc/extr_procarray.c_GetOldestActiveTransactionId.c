#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_8__ {int /*<<< orphan*/  nextFullXid; } ;
struct TYPE_7__ {int /*<<< orphan*/  xid; } ;
struct TYPE_6__ {int numProcs; int* pgprocnos; } ;
typedef  TYPE_1__ ProcArrayStruct ;
typedef  TYPE_2__ PGXACT ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int /*<<< orphan*/  ProcArrayLock ; 
 int /*<<< orphan*/  RecoveryInProgress () ; 
 TYPE_5__* ShmemVariableCache ; 
 int /*<<< orphan*/  TransactionIdIsNormal (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT32_ACCESS_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XidFromFullTransactionId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XidGenLock ; 
 TYPE_2__* allPgXact ; 
 TYPE_1__* procArray ; 

TransactionId
GetOldestActiveTransactionId(void)
{
	ProcArrayStruct *arrayP = procArray;
	TransactionId oldestRunningXid;
	int			index;

	Assert(!RecoveryInProgress());

	/*
	 * Read nextXid, as the upper bound of what's still active.
	 *
	 * Reading a TransactionId is atomic, but we must grab the lock to make
	 * sure that all XIDs < nextXid are already present in the proc array (or
	 * have already completed), when we spin over it.
	 */
	LWLockAcquire(XidGenLock, LW_SHARED);
	oldestRunningXid = XidFromFullTransactionId(ShmemVariableCache->nextFullXid);
	LWLockRelease(XidGenLock);

	/*
	 * Spin over procArray collecting all xids and subxids.
	 */
	LWLockAcquire(ProcArrayLock, LW_SHARED);
	for (index = 0; index < arrayP->numProcs; index++)
	{
		int			pgprocno = arrayP->pgprocnos[index];
		PGXACT	   *pgxact = &allPgXact[pgprocno];
		TransactionId xid;

		/* Fetch xid just once - see GetNewTransactionId */
		xid = UINT32_ACCESS_ONCE(pgxact->xid);

		if (!TransactionIdIsNormal(xid))
			continue;

		if (TransactionIdPrecedes(xid, oldestRunningXid))
			oldestRunningXid = xid;

		/*
		 * Top-level XID of a transaction is always less than any of its
		 * subxids, so we don't need to check if any of the subxids are
		 * smaller than oldestRunningXid
		 */
	}
	LWLockRelease(ProcArrayLock);

	return oldestRunningXid;
}