#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ backendId; scalar_t__ localTransactionId; } ;
typedef  TYPE_1__ VirtualTransactionId ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_14__ {int /*<<< orphan*/  xmin; } ;
struct TYPE_13__ {scalar_t__ backendId; scalar_t__ lxid; scalar_t__ databaseId; } ;
struct TYPE_12__ {int vacuumFlags; int /*<<< orphan*/  xmin; } ;
struct TYPE_11__ {int numProcs; int* pgprocnos; } ;
typedef  TYPE_2__ ProcArrayStruct ;
typedef  TYPE_3__ PGXACT ;
typedef  TYPE_4__ PGPROC ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 scalar_t__ MyDatabaseId ; 
 TYPE_9__* MyPgXact ; 
 int PROC_IN_VACUUM ; 
 int /*<<< orphan*/  ProcArrayLock ; 
 int /*<<< orphan*/  TransactionIdIsNormal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdPrecedesOrEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionXmin ; 
 int /*<<< orphan*/  UINT32_ACCESS_ONCE (int /*<<< orphan*/ ) ; 
 TYPE_3__* allPgXact ; 
 TYPE_4__* allProcs ; 
 TYPE_2__* procArray ; 

bool
ProcArrayInstallImportedXmin(TransactionId xmin,
							 VirtualTransactionId *sourcevxid)
{
	bool		result = false;
	ProcArrayStruct *arrayP = procArray;
	int			index;

	Assert(TransactionIdIsNormal(xmin));
	if (!sourcevxid)
		return false;

	/* Get lock so source xact can't end while we're doing this */
	LWLockAcquire(ProcArrayLock, LW_SHARED);

	for (index = 0; index < arrayP->numProcs; index++)
	{
		int			pgprocno = arrayP->pgprocnos[index];
		PGPROC	   *proc = &allProcs[pgprocno];
		PGXACT	   *pgxact = &allPgXact[pgprocno];
		TransactionId xid;

		/* Ignore procs running LAZY VACUUM */
		if (pgxact->vacuumFlags & PROC_IN_VACUUM)
			continue;

		/* We are only interested in the specific virtual transaction. */
		if (proc->backendId != sourcevxid->backendId)
			continue;
		if (proc->lxid != sourcevxid->localTransactionId)
			continue;

		/*
		 * We check the transaction's database ID for paranoia's sake: if it's
		 * in another DB then its xmin does not cover us.  Caller should have
		 * detected this already, so we just treat any funny cases as
		 * "transaction not found".
		 */
		if (proc->databaseId != MyDatabaseId)
			continue;

		/*
		 * Likewise, let's just make real sure its xmin does cover us.
		 */
		xid = UINT32_ACCESS_ONCE(pgxact->xmin);
		if (!TransactionIdIsNormal(xid) ||
			!TransactionIdPrecedesOrEquals(xid, xmin))
			continue;

		/*
		 * We're good.  Install the new xmin.  As in GetSnapshotData, set
		 * TransactionXmin too.  (Note that because snapmgr.c called
		 * GetSnapshotData first, we'll be overwriting a valid xmin here, so
		 * we don't check that.)
		 */
		MyPgXact->xmin = TransactionXmin = xmin;

		result = true;
		break;
	}

	LWLockRelease(ProcArrayLock);

	return result;
}