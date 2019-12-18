#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_9__ {scalar_t__ pid; } ;
struct TYPE_8__ {int /*<<< orphan*/  xid; } ;
struct TYPE_7__ {int numProcs; int* pgprocnos; } ;
typedef  TYPE_1__ ProcArrayStruct ;
typedef  TYPE_2__ PGXACT ;
typedef  TYPE_3__ PGPROC ;

/* Variables and functions */
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int /*<<< orphan*/  ProcArrayLock ; 
 int /*<<< orphan*/  RecentXmin ; 
 scalar_t__ TransactionIdEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT32_ACCESS_ONCE (int /*<<< orphan*/ ) ; 
 TYPE_2__* allPgXact ; 
 TYPE_3__* allProcs ; 
 TYPE_1__* procArray ; 

bool
TransactionIdIsActive(TransactionId xid)
{
	bool		result = false;
	ProcArrayStruct *arrayP = procArray;
	int			i;

	/*
	 * Don't bother checking a transaction older than RecentXmin; it could not
	 * possibly still be running.
	 */
	if (TransactionIdPrecedes(xid, RecentXmin))
		return false;

	LWLockAcquire(ProcArrayLock, LW_SHARED);

	for (i = 0; i < arrayP->numProcs; i++)
	{
		int			pgprocno = arrayP->pgprocnos[i];
		PGPROC	   *proc = &allProcs[pgprocno];
		PGXACT	   *pgxact = &allPgXact[pgprocno];
		TransactionId pxid;

		/* Fetch xid just once - see GetNewTransactionId */
		pxid = UINT32_ACCESS_ONCE(pgxact->xid);

		if (!TransactionIdIsValid(pxid))
			continue;

		if (proc->pid == 0)
			continue;			/* ignore prepared transactions */

		if (TransactionIdEquals(pxid, xid))
		{
			result = true;
			break;
		}
	}

	LWLockRelease(ProcArrayLock);

	return result;
}