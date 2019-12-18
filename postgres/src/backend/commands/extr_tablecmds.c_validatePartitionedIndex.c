#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_15__ ;
typedef  struct TYPE_18__   TYPE_13__ ;

/* Type definitions */
struct TYPE_24__ {int indisvalid; } ;
struct TYPE_23__ {int /*<<< orphan*/  inhrelid; } ;
struct TYPE_22__ {TYPE_2__* rd_index; TYPE_1__* rd_rel; TYPE_13__* rd_indextuple; } ;
struct TYPE_21__ {int /*<<< orphan*/  indisvalid; } ;
struct TYPE_20__ {scalar_t__ relkind; scalar_t__ relispartition; } ;
struct TYPE_19__ {int nparts; } ;
struct TYPE_18__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  TYPE_3__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_4__* Form_pg_inherits ;
typedef  TYPE_5__* Form_pg_index ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_inherits_inhparent ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CatalogTupleUpdate (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INDEXRELID ; 
 int /*<<< orphan*/  IndexRelationId ; 
 int /*<<< orphan*/  InheritsParentIndexId ; 
 int /*<<< orphan*/  InheritsRelationId ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ RELKIND_PARTITIONED_INDEX ; 
 TYPE_15__* RelationGetPartitionDesc (TYPE_3__*) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_3__*) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_partition_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_copytuple (TYPE_13__*) ; 
 int /*<<< orphan*/  relation_close (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
validatePartitionedIndex(Relation partedIdx, Relation partedTbl)
{
	Relation	inheritsRel;
	SysScanDesc scan;
	ScanKeyData key;
	int			tuples = 0;
	HeapTuple	inhTup;
	bool		updated = false;

	Assert(partedIdx->rd_rel->relkind == RELKIND_PARTITIONED_INDEX);

	/*
	 * Scan pg_inherits for this parent index.  Count each valid index we find
	 * (verifying the pg_index entry for each), and if we reach the total
	 * amount we expect, we can mark this parent index as valid.
	 */
	inheritsRel = table_open(InheritsRelationId, AccessShareLock);
	ScanKeyInit(&key, Anum_pg_inherits_inhparent,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(RelationGetRelid(partedIdx)));
	scan = systable_beginscan(inheritsRel, InheritsParentIndexId, true,
							  NULL, 1, &key);
	while ((inhTup = systable_getnext(scan)) != NULL)
	{
		Form_pg_inherits inhForm = (Form_pg_inherits) GETSTRUCT(inhTup);
		HeapTuple	indTup;
		Form_pg_index indexForm;

		indTup = SearchSysCache1(INDEXRELID,
								 ObjectIdGetDatum(inhForm->inhrelid));
		if (!HeapTupleIsValid(indTup))
			elog(ERROR, "cache lookup failed for index %u", inhForm->inhrelid);
		indexForm = (Form_pg_index) GETSTRUCT(indTup);
		if (indexForm->indisvalid)
			tuples += 1;
		ReleaseSysCache(indTup);
	}

	/* Done with pg_inherits */
	systable_endscan(scan);
	table_close(inheritsRel, AccessShareLock);

	/*
	 * If we found as many inherited indexes as the partitioned table has
	 * partitions, we're good; update pg_index to set indisvalid.
	 */
	if (tuples == RelationGetPartitionDesc(partedTbl)->nparts)
	{
		Relation	idxRel;
		HeapTuple	newtup;

		idxRel = table_open(IndexRelationId, RowExclusiveLock);

		newtup = heap_copytuple(partedIdx->rd_indextuple);
		((Form_pg_index) GETSTRUCT(newtup))->indisvalid = true;
		updated = true;

		CatalogTupleUpdate(idxRel, &partedIdx->rd_indextuple->t_self, newtup);

		table_close(idxRel, RowExclusiveLock);
	}

	/*
	 * If this index is in turn a partition of a larger index, validating it
	 * might cause the parent to become valid also.  Try that.
	 */
	if (updated && partedIdx->rd_rel->relispartition)
	{
		Oid			parentIdxId,
					parentTblId;
		Relation	parentIdx,
					parentTbl;

		/* make sure we see the validation we just did */
		CommandCounterIncrement();

		parentIdxId = get_partition_parent(RelationGetRelid(partedIdx));
		parentTblId = get_partition_parent(RelationGetRelid(partedTbl));
		parentIdx = relation_open(parentIdxId, AccessExclusiveLock);
		parentTbl = relation_open(parentTblId, AccessExclusiveLock);
		Assert(!parentIdx->rd_index->indisvalid);

		validatePartitionedIndex(parentIdx, parentTbl);

		relation_close(parentIdx, AccessExclusiveLock);
		relation_close(parentTbl, AccessExclusiveLock);
	}
}