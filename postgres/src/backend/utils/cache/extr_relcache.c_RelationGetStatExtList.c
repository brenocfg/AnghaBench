#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  oid; } ;
struct TYPE_8__ {int rd_statvalid; int /*<<< orphan*/ * rd_statlist; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  TYPE_1__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_statistic_ext ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_statistic_ext_stxrelid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CacheMemoryContext ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_1__*) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StatisticExtRelationId ; 
 int /*<<< orphan*/  StatisticExtRelidIndexId ; 
 int /*<<< orphan*/ * lappend_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_oid_cmp ; 
 int /*<<< orphan*/  list_sort (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

List *
RelationGetStatExtList(Relation relation)
{
	Relation	indrel;
	SysScanDesc indscan;
	ScanKeyData skey;
	HeapTuple	htup;
	List	   *result;
	List	   *oldlist;
	MemoryContext oldcxt;

	/* Quick exit if we already computed the list. */
	if (relation->rd_statvalid != 0)
		return list_copy(relation->rd_statlist);

	/*
	 * We build the list we intend to return (in the caller's context) while
	 * doing the scan.  After successfully completing the scan, we copy that
	 * list into the relcache entry.  This avoids cache-context memory leakage
	 * if we get some sort of error partway through.
	 */
	result = NIL;

	/*
	 * Prepare to scan pg_statistic_ext for entries having stxrelid = this
	 * rel.
	 */
	ScanKeyInit(&skey,
				Anum_pg_statistic_ext_stxrelid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(RelationGetRelid(relation)));

	indrel = table_open(StatisticExtRelationId, AccessShareLock);
	indscan = systable_beginscan(indrel, StatisticExtRelidIndexId, true,
								 NULL, 1, &skey);

	while (HeapTupleIsValid(htup = systable_getnext(indscan)))
	{
		Oid			oid = ((Form_pg_statistic_ext) GETSTRUCT(htup))->oid;

		result = lappend_oid(result, oid);
	}

	systable_endscan(indscan);

	table_close(indrel, AccessShareLock);

	/* Sort the result list into OID order, per API spec. */
	list_sort(result, list_oid_cmp);

	/* Now save a copy of the completed list in the relcache entry. */
	oldcxt = MemoryContextSwitchTo(CacheMemoryContext);
	oldlist = relation->rd_statlist;
	relation->rd_statlist = list_copy(result);

	relation->rd_statvalid = true;
	MemoryContextSwitchTo(oldcxt);

	/* Don't leak the old list, if there is one */
	list_free(oldlist);

	return result;
}