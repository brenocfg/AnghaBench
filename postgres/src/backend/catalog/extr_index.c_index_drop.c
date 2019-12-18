#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_25__ {int /*<<< orphan*/  relId; int /*<<< orphan*/  dbId; } ;
struct TYPE_22__ {TYPE_4__ lockRelId; } ;
struct TYPE_24__ {TYPE_2__* rd_rel; TYPE_1__ rd_lockInfo; } ;
struct TYPE_23__ {scalar_t__ relkind; } ;
typedef  TYPE_3__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_4__ LockRelId ;
typedef  int /*<<< orphan*/  LOCKTAG ;
typedef  int /*<<< orphan*/  LOCKMODE ;
typedef  TYPE_5__* HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  Anum_pg_index_indexprs ; 
 int /*<<< orphan*/  CacheInvalidateRelcache (TYPE_3__*) ; 
 int /*<<< orphan*/  CatalogTupleDelete (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CheckTableNotInUse (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/  DeleteAttributeTuples (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteInheritsTuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteRelationTuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GetTopTransactionIdIfAny () ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_5__*) ; 
 int /*<<< orphan*/  INDEXRELID ; 
 int /*<<< orphan*/  INDEX_DROP_CLEAR_VALID ; 
 int /*<<< orphan*/  IndexGetRelation (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IndexRelationId ; 
 int /*<<< orphan*/  InvalidOid ; 
 scalar_t__ InvalidTransactionId ; 
 int /*<<< orphan*/  LockRelationIdForSession (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PopActiveSnapshot () ; 
 scalar_t__ RELKIND_PARTITIONED_INDEX ; 
 int /*<<< orphan*/  RelationDropStorage (TYPE_3__*) ; 
 int /*<<< orphan*/  RelationForgetRelation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (TYPE_3__*) ; 
 int /*<<< orphan*/  ReleaseSysCache (TYPE_5__*) ; 
 int /*<<< orphan*/  RemoveStatistics (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  SET_LOCKTAG_RELATION (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShareUpdateExclusiveLock ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int /*<<< orphan*/  TransferPredicateLocksToHeapRelation (TYPE_3__*) ; 
 int /*<<< orphan*/  UnlockRelationIdForSession (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitForLockers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  heap_attisnull (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_close (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_concurrently_set_dead (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* index_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_set_state_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
index_drop(Oid indexId, bool concurrent, bool concurrent_lock_mode)
{
	Oid			heapId;
	Relation	userHeapRelation;
	Relation	userIndexRelation;
	Relation	indexRelation;
	HeapTuple	tuple;
	bool		hasexprs;
	LockRelId	heaprelid,
				indexrelid;
	LOCKTAG		heaplocktag;
	LOCKMODE	lockmode;

	/*
	 * To drop an index safely, we must grab exclusive lock on its parent
	 * table.  Exclusive lock on the index alone is insufficient because
	 * another backend might be about to execute a query on the parent table.
	 * If it relies on a previously cached list of index OIDs, then it could
	 * attempt to access the just-dropped index.  We must therefore take a
	 * table lock strong enough to prevent all queries on the table from
	 * proceeding until we commit and send out a shared-cache-inval notice
	 * that will make them update their index lists.
	 *
	 * In the concurrent case we avoid this requirement by disabling index use
	 * in multiple steps and waiting out any transactions that might be using
	 * the index, so we don't need exclusive lock on the parent table. Instead
	 * we take ShareUpdateExclusiveLock, to ensure that two sessions aren't
	 * doing CREATE/DROP INDEX CONCURRENTLY on the same index.  (We will get
	 * AccessExclusiveLock on the index below, once we're sure nobody else is
	 * using it.)
	 */
	heapId = IndexGetRelation(indexId, false);
	lockmode = (concurrent || concurrent_lock_mode) ? ShareUpdateExclusiveLock : AccessExclusiveLock;
	userHeapRelation = table_open(heapId, lockmode);
	userIndexRelation = index_open(indexId, lockmode);

	/*
	 * We might still have open queries using it in our own session, which the
	 * above locking won't prevent, so test explicitly.
	 */
	CheckTableNotInUse(userIndexRelation, "DROP INDEX");

	/*
	 * Drop Index Concurrently is more or less the reverse process of Create
	 * Index Concurrently.
	 *
	 * First we unset indisvalid so queries starting afterwards don't use the
	 * index to answer queries anymore.  We have to keep indisready = true so
	 * transactions that are still scanning the index can continue to see
	 * valid index contents.  For instance, if they are using READ COMMITTED
	 * mode, and another transaction makes changes and commits, they need to
	 * see those new tuples in the index.
	 *
	 * After all transactions that could possibly have used the index for
	 * queries end, we can unset indisready and indislive, then wait till
	 * nobody could be touching it anymore.  (Note: we need indislive because
	 * this state must be distinct from the initial state during CREATE INDEX
	 * CONCURRENTLY, which has indislive true while indisready and indisvalid
	 * are false.  That's because in that state, transactions must examine the
	 * index for HOT-safety decisions, while in this state we don't want them
	 * to open it at all.)
	 *
	 * Since all predicate locks on the index are about to be made invalid, we
	 * must promote them to predicate locks on the heap.  In the
	 * non-concurrent case we can just do that now.  In the concurrent case
	 * it's a bit trickier.  The predicate locks must be moved when there are
	 * no index scans in progress on the index and no more can subsequently
	 * start, so that no new predicate locks can be made on the index.  Also,
	 * they must be moved before heap inserts stop maintaining the index, else
	 * the conflict with the predicate lock on the index gap could be missed
	 * before the lock on the heap relation is in place to detect a conflict
	 * based on the heap tuple insert.
	 */
	if (concurrent)
	{
		/*
		 * We must commit our transaction in order to make the first pg_index
		 * state update visible to other sessions.  If the DROP machinery has
		 * already performed any other actions (removal of other objects,
		 * pg_depend entries, etc), the commit would make those actions
		 * permanent, which would leave us with inconsistent catalog state if
		 * we fail partway through the following sequence.  Since DROP INDEX
		 * CONCURRENTLY is restricted to dropping just one index that has no
		 * dependencies, we should get here before anything's been done ---
		 * but let's check that to be sure.  We can verify that the current
		 * transaction has not executed any transactional updates by checking
		 * that no XID has been assigned.
		 */
		if (GetTopTransactionIdIfAny() != InvalidTransactionId)
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("DROP INDEX CONCURRENTLY must be first action in transaction")));

		/*
		 * Mark index invalid by updating its pg_index entry
		 */
		index_set_state_flags(indexId, INDEX_DROP_CLEAR_VALID);

		/*
		 * Invalidate the relcache for the table, so that after this commit
		 * all sessions will refresh any cached plans that might reference the
		 * index.
		 */
		CacheInvalidateRelcache(userHeapRelation);

		/* save lockrelid and locktag for below, then close but keep locks */
		heaprelid = userHeapRelation->rd_lockInfo.lockRelId;
		SET_LOCKTAG_RELATION(heaplocktag, heaprelid.dbId, heaprelid.relId);
		indexrelid = userIndexRelation->rd_lockInfo.lockRelId;

		table_close(userHeapRelation, NoLock);
		index_close(userIndexRelation, NoLock);

		/*
		 * We must commit our current transaction so that the indisvalid
		 * update becomes visible to other transactions; then start another.
		 * Note that any previously-built data structures are lost in the
		 * commit.  The only data we keep past here are the relation IDs.
		 *
		 * Before committing, get a session-level lock on the table, to ensure
		 * that neither it nor the index can be dropped before we finish. This
		 * cannot block, even if someone else is waiting for access, because
		 * we already have the same lock within our transaction.
		 */
		LockRelationIdForSession(&heaprelid, ShareUpdateExclusiveLock);
		LockRelationIdForSession(&indexrelid, ShareUpdateExclusiveLock);

		PopActiveSnapshot();
		CommitTransactionCommand();
		StartTransactionCommand();

		/*
		 * Now we must wait until no running transaction could be using the
		 * index for a query.  Use AccessExclusiveLock here to check for
		 * running transactions that hold locks of any kind on the table. Note
		 * we do not need to worry about xacts that open the table for reading
		 * after this point; they will see the index as invalid when they open
		 * the relation.
		 *
		 * Note: the reason we use actual lock acquisition here, rather than
		 * just checking the ProcArray and sleeping, is that deadlock is
		 * possible if one of the transactions in question is blocked trying
		 * to acquire an exclusive lock on our table.  The lock code will
		 * detect deadlock and error out properly.
		 *
		 * Note: we report progress through WaitForLockers() unconditionally
		 * here, even though it will only be used when we're called by REINDEX
		 * CONCURRENTLY and not when called by DROP INDEX CONCURRENTLY.
		 */
		WaitForLockers(heaplocktag, AccessExclusiveLock, true);

		/* Finish invalidation of index and mark it as dead */
		index_concurrently_set_dead(heapId, indexId);

		/*
		 * Again, commit the transaction to make the pg_index update visible
		 * to other sessions.
		 */
		CommitTransactionCommand();
		StartTransactionCommand();

		/*
		 * Wait till every transaction that saw the old index state has
		 * finished.  See above about progress reporting.
		 */
		WaitForLockers(heaplocktag, AccessExclusiveLock, true);

		/*
		 * Re-open relations to allow us to complete our actions.
		 *
		 * At this point, nothing should be accessing the index, but lets
		 * leave nothing to chance and grab AccessExclusiveLock on the index
		 * before the physical deletion.
		 */
		userHeapRelation = table_open(heapId, ShareUpdateExclusiveLock);
		userIndexRelation = index_open(indexId, AccessExclusiveLock);
	}
	else
	{
		/* Not concurrent, so just transfer predicate locks and we're good */
		TransferPredicateLocksToHeapRelation(userIndexRelation);
	}

	/*
	 * Schedule physical removal of the files (if any)
	 */
	if (userIndexRelation->rd_rel->relkind != RELKIND_PARTITIONED_INDEX)
		RelationDropStorage(userIndexRelation);

	/*
	 * Close and flush the index's relcache entry, to ensure relcache doesn't
	 * try to rebuild it while we're deleting catalog entries. We keep the
	 * lock though.
	 */
	index_close(userIndexRelation, NoLock);

	RelationForgetRelation(indexId);

	/*
	 * fix INDEX relation, and check for expressional index
	 */
	indexRelation = table_open(IndexRelationId, RowExclusiveLock);

	tuple = SearchSysCache1(INDEXRELID, ObjectIdGetDatum(indexId));
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "cache lookup failed for index %u", indexId);

	hasexprs = !heap_attisnull(tuple, Anum_pg_index_indexprs,
							   RelationGetDescr(indexRelation));

	CatalogTupleDelete(indexRelation, &tuple->t_self);

	ReleaseSysCache(tuple);
	table_close(indexRelation, RowExclusiveLock);

	/*
	 * if it has any expression columns, we might have stored statistics about
	 * them.
	 */
	if (hasexprs)
		RemoveStatistics(indexId, 0);

	/*
	 * fix ATTRIBUTE relation
	 */
	DeleteAttributeTuples(indexId);

	/*
	 * fix RELATION relation
	 */
	DeleteRelationTuple(indexId);

	/*
	 * fix INHERITS relation
	 */
	DeleteInheritsTuple(indexId, InvalidOid);

	/*
	 * We are presently too lazy to attempt to compute the new correct value
	 * of relhasindex (the next VACUUM will fix it if necessary). So there is
	 * no need to update the pg_class tuple for the owning relation. But we
	 * must send out a shared-cache-inval notice on the owning relation to
	 * ensure other backends update their relcache lists of indexes.  (In the
	 * concurrent case, this is redundant but harmless.)
	 */
	CacheInvalidateRelcache(userHeapRelation);

	/*
	 * Close owning rel, but keep lock
	 */
	table_close(userHeapRelation, NoLock);

	/*
	 * Release the session locks before we go.
	 */
	if (concurrent)
	{
		UnlockRelationIdForSession(&heaprelid, ShareUpdateExclusiveLock);
		UnlockRelationIdForSession(&indexrelid, ShareUpdateExclusiveLock);
	}
}