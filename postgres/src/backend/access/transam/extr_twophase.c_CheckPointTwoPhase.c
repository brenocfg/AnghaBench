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
typedef  scalar_t__ XLogRecPtr ;
struct TYPE_4__ {int numPrepXacts; TYPE_1__** prepXacts; } ;
struct TYPE_3__ {int ondisk; scalar_t__ prepare_end_lsn; void* prepare_start_lsn; int /*<<< orphan*/  xid; scalar_t__ inredo; scalar_t__ valid; } ;
typedef  TYPE_1__* GlobalTransaction ;

/* Variables and functions */
 void* InvalidXLogRecPtr ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int /*<<< orphan*/  RecreateTwoPhaseFile (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  TRACE_POSTGRESQL_TWOPHASE_CHECKPOINT_DONE () ; 
 int /*<<< orphan*/  TRACE_POSTGRESQL_TWOPHASE_CHECKPOINT_START () ; 
 int /*<<< orphan*/  TWOPHASE_DIR ; 
 TYPE_2__* TwoPhaseState ; 
 int /*<<< orphan*/  TwoPhaseStateLock ; 
 int /*<<< orphan*/  XlogReadTwoPhaseData (void*,char**,int*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg_plural (char*,char*,int,int) ; 
 int /*<<< orphan*/  fsync_fname (int /*<<< orphan*/ ,int) ; 
 scalar_t__ log_checkpoints ; 
 scalar_t__ max_prepared_xacts ; 
 int /*<<< orphan*/  pfree (char*) ; 

void
CheckPointTwoPhase(XLogRecPtr redo_horizon)
{
	int			i;
	int			serialized_xacts = 0;

	if (max_prepared_xacts <= 0)
		return;					/* nothing to do */

	TRACE_POSTGRESQL_TWOPHASE_CHECKPOINT_START();

	/*
	 * We are expecting there to be zero GXACTs that need to be copied to
	 * disk, so we perform all I/O while holding TwoPhaseStateLock for
	 * simplicity. This prevents any new xacts from preparing while this
	 * occurs, which shouldn't be a problem since the presence of long-lived
	 * prepared xacts indicates the transaction manager isn't active.
	 *
	 * It's also possible to move I/O out of the lock, but on every error we
	 * should check whether somebody committed our transaction in different
	 * backend. Let's leave this optimization for future, if somebody will
	 * spot that this place cause bottleneck.
	 *
	 * Note that it isn't possible for there to be a GXACT with a
	 * prepare_end_lsn set prior to the last checkpoint yet is marked invalid,
	 * because of the efforts with delayChkpt.
	 */
	LWLockAcquire(TwoPhaseStateLock, LW_SHARED);
	for (i = 0; i < TwoPhaseState->numPrepXacts; i++)
	{
		/*
		 * Note that we are using gxact not pgxact so this works in recovery
		 * also
		 */
		GlobalTransaction gxact = TwoPhaseState->prepXacts[i];

		if ((gxact->valid || gxact->inredo) &&
			!gxact->ondisk &&
			gxact->prepare_end_lsn <= redo_horizon)
		{
			char	   *buf;
			int			len;

			XlogReadTwoPhaseData(gxact->prepare_start_lsn, &buf, &len);
			RecreateTwoPhaseFile(gxact->xid, buf, len);
			gxact->ondisk = true;
			gxact->prepare_start_lsn = InvalidXLogRecPtr;
			gxact->prepare_end_lsn = InvalidXLogRecPtr;
			pfree(buf);
			serialized_xacts++;
		}
	}
	LWLockRelease(TwoPhaseStateLock);

	/*
	 * Flush unconditionally the parent directory to make any information
	 * durable on disk.  Two-phase files could have been removed and those
	 * removals need to be made persistent as well as any files newly created
	 * previously since the last checkpoint.
	 */
	fsync_fname(TWOPHASE_DIR, true);

	TRACE_POSTGRESQL_TWOPHASE_CHECKPOINT_DONE();

	if (log_checkpoints && serialized_xacts > 0)
		ereport(LOG,
				(errmsg_plural("%u two-phase state file was written "
							   "for a long-running prepared transaction",
							   "%u two-phase state files were written "
							   "for long-running prepared transactions",
							   serialized_xacts,
							   serialized_xacts)));
}