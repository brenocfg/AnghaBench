#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ oldestRunningXid; scalar_t__ nextXid; int /*<<< orphan*/  xcnt; } ;
typedef  TYPE_1__ xl_running_xacts ;
typedef  int /*<<< orphan*/  uint32 ;
typedef  int XLogRecPtr ;
struct TYPE_10__ {scalar_t__ initial_xmin_horizon; int start_decoding_at; scalar_t__ xmin; scalar_t__ xmax; scalar_t__ state; int /*<<< orphan*/  building_full_snapshot; } ;
typedef  TYPE_2__ SnapBuild ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (scalar_t__) ; 
 int /*<<< orphan*/  DEBUG1 ; 
 scalar_t__ InvalidTransactionId ; 
 int InvalidXLogRecPtr ; 
 int /*<<< orphan*/  LOG ; 
 scalar_t__ NormalTransactionIdPrecedes (scalar_t__,scalar_t__) ; 
 scalar_t__ SNAPBUILD_BUILDING_SNAPSHOT ; 
 void* SNAPBUILD_CONSISTENT ; 
 scalar_t__ SNAPBUILD_FULL_SNAPSHOT ; 
 scalar_t__ SNAPBUILD_START ; 
 int /*<<< orphan*/  SnapBuildNextPhaseAt (TYPE_2__*) ; 
 scalar_t__ SnapBuildRestore (TYPE_2__*,int) ; 
 int /*<<< orphan*/  SnapBuildStartNextPhaseAt (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  SnapBuildWaitSnapshot (TYPE_1__*,scalar_t__) ; 
 scalar_t__ TransactionIdIsNormal (scalar_t__) ; 
 scalar_t__ TransactionIdPrecedesOrEquals (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,...) ; 
 int /*<<< orphan*/  errdetail_internal (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg_internal (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
SnapBuildFindSnapshot(SnapBuild *builder, XLogRecPtr lsn, xl_running_xacts *running)
{
	/* ---
	 * Build catalog decoding snapshot incrementally using information about
	 * the currently running transactions. There are several ways to do that:
	 *
	 * a) There were no running transactions when the xl_running_xacts record
	 *	  was inserted, jump to CONSISTENT immediately. We might find such a
	 *	  state while waiting on c)'s sub-states.
	 *
	 * b) This (in a previous run) or another decoding slot serialized a
	 *	  snapshot to disk that we can use.  Can't use this method for the
	 *	  initial snapshot when slot is being created and needs full snapshot
	 *	  for export or direct use, as that snapshot will only contain catalog
	 *	  modifying transactions.
	 *
	 * c) First incrementally build a snapshot for catalog tuples
	 *	  (BUILDING_SNAPSHOT), that requires all, already in-progress,
	 *	  transactions to finish.  Every transaction starting after that
	 *	  (FULL_SNAPSHOT state), has enough information to be decoded.  But
	 *	  for older running transactions no viable snapshot exists yet, so
	 *	  CONSISTENT will only be reached once all of those have finished.
	 * ---
	 */

	/*
	 * xl_running_xact record is older than what we can use, we might not have
	 * all necessary catalog rows anymore.
	 */
	if (TransactionIdIsNormal(builder->initial_xmin_horizon) &&
		NormalTransactionIdPrecedes(running->oldestRunningXid,
									builder->initial_xmin_horizon))
	{
		ereport(DEBUG1,
				(errmsg_internal("skipping snapshot at %X/%X while building logical decoding snapshot, xmin horizon too low",
								 (uint32) (lsn >> 32), (uint32) lsn),
				 errdetail_internal("initial xmin horizon of %u vs the snapshot's %u",
									builder->initial_xmin_horizon, running->oldestRunningXid)));


		SnapBuildWaitSnapshot(running, builder->initial_xmin_horizon);

		return true;
	}

	/*
	 * a) No transaction were running, we can jump to consistent.
	 *
	 * This is not affected by races around xl_running_xacts, because we can
	 * miss transaction commits, but currently not transactions starting.
	 *
	 * NB: We might have already started to incrementally assemble a snapshot,
	 * so we need to be careful to deal with that.
	 */
	if (running->oldestRunningXid == running->nextXid)
	{
		if (builder->start_decoding_at == InvalidXLogRecPtr ||
			builder->start_decoding_at <= lsn)
			/* can decode everything after this */
			builder->start_decoding_at = lsn + 1;

		/* As no transactions were running xmin/xmax can be trivially set. */
		builder->xmin = running->nextXid;	/* < are finished */
		builder->xmax = running->nextXid;	/* >= are running */

		/* so we can safely use the faster comparisons */
		Assert(TransactionIdIsNormal(builder->xmin));
		Assert(TransactionIdIsNormal(builder->xmax));

		builder->state = SNAPBUILD_CONSISTENT;
		SnapBuildStartNextPhaseAt(builder, InvalidTransactionId);

		ereport(LOG,
				(errmsg("logical decoding found consistent point at %X/%X",
						(uint32) (lsn >> 32), (uint32) lsn),
				 errdetail("There are no running transactions.")));

		return false;
	}
	/* b) valid on disk state and not building full snapshot */
	else if (!builder->building_full_snapshot &&
			 SnapBuildRestore(builder, lsn))
	{
		/* there won't be any state to cleanup */
		return false;
	}

	/*
	 * c) transition from START to BUILDING_SNAPSHOT.
	 *
	 * In START state, and a xl_running_xacts record with running xacts is
	 * encountered.  In that case, switch to BUILDING_SNAPSHOT state, and
	 * record xl_running_xacts->nextXid.  Once all running xacts have finished
	 * (i.e. they're all >= nextXid), we have a complete catalog snapshot.  It
	 * might look that we could use xl_running_xact's ->xids information to
	 * get there quicker, but that is problematic because transactions marked
	 * as running, might already have inserted their commit record - it's
	 * infeasible to change that with locking.
	 */
	else if (builder->state == SNAPBUILD_START)
	{
		builder->state = SNAPBUILD_BUILDING_SNAPSHOT;
		SnapBuildStartNextPhaseAt(builder, running->nextXid);

		/*
		 * Start with an xmin/xmax that's correct for future, when all the
		 * currently running transactions have finished. We'll update both
		 * while waiting for the pending transactions to finish.
		 */
		builder->xmin = running->nextXid;	/* < are finished */
		builder->xmax = running->nextXid;	/* >= are running */

		/* so we can safely use the faster comparisons */
		Assert(TransactionIdIsNormal(builder->xmin));
		Assert(TransactionIdIsNormal(builder->xmax));

		ereport(LOG,
				(errmsg("logical decoding found initial starting point at %X/%X",
						(uint32) (lsn >> 32), (uint32) lsn),
				 errdetail("Waiting for transactions (approximately %d) older than %u to end.",
						   running->xcnt, running->nextXid)));

		SnapBuildWaitSnapshot(running, running->nextXid);
	}

	/*
	 * c) transition from BUILDING_SNAPSHOT to FULL_SNAPSHOT.
	 *
	 * In BUILDING_SNAPSHOT state, and this xl_running_xacts' oldestRunningXid
	 * is >= than nextXid from when we switched to BUILDING_SNAPSHOT.  This
	 * means all transactions starting afterwards have enough information to
	 * be decoded.  Switch to FULL_SNAPSHOT.
	 */
	else if (builder->state == SNAPBUILD_BUILDING_SNAPSHOT &&
			 TransactionIdPrecedesOrEquals(SnapBuildNextPhaseAt(builder),
										   running->oldestRunningXid))
	{
		builder->state = SNAPBUILD_FULL_SNAPSHOT;
		SnapBuildStartNextPhaseAt(builder, running->nextXid);

		ereport(LOG,
				(errmsg("logical decoding found initial consistent point at %X/%X",
						(uint32) (lsn >> 32), (uint32) lsn),
				 errdetail("Waiting for transactions (approximately %d) older than %u to end.",
						   running->xcnt, running->nextXid)));

		SnapBuildWaitSnapshot(running, running->nextXid);
	}

	/*
	 * c) transition from FULL_SNAPSHOT to CONSISTENT.
	 *
	 * In FULL_SNAPSHOT state (see d) ), and this xl_running_xacts'
	 * oldestRunningXid is >= than nextXid from when we switched to
	 * FULL_SNAPSHOT.  This means all transactions that are currently in
	 * progress have a catalog snapshot, and all their changes have been
	 * collected.  Switch to CONSISTENT.
	 */
	else if (builder->state == SNAPBUILD_FULL_SNAPSHOT &&
			 TransactionIdPrecedesOrEquals(SnapBuildNextPhaseAt(builder),
										   running->oldestRunningXid))
	{
		builder->state = SNAPBUILD_CONSISTENT;
		SnapBuildStartNextPhaseAt(builder, InvalidTransactionId);

		ereport(LOG,
				(errmsg("logical decoding found consistent point at %X/%X",
						(uint32) (lsn >> 32), (uint32) lsn),
				 errdetail("There are no old transactions anymore.")));
	}

	/*
	 * We already started to track running xacts and need to wait for all
	 * in-progress ones to finish. We fall through to the normal processing of
	 * records so incremental cleanup can be performed.
	 */
	return true;

}