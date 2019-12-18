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
struct TYPE_6__ {int numProcs; int* pgprocnos; int /*<<< orphan*/  replication_slot_catalog_xmin; int /*<<< orphan*/  replication_slot_xmin; } ;
typedef  TYPE_1__ ProcArrayStruct ;
typedef  TYPE_2__ PGXACT ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockHeldByMe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int /*<<< orphan*/  ProcArrayLock ; 
 int RecoveryInProgress () ; 
 TYPE_5__* ShmemVariableCache ; 
 int /*<<< orphan*/  TransactionIdIsNormal (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT32_ACCESS_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XidFromFullTransactionId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XidGenLock ; 
 TYPE_2__* allPgXact ; 
 TYPE_1__* procArray ; 

TransactionId
GetOldestSafeDecodingTransactionId(bool catalogOnly)
{
	ProcArrayStruct *arrayP = procArray;
	TransactionId oldestSafeXid;
	int			index;
	bool		recovery_in_progress = RecoveryInProgress();

	Assert(LWLockHeldByMe(ProcArrayLock));

	/*
	 * Acquire XidGenLock, so no transactions can acquire an xid while we're
	 * running. If no transaction with xid were running concurrently a new xid
	 * could influence the RecentXmin et al.
	 *
	 * We initialize the computation to nextXid since that's guaranteed to be
	 * a safe, albeit pessimal, value.
	 */
	LWLockAcquire(XidGenLock, LW_SHARED);
	oldestSafeXid = XidFromFullTransactionId(ShmemVariableCache->nextFullXid);

	/*
	 * If there's already a slot pegging the xmin horizon, we can start with
	 * that value, it's guaranteed to be safe since it's computed by this
	 * routine initially and has been enforced since.  We can always use the
	 * slot's general xmin horizon, but the catalog horizon is only usable
	 * when only catalog data is going to be looked at.
	 */
	if (TransactionIdIsValid(procArray->replication_slot_xmin) &&
		TransactionIdPrecedes(procArray->replication_slot_xmin,
							  oldestSafeXid))
		oldestSafeXid = procArray->replication_slot_xmin;

	if (catalogOnly &&
		TransactionIdIsValid(procArray->replication_slot_catalog_xmin) &&
		TransactionIdPrecedes(procArray->replication_slot_catalog_xmin,
							  oldestSafeXid))
		oldestSafeXid = procArray->replication_slot_catalog_xmin;

	/*
	 * If we're not in recovery, we walk over the procarray and collect the
	 * lowest xid. Since we're called with ProcArrayLock held and have
	 * acquired XidGenLock, no entries can vanish concurrently, since
	 * PGXACT->xid is only set with XidGenLock held and only cleared with
	 * ProcArrayLock held.
	 *
	 * In recovery we can't lower the safe value besides what we've computed
	 * above, so we'll have to wait a bit longer there. We unfortunately can
	 * *not* use KnownAssignedXidsGetOldestXmin() since the KnownAssignedXids
	 * machinery can miss values and return an older value than is safe.
	 */
	if (!recovery_in_progress)
	{
		/*
		 * Spin over procArray collecting all min(PGXACT->xid)
		 */
		for (index = 0; index < arrayP->numProcs; index++)
		{
			int			pgprocno = arrayP->pgprocnos[index];
			PGXACT	   *pgxact = &allPgXact[pgprocno];
			TransactionId xid;

			/* Fetch xid just once - see GetNewTransactionId */
			xid = UINT32_ACCESS_ONCE(pgxact->xid);

			if (!TransactionIdIsNormal(xid))
				continue;

			if (TransactionIdPrecedes(xid, oldestSafeXid))
				oldestSafeXid = xid;
		}
	}

	LWLockRelease(XidGenLock);

	return oldestSafeXid;
}