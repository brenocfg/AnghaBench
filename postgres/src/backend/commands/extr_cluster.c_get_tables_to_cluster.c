#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TableScanDesc ;
struct TYPE_5__ {int /*<<< orphan*/  indexrelid; int /*<<< orphan*/  indrelid; } ;
struct TYPE_4__ {int /*<<< orphan*/  indexOid; int /*<<< orphan*/  tableOid; } ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ RelToCluster ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_2__* Form_pg_index ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_index_indisclustered ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  BoolGetDatum (int) ; 
 int /*<<< orphan*/  F_BOOLEQ ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  IndexRelationId ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_getnext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pg_class_ownercheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_beginscan_catalog (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static List *
get_tables_to_cluster(MemoryContext cluster_context)
{
	Relation	indRelation;
	TableScanDesc scan;
	ScanKeyData entry;
	HeapTuple	indexTuple;
	Form_pg_index index;
	MemoryContext old_context;
	RelToCluster *rvtc;
	List	   *rvs = NIL;

	/*
	 * Get all indexes that have indisclustered set and are owned by
	 * appropriate user. System relations or nailed-in relations cannot ever
	 * have indisclustered set, because CLUSTER will refuse to set it when
	 * called with one of them as argument.
	 */
	indRelation = table_open(IndexRelationId, AccessShareLock);
	ScanKeyInit(&entry,
				Anum_pg_index_indisclustered,
				BTEqualStrategyNumber, F_BOOLEQ,
				BoolGetDatum(true));
	scan = table_beginscan_catalog(indRelation, 1, &entry);
	while ((indexTuple = heap_getnext(scan, ForwardScanDirection)) != NULL)
	{
		index = (Form_pg_index) GETSTRUCT(indexTuple);

		if (!pg_class_ownercheck(index->indrelid, GetUserId()))
			continue;

		/*
		 * We have to build the list in a different memory context so it will
		 * survive the cross-transaction processing
		 */
		old_context = MemoryContextSwitchTo(cluster_context);

		rvtc = (RelToCluster *) palloc(sizeof(RelToCluster));
		rvtc->tableOid = index->indrelid;
		rvtc->indexOid = index->indexrelid;
		rvs = lappend(rvs, rvtc);

		MemoryContextSwitchTo(old_context);
	}
	table_endscan(scan);

	relation_close(indRelation, AccessShareLock);

	return rvs;
}