#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_14__ ;

/* Type definitions */
struct TYPE_17__ {int options; scalar_t__ log_min_duration; scalar_t__ index_cleanup; scalar_t__ truncate; scalar_t__ is_wraparound; } ;
typedef  TYPE_2__ VacuumParams ;
struct TYPE_20__ {scalar_t__ relkind; scalar_t__ reltoastrelid; scalar_t__ relowner; } ;
struct TYPE_16__ {int /*<<< orphan*/  lockRelId; } ;
struct TYPE_19__ {TYPE_7__* rd_rel; int /*<<< orphan*/ * rd_options; TYPE_1__ rd_lockInfo; } ;
struct TYPE_18__ {scalar_t__ vacuum_truncate; scalar_t__ vacuum_index_cleanup; } ;
struct TYPE_15__ {int /*<<< orphan*/  vacuumFlags; } ;
typedef  TYPE_3__ StdRdOptions ;
typedef  TYPE_4__* Relation ;
typedef  int /*<<< orphan*/  RangeVar ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  LockRelId ;
typedef  int /*<<< orphan*/  LOCKMODE ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AtEOXact_GUC (int,int) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int CLUOPT_VERBOSE ; 
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/  GetTransactionSnapshot () ; 
 int /*<<< orphan*/  GetUserIdAndSecContext (scalar_t__*,int*) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  LockRelationIdForSession (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_14__* MyPgXact ; 
 int NewGUCNestLevel () ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  PROC_IN_VACUUM ; 
 int /*<<< orphan*/  PROC_VACUUM_FOR_WRAPAROUND ; 
 int /*<<< orphan*/  PopActiveSnapshot () ; 
 int /*<<< orphan*/  ProcArrayLock ; 
 int /*<<< orphan*/  PushActiveSnapshot (int /*<<< orphan*/ ) ; 
 scalar_t__ RELATION_IS_OTHER_TEMP (TYPE_4__*) ; 
 scalar_t__ RELKIND_MATVIEW ; 
 scalar_t__ RELKIND_PARTITIONED_TABLE ; 
 scalar_t__ RELKIND_RELATION ; 
 scalar_t__ RELKIND_TOASTVALUE ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_4__*) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_4__*) ; 
 int SECURITY_RESTRICTED_OPERATION ; 
 int /*<<< orphan*/  SetUserIdAndSecContext (scalar_t__,int) ; 
 int /*<<< orphan*/  ShareUpdateExclusiveLock ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int /*<<< orphan*/  UnlockRelationIdForSession (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int VACOPT_FULL ; 
 int VACOPT_SKIPTOAST ; 
 scalar_t__ VACOPT_TERNARY_DEFAULT ; 
 void* VACOPT_TERNARY_DISABLED ; 
 void* VACOPT_TERNARY_ENABLED ; 
 int VACOPT_VACUUM ; 
 int VACOPT_VERBOSE ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  cluster_rel (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_close (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_relation_vacuum (TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vac_strategy ; 
 int /*<<< orphan*/  vacuum_is_relation_owner (int /*<<< orphan*/ ,TYPE_7__*,int) ; 
 TYPE_4__* vacuum_open_relation (scalar_t__,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
vacuum_rel(Oid relid, RangeVar *relation, VacuumParams *params)
{
	LOCKMODE	lmode;
	Relation	onerel;
	LockRelId	onerelid;
	Oid			toast_relid;
	Oid			save_userid;
	int			save_sec_context;
	int			save_nestlevel;

	Assert(params != NULL);

	/* Begin a transaction for vacuuming this relation */
	StartTransactionCommand();

	/*
	 * Functions in indexes may want a snapshot set.  Also, setting a snapshot
	 * ensures that RecentGlobalXmin is kept truly recent.
	 */
	PushActiveSnapshot(GetTransactionSnapshot());

	if (!(params->options & VACOPT_FULL))
	{
		/*
		 * In lazy vacuum, we can set the PROC_IN_VACUUM flag, which lets
		 * other concurrent VACUUMs know that they can ignore this one while
		 * determining their OldestXmin.  (The reason we don't set it during a
		 * full VACUUM is exactly that we may have to run user-defined
		 * functions for functional indexes, and we want to make sure that if
		 * they use the snapshot set above, any tuples it requires can't get
		 * removed from other tables.  An index function that depends on the
		 * contents of other tables is arguably broken, but we won't break it
		 * here by violating transaction semantics.)
		 *
		 * We also set the VACUUM_FOR_WRAPAROUND flag, which is passed down by
		 * autovacuum; it's used to avoid canceling a vacuum that was invoked
		 * in an emergency.
		 *
		 * Note: these flags remain set until CommitTransaction or
		 * AbortTransaction.  We don't want to clear them until we reset
		 * MyPgXact->xid/xmin, else OldestXmin might appear to go backwards,
		 * which is probably Not Good.
		 */
		LWLockAcquire(ProcArrayLock, LW_EXCLUSIVE);
		MyPgXact->vacuumFlags |= PROC_IN_VACUUM;
		if (params->is_wraparound)
			MyPgXact->vacuumFlags |= PROC_VACUUM_FOR_WRAPAROUND;
		LWLockRelease(ProcArrayLock);
	}

	/*
	 * Check for user-requested abort.  Note we want this to be inside a
	 * transaction, so xact.c doesn't issue useless WARNING.
	 */
	CHECK_FOR_INTERRUPTS();

	/*
	 * Determine the type of lock we want --- hard exclusive lock for a FULL
	 * vacuum, but just ShareUpdateExclusiveLock for concurrent vacuum. Either
	 * way, we can be sure that no other backend is vacuuming the same table.
	 */
	lmode = (params->options & VACOPT_FULL) ?
		AccessExclusiveLock : ShareUpdateExclusiveLock;

	/* open the relation and get the appropriate lock on it */
	onerel = vacuum_open_relation(relid, relation, params->options,
								  params->log_min_duration >= 0, lmode);

	/* leave if relation could not be opened or locked */
	if (!onerel)
	{
		PopActiveSnapshot();
		CommitTransactionCommand();
		return false;
	}

	/*
	 * Check if relation needs to be skipped based on ownership.  This check
	 * happens also when building the relation list to vacuum for a manual
	 * operation, and needs to be done additionally here as VACUUM could
	 * happen across multiple transactions where relation ownership could have
	 * changed in-between.  Make sure to only generate logs for VACUUM in this
	 * case.
	 */
	if (!vacuum_is_relation_owner(RelationGetRelid(onerel),
								  onerel->rd_rel,
								  params->options & VACOPT_VACUUM))
	{
		relation_close(onerel, lmode);
		PopActiveSnapshot();
		CommitTransactionCommand();
		return false;
	}

	/*
	 * Check that it's of a vacuumable relkind.
	 */
	if (onerel->rd_rel->relkind != RELKIND_RELATION &&
		onerel->rd_rel->relkind != RELKIND_MATVIEW &&
		onerel->rd_rel->relkind != RELKIND_TOASTVALUE &&
		onerel->rd_rel->relkind != RELKIND_PARTITIONED_TABLE)
	{
		ereport(WARNING,
				(errmsg("skipping \"%s\" --- cannot vacuum non-tables or special system tables",
						RelationGetRelationName(onerel))));
		relation_close(onerel, lmode);
		PopActiveSnapshot();
		CommitTransactionCommand();
		return false;
	}

	/*
	 * Silently ignore tables that are temp tables of other backends ---
	 * trying to vacuum these will lead to great unhappiness, since their
	 * contents are probably not up-to-date on disk.  (We don't throw a
	 * warning here; it would just lead to chatter during a database-wide
	 * VACUUM.)
	 */
	if (RELATION_IS_OTHER_TEMP(onerel))
	{
		relation_close(onerel, lmode);
		PopActiveSnapshot();
		CommitTransactionCommand();
		return false;
	}

	/*
	 * Silently ignore partitioned tables as there is no work to be done.  The
	 * useful work is on their child partitions, which have been queued up for
	 * us separately.
	 */
	if (onerel->rd_rel->relkind == RELKIND_PARTITIONED_TABLE)
	{
		relation_close(onerel, lmode);
		PopActiveSnapshot();
		CommitTransactionCommand();
		/* It's OK to proceed with ANALYZE on this table */
		return true;
	}

	/*
	 * Get a session-level lock too. This will protect our access to the
	 * relation across multiple transactions, so that we can vacuum the
	 * relation's TOAST table (if any) secure in the knowledge that no one is
	 * deleting the parent relation.
	 *
	 * NOTE: this cannot block, even if someone else is waiting for access,
	 * because the lock manager knows that both lock requests are from the
	 * same process.
	 */
	onerelid = onerel->rd_lockInfo.lockRelId;
	LockRelationIdForSession(&onerelid, lmode);

	/* Set index cleanup option based on reloptions if not yet */
	if (params->index_cleanup == VACOPT_TERNARY_DEFAULT)
	{
		if (onerel->rd_options == NULL ||
			((StdRdOptions *) onerel->rd_options)->vacuum_index_cleanup)
			params->index_cleanup = VACOPT_TERNARY_ENABLED;
		else
			params->index_cleanup = VACOPT_TERNARY_DISABLED;
	}

	/* Set truncate option based on reloptions if not yet */
	if (params->truncate == VACOPT_TERNARY_DEFAULT)
	{
		if (onerel->rd_options == NULL ||
			((StdRdOptions *) onerel->rd_options)->vacuum_truncate)
			params->truncate = VACOPT_TERNARY_ENABLED;
		else
			params->truncate = VACOPT_TERNARY_DISABLED;
	}

	/*
	 * Remember the relation's TOAST relation for later, if the caller asked
	 * us to process it.  In VACUUM FULL, though, the toast table is
	 * automatically rebuilt by cluster_rel so we shouldn't recurse to it.
	 */
	if (!(params->options & VACOPT_SKIPTOAST) && !(params->options & VACOPT_FULL))
		toast_relid = onerel->rd_rel->reltoastrelid;
	else
		toast_relid = InvalidOid;

	/*
	 * Switch to the table owner's userid, so that any index functions are run
	 * as that user.  Also lock down security-restricted operations and
	 * arrange to make GUC variable changes local to this command. (This is
	 * unnecessary, but harmless, for lazy VACUUM.)
	 */
	GetUserIdAndSecContext(&save_userid, &save_sec_context);
	SetUserIdAndSecContext(onerel->rd_rel->relowner,
						   save_sec_context | SECURITY_RESTRICTED_OPERATION);
	save_nestlevel = NewGUCNestLevel();

	/*
	 * Do the actual work --- either FULL or "lazy" vacuum
	 */
	if (params->options & VACOPT_FULL)
	{
		int			cluster_options = 0;

		/* close relation before vacuuming, but hold lock until commit */
		relation_close(onerel, NoLock);
		onerel = NULL;

		if ((params->options & VACOPT_VERBOSE) != 0)
			cluster_options |= CLUOPT_VERBOSE;

		/* VACUUM FULL is now a variant of CLUSTER; see cluster.c */
		cluster_rel(relid, InvalidOid, cluster_options);
	}
	else
		table_relation_vacuum(onerel, params, vac_strategy);

	/* Roll back any GUC changes executed by index functions */
	AtEOXact_GUC(false, save_nestlevel);

	/* Restore userid and security context */
	SetUserIdAndSecContext(save_userid, save_sec_context);

	/* all done with this class, but hold lock until commit */
	if (onerel)
		relation_close(onerel, NoLock);

	/*
	 * Complete the transaction and free all temporary memory used.
	 */
	PopActiveSnapshot();
	CommitTransactionCommand();

	/*
	 * If the relation has a secondary toast rel, vacuum that too while we
	 * still hold the session lock on the master table.  Note however that
	 * "analyze" will not get done on the toast table.  This is good, because
	 * the toaster always uses hardcoded index access and statistics are
	 * totally unimportant for toast relations.
	 */
	if (toast_relid != InvalidOid)
		vacuum_rel(toast_relid, NULL, params);

	/*
	 * Now release the session-level lock on the master table.
	 */
	UnlockRelationIdForSession(&onerelid, lmode);

	/* Report that we really did it. */
	return true;
}