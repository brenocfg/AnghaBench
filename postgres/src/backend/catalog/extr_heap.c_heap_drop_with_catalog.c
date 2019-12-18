#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ relispartition; } ;
struct TYPE_19__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_18__ {TYPE_1__* rd_rel; } ;
struct TYPE_17__ {scalar_t__ relkind; } ;
typedef  TYPE_2__* Relation ;
typedef  scalar_t__ Oid ;
typedef  TYPE_3__* HeapTuple ;
typedef  TYPE_4__* Form_pg_class ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  CacheInvalidateRelcacheByRelid (scalar_t__) ; 
 int /*<<< orphan*/  CatalogTupleDelete (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CheckTableForSerializableConflictIn (TYPE_2__*) ; 
 int /*<<< orphan*/  CheckTableNotInUse (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  DeleteAttributeTuples (scalar_t__) ; 
 int /*<<< orphan*/  DeleteRelationTuple (scalar_t__) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FOREIGNTABLEREL ; 
 int /*<<< orphan*/  ForeignTableRelationId ; 
 scalar_t__ GETSTRUCT (TYPE_3__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_3__*) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  LockRelationOid (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 scalar_t__ OidIsValid (scalar_t__) ; 
 scalar_t__ RELKIND_COMPOSITE_TYPE ; 
 scalar_t__ RELKIND_FOREIGN_TABLE ; 
 scalar_t__ RELKIND_PARTITIONED_TABLE ; 
 scalar_t__ RELKIND_VIEW ; 
 int /*<<< orphan*/  RELOID ; 
 int /*<<< orphan*/  RelationDropStorage (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationForgetRelation (scalar_t__) ; 
 int /*<<< orphan*/  RelationRemoveInheritance (scalar_t__) ; 
 int /*<<< orphan*/  ReleaseSysCache (TYPE_3__*) ; 
 int /*<<< orphan*/  RemovePartitionKeyByRelId (scalar_t__) ; 
 int /*<<< orphan*/  RemoveStatistics (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveSubscriptionRel (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_3__* SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ get_default_partition_oid (scalar_t__) ; 
 scalar_t__ get_partition_parent (scalar_t__) ; 
 int /*<<< orphan*/  relation_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* relation_open (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_on_commit_action (scalar_t__) ; 
 int /*<<< orphan*/  table_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_default_partition_oid (scalar_t__,scalar_t__) ; 

void
heap_drop_with_catalog(Oid relid)
{
	Relation	rel;
	HeapTuple	tuple;
	Oid			parentOid = InvalidOid,
				defaultPartOid = InvalidOid;

	/*
	 * To drop a partition safely, we must grab exclusive lock on its parent,
	 * because another backend might be about to execute a query on the parent
	 * table.  If it relies on previously cached partition descriptor, then it
	 * could attempt to access the just-dropped relation as its partition. We
	 * must therefore take a table lock strong enough to prevent all queries
	 * on the table from proceeding until we commit and send out a
	 * shared-cache-inval notice that will make them update their partition
	 * descriptors.
	 */
	tuple = SearchSysCache1(RELOID, ObjectIdGetDatum(relid));
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "cache lookup failed for relation %u", relid);
	if (((Form_pg_class) GETSTRUCT(tuple))->relispartition)
	{
		parentOid = get_partition_parent(relid);
		LockRelationOid(parentOid, AccessExclusiveLock);

		/*
		 * If this is not the default partition, dropping it will change the
		 * default partition's partition constraint, so we must lock it.
		 */
		defaultPartOid = get_default_partition_oid(parentOid);
		if (OidIsValid(defaultPartOid) && relid != defaultPartOid)
			LockRelationOid(defaultPartOid, AccessExclusiveLock);
	}

	ReleaseSysCache(tuple);

	/*
	 * Open and lock the relation.
	 */
	rel = relation_open(relid, AccessExclusiveLock);

	/*
	 * There can no longer be anyone *else* touching the relation, but we
	 * might still have open queries or cursors, or pending trigger events, in
	 * our own session.
	 */
	CheckTableNotInUse(rel, "DROP TABLE");

	/*
	 * This effectively deletes all rows in the table, and may be done in a
	 * serializable transaction.  In that case we must record a rw-conflict in
	 * to this transaction from each transaction holding a predicate lock on
	 * the table.
	 */
	CheckTableForSerializableConflictIn(rel);

	/*
	 * Delete pg_foreign_table tuple first.
	 */
	if (rel->rd_rel->relkind == RELKIND_FOREIGN_TABLE)
	{
		Relation	rel;
		HeapTuple	tuple;

		rel = table_open(ForeignTableRelationId, RowExclusiveLock);

		tuple = SearchSysCache1(FOREIGNTABLEREL, ObjectIdGetDatum(relid));
		if (!HeapTupleIsValid(tuple))
			elog(ERROR, "cache lookup failed for foreign table %u", relid);

		CatalogTupleDelete(rel, &tuple->t_self);

		ReleaseSysCache(tuple);
		table_close(rel, RowExclusiveLock);
	}

	/*
	 * If a partitioned table, delete the pg_partitioned_table tuple.
	 */
	if (rel->rd_rel->relkind == RELKIND_PARTITIONED_TABLE)
		RemovePartitionKeyByRelId(relid);

	/*
	 * If the relation being dropped is the default partition itself,
	 * invalidate its entry in pg_partitioned_table.
	 */
	if (relid == defaultPartOid)
		update_default_partition_oid(parentOid, InvalidOid);

	/*
	 * Schedule unlinking of the relation's physical files at commit.
	 */
	if (rel->rd_rel->relkind != RELKIND_VIEW &&
		rel->rd_rel->relkind != RELKIND_COMPOSITE_TYPE &&
		rel->rd_rel->relkind != RELKIND_FOREIGN_TABLE &&
		rel->rd_rel->relkind != RELKIND_PARTITIONED_TABLE)
	{
		RelationDropStorage(rel);
	}

	/*
	 * Close relcache entry, but *keep* AccessExclusiveLock on the relation
	 * until transaction commit.  This ensures no one else will try to do
	 * something with the doomed relation.
	 */
	relation_close(rel, NoLock);

	/*
	 * Remove any associated relation synchronization states.
	 */
	RemoveSubscriptionRel(InvalidOid, relid);

	/*
	 * Forget any ON COMMIT action for the rel
	 */
	remove_on_commit_action(relid);

	/*
	 * Flush the relation from the relcache.  We want to do this before
	 * starting to remove catalog entries, just to be certain that no relcache
	 * entry rebuild will happen partway through.  (That should not really
	 * matter, since we don't do CommandCounterIncrement here, but let's be
	 * safe.)
	 */
	RelationForgetRelation(relid);

	/*
	 * remove inheritance information
	 */
	RelationRemoveInheritance(relid);

	/*
	 * delete statistics
	 */
	RemoveStatistics(relid, 0);

	/*
	 * delete attribute tuples
	 */
	DeleteAttributeTuples(relid);

	/*
	 * delete relation tuple
	 */
	DeleteRelationTuple(relid);

	if (OidIsValid(parentOid))
	{
		/*
		 * If this is not the default partition, the partition constraint of
		 * the default partition has changed to include the portion of the key
		 * space previously covered by the dropped partition.
		 */
		if (OidIsValid(defaultPartOid) && relid != defaultPartOid)
			CacheInvalidateRelcacheByRelid(defaultPartOid);

		/*
		 * Invalidate the parent's relcache so that the partition is no longer
		 * included in its partition descriptor.
		 */
		CacheInvalidateRelcacheByRelid(parentOid);
		/* keep the lock */
	}
}