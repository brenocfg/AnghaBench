#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {void* indexrelid; scalar_t__ indisreplident; scalar_t__ indisprimary; int /*<<< orphan*/  indimmediate; int /*<<< orphan*/  indisunique; int /*<<< orphan*/  indisvalid; int /*<<< orphan*/  indislive; } ;
struct TYPE_10__ {int rd_indexvalid; void* rd_replidindex; void* rd_pkindex; int /*<<< orphan*/ * rd_indexlist; TYPE_1__* rd_rel; } ;
struct TYPE_9__ {char relreplident; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  TYPE_2__* Relation ;
typedef  void* Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__* Form_pg_index ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_index_indpred ; 
 int /*<<< orphan*/  Anum_pg_index_indrelid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CacheMemoryContext ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IndexIndrelidIndexId ; 
 int /*<<< orphan*/  IndexRelationId ; 
 void* InvalidOid ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (void*) ; 
 char REPLICA_IDENTITY_DEFAULT ; 
 char REPLICA_IDENTITY_INDEX ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_2__*) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_attisnull (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lappend_oid (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/ * list_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_oid_cmp ; 
 int /*<<< orphan*/  list_sort (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

List *
RelationGetIndexList(Relation relation)
{
	Relation	indrel;
	SysScanDesc indscan;
	ScanKeyData skey;
	HeapTuple	htup;
	List	   *result;
	List	   *oldlist;
	char		replident = relation->rd_rel->relreplident;
	Oid			pkeyIndex = InvalidOid;
	Oid			candidateIndex = InvalidOid;
	MemoryContext oldcxt;

	/* Quick exit if we already computed the list. */
	if (relation->rd_indexvalid)
		return list_copy(relation->rd_indexlist);

	/*
	 * We build the list we intend to return (in the caller's context) while
	 * doing the scan.  After successfully completing the scan, we copy that
	 * list into the relcache entry.  This avoids cache-context memory leakage
	 * if we get some sort of error partway through.
	 */
	result = NIL;

	/* Prepare to scan pg_index for entries having indrelid = this rel. */
	ScanKeyInit(&skey,
				Anum_pg_index_indrelid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(RelationGetRelid(relation)));

	indrel = table_open(IndexRelationId, AccessShareLock);
	indscan = systable_beginscan(indrel, IndexIndrelidIndexId, true,
								 NULL, 1, &skey);

	while (HeapTupleIsValid(htup = systable_getnext(indscan)))
	{
		Form_pg_index index = (Form_pg_index) GETSTRUCT(htup);

		/*
		 * Ignore any indexes that are currently being dropped.  This will
		 * prevent them from being searched, inserted into, or considered in
		 * HOT-safety decisions.  It's unsafe to touch such an index at all
		 * since its catalog entries could disappear at any instant.
		 */
		if (!index->indislive)
			continue;

		/* add index's OID to result list */
		result = lappend_oid(result, index->indexrelid);

		/*
		 * Invalid, non-unique, non-immediate or predicate indexes aren't
		 * interesting for either oid indexes or replication identity indexes,
		 * so don't check them.
		 */
		if (!index->indisvalid || !index->indisunique ||
			!index->indimmediate ||
			!heap_attisnull(htup, Anum_pg_index_indpred, NULL))
			continue;

		/* remember primary key index if any */
		if (index->indisprimary)
			pkeyIndex = index->indexrelid;

		/* remember explicitly chosen replica index */
		if (index->indisreplident)
			candidateIndex = index->indexrelid;
	}

	systable_endscan(indscan);

	table_close(indrel, AccessShareLock);

	/* Sort the result list into OID order, per API spec. */
	list_sort(result, list_oid_cmp);

	/* Now save a copy of the completed list in the relcache entry. */
	oldcxt = MemoryContextSwitchTo(CacheMemoryContext);
	oldlist = relation->rd_indexlist;
	relation->rd_indexlist = list_copy(result);
	relation->rd_pkindex = pkeyIndex;
	if (replident == REPLICA_IDENTITY_DEFAULT && OidIsValid(pkeyIndex))
		relation->rd_replidindex = pkeyIndex;
	else if (replident == REPLICA_IDENTITY_INDEX && OidIsValid(candidateIndex))
		relation->rd_replidindex = candidateIndex;
	else
		relation->rd_replidindex = InvalidOid;
	relation->rd_indexvalid = true;
	MemoryContextSwitchTo(oldcxt);

	/* Don't leak the old list, if there is one */
	list_free(oldlist);

	return result;
}