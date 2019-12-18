#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  xl_standby_lock ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  RunningTransactions ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetRunningTransactionData () ; 
 int /*<<< orphan*/ * GetRunningTransactionLocks (int*) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LogAccessExclusiveLocks (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LogCurrentRunningXacts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcArrayLock ; 
 scalar_t__ WAL_LEVEL_LOGICAL ; 
 int /*<<< orphan*/  XLogStandbyInfoActive () ; 
 int /*<<< orphan*/  XidGenLock ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 scalar_t__ wal_level ; 

XLogRecPtr
LogStandbySnapshot(void)
{
	XLogRecPtr	recptr;
	RunningTransactions running;
	xl_standby_lock *locks;
	int			nlocks;

	Assert(XLogStandbyInfoActive());

	/*
	 * Get details of any AccessExclusiveLocks being held at the moment.
	 */
	locks = GetRunningTransactionLocks(&nlocks);
	if (nlocks > 0)
		LogAccessExclusiveLocks(nlocks, locks);
	pfree(locks);

	/*
	 * Log details of all in-progress transactions. This should be the last
	 * record we write, because standby will open up when it sees this.
	 */
	running = GetRunningTransactionData();

	/*
	 * GetRunningTransactionData() acquired ProcArrayLock, we must release it.
	 * For Hot Standby this can be done before inserting the WAL record
	 * because ProcArrayApplyRecoveryInfo() rechecks the commit status using
	 * the clog. For logical decoding, though, the lock can't be released
	 * early because the clog might be "in the future" from the POV of the
	 * historic snapshot. This would allow for situations where we're waiting
	 * for the end of a transaction listed in the xl_running_xacts record
	 * which, according to the WAL, has committed before the xl_running_xacts
	 * record. Fortunately this routine isn't executed frequently, and it's
	 * only a shared lock.
	 */
	if (wal_level < WAL_LEVEL_LOGICAL)
		LWLockRelease(ProcArrayLock);

	recptr = LogCurrentRunningXacts(running);

	/* Release lock if we kept it longer ... */
	if (wal_level >= WAL_LEVEL_LOGICAL)
		LWLockRelease(ProcArrayLock);

	/* GetRunningTransactionData() acquired XidGenLock, we must release it */
	LWLockRelease(XidGenLock);

	return recptr;
}