#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  indisclustered; } ;
struct TYPE_13__ {TYPE_1__* rd_rel; } ;
struct TYPE_12__ {scalar_t__ relkind; scalar_t__ relisshared; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__* Form_pg_index ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int CLUOPT_RECHECK ; 
 int CLUOPT_VERBOSE ; 
 int /*<<< orphan*/  CheckTableNotInUse (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INDEXRELID ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROGRESS_CLUSTER_COMMAND ; 
 int /*<<< orphan*/  PROGRESS_CLUSTER_COMMAND_CLUSTER ; 
 int /*<<< orphan*/  PROGRESS_CLUSTER_COMMAND_VACUUM_FULL ; 
 int /*<<< orphan*/  PROGRESS_COMMAND_CLUSTER ; 
 scalar_t__ RELATION_IS_OTHER_TEMP (TYPE_2__*) ; 
 scalar_t__ RELKIND_MATVIEW ; 
 int /*<<< orphan*/  RELOID ; 
 int /*<<< orphan*/  RelationIsPopulated (TYPE_2__*) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCacheExists1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransferPredicateLocksToHeapRelation (TYPE_2__*) ; 
 int /*<<< orphan*/  check_index_is_clusterable (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  pg_class_ownercheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgstat_progress_end_command () ; 
 int /*<<< orphan*/  pgstat_progress_start_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgstat_progress_update_param (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rebuild_relation (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  relation_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* try_relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
cluster_rel(Oid tableOid, Oid indexOid, int options)
{
	Relation	OldHeap;
	bool		verbose = ((options & CLUOPT_VERBOSE) != 0);
	bool		recheck = ((options & CLUOPT_RECHECK) != 0);

	/* Check for user-requested abort. */
	CHECK_FOR_INTERRUPTS();

	pgstat_progress_start_command(PROGRESS_COMMAND_CLUSTER, tableOid);
	if (OidIsValid(indexOid))
		pgstat_progress_update_param(PROGRESS_CLUSTER_COMMAND,
									 PROGRESS_CLUSTER_COMMAND_CLUSTER);
	else
		pgstat_progress_update_param(PROGRESS_CLUSTER_COMMAND,
									 PROGRESS_CLUSTER_COMMAND_VACUUM_FULL);

	/*
	 * We grab exclusive access to the target rel and index for the duration
	 * of the transaction.  (This is redundant for the single-transaction
	 * case, since cluster() already did it.)  The index lock is taken inside
	 * check_index_is_clusterable.
	 */
	OldHeap = try_relation_open(tableOid, AccessExclusiveLock);

	/* If the table has gone away, we can skip processing it */
	if (!OldHeap)
	{
		pgstat_progress_end_command();
		return;
	}

	/*
	 * Since we may open a new transaction for each relation, we have to check
	 * that the relation still is what we think it is.
	 *
	 * If this is a single-transaction CLUSTER, we can skip these tests. We
	 * *must* skip the one on indisclustered since it would reject an attempt
	 * to cluster a not-previously-clustered index.
	 */
	if (recheck)
	{
		HeapTuple	tuple;
		Form_pg_index indexForm;

		/* Check that the user still owns the relation */
		if (!pg_class_ownercheck(tableOid, GetUserId()))
		{
			relation_close(OldHeap, AccessExclusiveLock);
			pgstat_progress_end_command();
			return;
		}

		/*
		 * Silently skip a temp table for a remote session.  Only doing this
		 * check in the "recheck" case is appropriate (which currently means
		 * somebody is executing a database-wide CLUSTER), because there is
		 * another check in cluster() which will stop any attempt to cluster
		 * remote temp tables by name.  There is another check in cluster_rel
		 * which is redundant, but we leave it for extra safety.
		 */
		if (RELATION_IS_OTHER_TEMP(OldHeap))
		{
			relation_close(OldHeap, AccessExclusiveLock);
			pgstat_progress_end_command();
			return;
		}

		if (OidIsValid(indexOid))
		{
			/*
			 * Check that the index still exists
			 */
			if (!SearchSysCacheExists1(RELOID, ObjectIdGetDatum(indexOid)))
			{
				relation_close(OldHeap, AccessExclusiveLock);
				pgstat_progress_end_command();
				return;
			}

			/*
			 * Check that the index is still the one with indisclustered set.
			 */
			tuple = SearchSysCache1(INDEXRELID, ObjectIdGetDatum(indexOid));
			if (!HeapTupleIsValid(tuple))	/* probably can't happen */
			{
				relation_close(OldHeap, AccessExclusiveLock);
				pgstat_progress_end_command();
				return;
			}
			indexForm = (Form_pg_index) GETSTRUCT(tuple);
			if (!indexForm->indisclustered)
			{
				ReleaseSysCache(tuple);
				relation_close(OldHeap, AccessExclusiveLock);
				pgstat_progress_end_command();
				return;
			}
			ReleaseSysCache(tuple);
		}
	}

	/*
	 * We allow VACUUM FULL, but not CLUSTER, on shared catalogs.  CLUSTER
	 * would work in most respects, but the index would only get marked as
	 * indisclustered in the current database, leading to unexpected behavior
	 * if CLUSTER were later invoked in another database.
	 */
	if (OidIsValid(indexOid) && OldHeap->rd_rel->relisshared)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("cannot cluster a shared catalog")));

	/*
	 * Don't process temp tables of other backends ... their local buffer
	 * manager is not going to cope.
	 */
	if (RELATION_IS_OTHER_TEMP(OldHeap))
	{
		if (OidIsValid(indexOid))
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("cannot cluster temporary tables of other sessions")));
		else
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("cannot vacuum temporary tables of other sessions")));
	}

	/*
	 * Also check for active uses of the relation in the current transaction,
	 * including open scans and pending AFTER trigger events.
	 */
	CheckTableNotInUse(OldHeap, OidIsValid(indexOid) ? "CLUSTER" : "VACUUM");

	/* Check heap and index are valid to cluster on */
	if (OidIsValid(indexOid))
		check_index_is_clusterable(OldHeap, indexOid, recheck, AccessExclusiveLock);

	/*
	 * Quietly ignore the request if this is a materialized view which has not
	 * been populated from its query. No harm is done because there is no data
	 * to deal with, and we don't want to throw an error if this is part of a
	 * multi-relation request -- for example, CLUSTER was run on the entire
	 * database.
	 */
	if (OldHeap->rd_rel->relkind == RELKIND_MATVIEW &&
		!RelationIsPopulated(OldHeap))
	{
		relation_close(OldHeap, AccessExclusiveLock);
		pgstat_progress_end_command();
		return;
	}

	/*
	 * All predicate locks on the tuples or pages are about to be made
	 * invalid, because we move tuples around.  Promote them to relation
	 * locks.  Predicate locks on indexes will be promoted when they are
	 * reindexed.
	 */
	TransferPredicateLocksToHeapRelation(OldHeap);

	/* rebuild_relation does all the dirty work */
	rebuild_relation(OldHeap, indexOid, verbose);

	/* NB: rebuild_relation does table_close() on OldHeap */

	pgstat_progress_end_command();
}