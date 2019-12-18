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
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * AuxProcessResourceOwner ; 
 int CHECKPOINT_IMMEDIATE ; 
 int CHECKPOINT_IS_SHUTDOWN ; 
 int /*<<< orphan*/  CreateCheckPoint (int) ; 
 int /*<<< orphan*/  CreateRestartPoint (int) ; 
 int /*<<< orphan*/ * CurrentResourceOwner ; 
 scalar_t__ IsPostmasterEnvironment ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  NOTICE ; 
 scalar_t__ RecoveryInProgress () ; 
 int /*<<< orphan*/  RequestXLogSwitch (int) ; 
 int /*<<< orphan*/  ShutdownCLOG () ; 
 int /*<<< orphan*/  ShutdownCommitTs () ; 
 int /*<<< orphan*/  ShutdownMultiXact () ; 
 int /*<<< orphan*/  ShutdownSUBTRANS () ; 
 int /*<<< orphan*/  WalSndInitStopping () ; 
 int /*<<< orphan*/  WalSndWaitStopping () ; 
 scalar_t__ XLogArchiveCommandSet () ; 
 scalar_t__ XLogArchivingActive () ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

void
ShutdownXLOG(int code, Datum arg)
{
	/*
	 * We should have an aux process resource owner to use, and we should not
	 * be in a transaction that's installed some other resowner.
	 */
	Assert(AuxProcessResourceOwner != NULL);
	Assert(CurrentResourceOwner == NULL ||
		   CurrentResourceOwner == AuxProcessResourceOwner);
	CurrentResourceOwner = AuxProcessResourceOwner;

	/* Don't be chatty in standalone mode */
	ereport(IsPostmasterEnvironment ? LOG : NOTICE,
			(errmsg("shutting down")));

	/*
	 * Signal walsenders to move to stopping state.
	 */
	WalSndInitStopping();

	/*
	 * Wait for WAL senders to be in stopping state.  This prevents commands
	 * from writing new WAL.
	 */
	WalSndWaitStopping();

	if (RecoveryInProgress())
		CreateRestartPoint(CHECKPOINT_IS_SHUTDOWN | CHECKPOINT_IMMEDIATE);
	else
	{
		/*
		 * If archiving is enabled, rotate the last XLOG file so that all the
		 * remaining records are archived (postmaster wakes up the archiver
		 * process one more time at the end of shutdown). The checkpoint
		 * record will go to the next XLOG file and won't be archived (yet).
		 */
		if (XLogArchivingActive() && XLogArchiveCommandSet())
			RequestXLogSwitch(false);

		CreateCheckPoint(CHECKPOINT_IS_SHUTDOWN | CHECKPOINT_IMMEDIATE);
	}
	ShutdownCLOG();
	ShutdownCommitTs();
	ShutdownSUBTRANS();
	ShutdownMultiXact();
}