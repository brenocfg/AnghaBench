#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  int XLogRecPtr ;
struct TYPE_4__ {int backupEndPoint; int minRecoveryPoint; int backupStartPoint; int backupEndRequired; } ;
struct TYPE_3__ {int lastReplayedEndRecPtr; int SharedHotStandbyActive; int /*<<< orphan*/  info_lck; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 TYPE_2__* ControlFile ; 
 int /*<<< orphan*/  ControlFileLock ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  InArchiveRecovery ; 
 void* InvalidXLogRecPtr ; 
 scalar_t__ IsUnderPostmaster ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int LocalHotStandbyActive ; 
 int /*<<< orphan*/  PMSIGNAL_BEGIN_HOT_STANDBY ; 
 scalar_t__ STANDBY_SNAPSHOT_READY ; 
 int /*<<< orphan*/  SendPostmasterSignal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UpdateControlFile () ; 
 int /*<<< orphan*/  XLogCheckInvalidPages () ; 
 TYPE_1__* XLogCtl ; 
 scalar_t__ XLogRecPtrIsInvalid (int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int minRecoveryPoint ; 
 int reachedConsistency ; 
 scalar_t__ standbyState ; 

__attribute__((used)) static void
CheckRecoveryConsistency(void)
{
	XLogRecPtr	lastReplayedEndRecPtr;

	/*
	 * During crash recovery, we don't reach a consistent state until we've
	 * replayed all the WAL.
	 */
	if (XLogRecPtrIsInvalid(minRecoveryPoint))
		return;

	Assert(InArchiveRecovery);

	/*
	 * assume that we are called in the startup process, and hence don't need
	 * a lock to read lastReplayedEndRecPtr
	 */
	lastReplayedEndRecPtr = XLogCtl->lastReplayedEndRecPtr;

	/*
	 * Have we reached the point where our base backup was completed?
	 */
	if (!XLogRecPtrIsInvalid(ControlFile->backupEndPoint) &&
		ControlFile->backupEndPoint <= lastReplayedEndRecPtr)
	{
		/*
		 * We have reached the end of base backup, as indicated by pg_control.
		 * The data on disk is now consistent. Reset backupStartPoint and
		 * backupEndPoint, and update minRecoveryPoint to make sure we don't
		 * allow starting up at an earlier point even if recovery is stopped
		 * and restarted soon after this.
		 */
		elog(DEBUG1, "end of backup reached");

		LWLockAcquire(ControlFileLock, LW_EXCLUSIVE);

		if (ControlFile->minRecoveryPoint < lastReplayedEndRecPtr)
			ControlFile->minRecoveryPoint = lastReplayedEndRecPtr;

		ControlFile->backupStartPoint = InvalidXLogRecPtr;
		ControlFile->backupEndPoint = InvalidXLogRecPtr;
		ControlFile->backupEndRequired = false;
		UpdateControlFile();

		LWLockRelease(ControlFileLock);
	}

	/*
	 * Have we passed our safe starting point? Note that minRecoveryPoint is
	 * known to be incorrectly set if ControlFile->backupEndRequired, until
	 * the XLOG_BACKUP_END arrives to advise us of the correct
	 * minRecoveryPoint. All we know prior to that is that we're not
	 * consistent yet.
	 */
	if (!reachedConsistency && !ControlFile->backupEndRequired &&
		minRecoveryPoint <= lastReplayedEndRecPtr &&
		XLogRecPtrIsInvalid(ControlFile->backupStartPoint))
	{
		/*
		 * Check to see if the XLOG sequence contained any unresolved
		 * references to uninitialized pages.
		 */
		XLogCheckInvalidPages();

		reachedConsistency = true;
		ereport(LOG,
				(errmsg("consistent recovery state reached at %X/%X",
						(uint32) (lastReplayedEndRecPtr >> 32),
						(uint32) lastReplayedEndRecPtr)));
	}

	/*
	 * Have we got a valid starting snapshot that will allow queries to be
	 * run? If so, we can tell postmaster that the database is consistent now,
	 * enabling connections.
	 */
	if (standbyState == STANDBY_SNAPSHOT_READY &&
		!LocalHotStandbyActive &&
		reachedConsistency &&
		IsUnderPostmaster)
	{
		SpinLockAcquire(&XLogCtl->info_lck);
		XLogCtl->SharedHotStandbyActive = true;
		SpinLockRelease(&XLogCtl->info_lck);

		LocalHotStandbyActive = true;

		SendPostmasterSignal(PMSIGNAL_BEGIN_HOT_STANDBY);
	}
}