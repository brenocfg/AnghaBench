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
struct TYPE_8__ {int /*<<< orphan*/  xmin; } ;
struct TYPE_7__ {size_t pgprocno; scalar_t__ databaseId; } ;
struct TYPE_6__ {int /*<<< orphan*/  xmin; } ;
typedef  TYPE_1__ PGXACT ;
typedef  TYPE_2__ PGPROC ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (scalar_t__) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 scalar_t__ MyDatabaseId ; 
 TYPE_5__* MyPgXact ; 
 int /*<<< orphan*/  ProcArrayLock ; 
 scalar_t__ TransactionIdIsNormal (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdPrecedesOrEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionXmin ; 
 int /*<<< orphan*/  UINT32_ACCESS_ONCE (int /*<<< orphan*/ ) ; 
 TYPE_1__* allPgXact ; 

bool
ProcArrayInstallRestoredXmin(TransactionId xmin, PGPROC *proc)
{
	bool		result = false;
	TransactionId xid;
	PGXACT	   *pgxact;

	Assert(TransactionIdIsNormal(xmin));
	Assert(proc != NULL);

	/* Get lock so source xact can't end while we're doing this */
	LWLockAcquire(ProcArrayLock, LW_SHARED);

	pgxact = &allPgXact[proc->pgprocno];

	/*
	 * Be certain that the referenced PGPROC has an advertised xmin which is
	 * no later than the one we're installing, so that the system-wide xmin
	 * can't go backwards.  Also, make sure it's running in the same database,
	 * so that the per-database xmin cannot go backwards.
	 */
	xid = UINT32_ACCESS_ONCE(pgxact->xmin);
	if (proc->databaseId == MyDatabaseId &&
		TransactionIdIsNormal(xid) &&
		TransactionIdPrecedesOrEquals(xid, xmin))
	{
		MyPgXact->xmin = TransactionXmin = xmin;
		result = true;
	}

	LWLockRelease(ProcArrayLock);

	return result;
}