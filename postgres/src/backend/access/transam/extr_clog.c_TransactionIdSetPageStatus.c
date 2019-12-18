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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XidStatus ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  scalar_t__ TransactionId ;
struct TYPE_6__ {scalar_t__ xid; int nxids; } ;
struct TYPE_4__ {int /*<<< orphan*/  xids; } ;
struct TYPE_5__ {TYPE_1__ subxids; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CLogControlLock ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LWLockConditionalAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 TYPE_3__* MyPgXact ; 
 TYPE_2__* MyProc ; 
 int PGPROC_MAX_CACHED_SUBXIDS ; 
 int /*<<< orphan*/  StaticAssertStmt (int,char*) ; 
 int THRESHOLD_SUBTRANS_CLOG_OPT ; 
 scalar_t__ TransactionGroupUpdateXidStatus (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TransactionIdSetPageStatusInternal (scalar_t__,int,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ memcmp (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
TransactionIdSetPageStatus(TransactionId xid, int nsubxids,
						   TransactionId *subxids, XidStatus status,
						   XLogRecPtr lsn, int pageno,
						   bool all_xact_same_page)
{
	/* Can't use group update when PGPROC overflows. */
	StaticAssertStmt(THRESHOLD_SUBTRANS_CLOG_OPT <= PGPROC_MAX_CACHED_SUBXIDS,
					 "group clog threshold less than PGPROC cached subxids");

	/*
	 * When there is contention on CLogControlLock, we try to group multiple
	 * updates; a single leader process will perform transaction status
	 * updates for multiple backends so that the number of times
	 * CLogControlLock needs to be acquired is reduced.
	 *
	 * For this optimization to be safe, the XID in MyPgXact and the subxids
	 * in MyProc must be the same as the ones for which we're setting the
	 * status.  Check that this is the case.
	 *
	 * For this optimization to be efficient, we shouldn't have too many
	 * sub-XIDs and all of the XIDs for which we're adjusting clog should be
	 * on the same page.  Check those conditions, too.
	 */
	if (all_xact_same_page && xid == MyPgXact->xid &&
		nsubxids <= THRESHOLD_SUBTRANS_CLOG_OPT &&
		nsubxids == MyPgXact->nxids &&
		memcmp(subxids, MyProc->subxids.xids,
			   nsubxids * sizeof(TransactionId)) == 0)
	{
		/*
		 * We don't try to do group update optimization if a process has
		 * overflowed the subxids array in its PGPROC, since in that case we
		 * don't have a complete list of XIDs for it.
		 */
		Assert(THRESHOLD_SUBTRANS_CLOG_OPT <= PGPROC_MAX_CACHED_SUBXIDS);

		/*
		 * If we can immediately acquire CLogControlLock, we update the status
		 * of our own XID and release the lock.  If not, try use group XID
		 * update.  If that doesn't work out, fall back to waiting for the
		 * lock to perform an update for this transaction only.
		 */
		if (LWLockConditionalAcquire(CLogControlLock, LW_EXCLUSIVE))
		{
			/* Got the lock without waiting!  Do the update. */
			TransactionIdSetPageStatusInternal(xid, nsubxids, subxids, status,
											   lsn, pageno);
			LWLockRelease(CLogControlLock);
			return;
		}
		else if (TransactionGroupUpdateXidStatus(xid, status, lsn, pageno))
		{
			/* Group update mechanism has done the work. */
			return;
		}

		/* Fall through only if update isn't done yet. */
	}

	/* Group update not applicable, or couldn't accept this page number. */
	LWLockAcquire(CLogControlLock, LW_EXCLUSIVE);
	TransactionIdSetPageStatusInternal(xid, nsubxids, subxids, status,
									   lsn, pageno);
	LWLockRelease(CLogControlLock);
}