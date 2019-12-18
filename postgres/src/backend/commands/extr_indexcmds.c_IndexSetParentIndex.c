#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isnull ;
struct TYPE_23__ {scalar_t__ inhparent; int /*<<< orphan*/  inhrelid; } ;
struct TYPE_22__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_21__ {TYPE_2__* rd_index; TYPE_1__* rd_rel; } ;
struct TYPE_20__ {scalar_t__ indrelid; } ;
struct TYPE_19__ {scalar_t__ relkind; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  TYPE_3__* Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  TYPE_4__* HeapTuple ;
typedef  TYPE_5__* Form_pg_inherits ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int Anum_pg_inherits_inhparent ; 
 int Anum_pg_inherits_inhrelid ; 
 int Anum_pg_inherits_inhseqno ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CatalogTupleDelete (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CatalogTupleInsert (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  DEPENDENCY_PARTITION_PRI ; 
 int /*<<< orphan*/  DEPENDENCY_PARTITION_SEC ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  GETSTRUCT (TYPE_4__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_4__*) ; 
 int /*<<< orphan*/  InheritsRelationId ; 
 int /*<<< orphan*/  InheritsRelidSeqnoIndexId ; 
 int /*<<< orphan*/  Int32GetDatum (int) ; 
 scalar_t__ InvalidOid ; 
 int Natts_pg_inherits ; 
 int /*<<< orphan*/  ObjectAddressSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 scalar_t__ OidIsValid (scalar_t__) ; 
 scalar_t__ RELKIND_INDEX ; 
 scalar_t__ RELKIND_PARTITIONED_INDEX ; 
 int /*<<< orphan*/  RelationGetDescr (TYPE_3__*) ; 
 scalar_t__ RelationGetRelid (TYPE_3__*) ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetRelationHasSubclass (scalar_t__,int) ; 
 int /*<<< orphan*/  deleteDependencyRecordsForClass (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_4__* heap_form_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  recordDependencyOn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_close (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 TYPE_4__* systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_relispartition (scalar_t__,scalar_t__) ; 

void
IndexSetParentIndex(Relation partitionIdx, Oid parentOid)
{
	Relation	pg_inherits;
	ScanKeyData key[2];
	SysScanDesc scan;
	Oid			partRelid = RelationGetRelid(partitionIdx);
	HeapTuple	tuple;
	bool		fix_dependencies;

	/* Make sure this is an index */
	Assert(partitionIdx->rd_rel->relkind == RELKIND_INDEX ||
		   partitionIdx->rd_rel->relkind == RELKIND_PARTITIONED_INDEX);

	/*
	 * Scan pg_inherits for rows linking our index to some parent.
	 */
	pg_inherits = relation_open(InheritsRelationId, RowExclusiveLock);
	ScanKeyInit(&key[0],
				Anum_pg_inherits_inhrelid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(partRelid));
	ScanKeyInit(&key[1],
				Anum_pg_inherits_inhseqno,
				BTEqualStrategyNumber, F_INT4EQ,
				Int32GetDatum(1));
	scan = systable_beginscan(pg_inherits, InheritsRelidSeqnoIndexId, true,
							  NULL, 2, key);
	tuple = systable_getnext(scan);

	if (!HeapTupleIsValid(tuple))
	{
		if (parentOid == InvalidOid)
		{
			/*
			 * No pg_inherits row, and no parent wanted: nothing to do in this
			 * case.
			 */
			fix_dependencies = false;
		}
		else
		{
			Datum		values[Natts_pg_inherits];
			bool		isnull[Natts_pg_inherits];

			/*
			 * No pg_inherits row exists, and we want a parent for this index,
			 * so insert it.
			 */
			values[Anum_pg_inherits_inhrelid - 1] = ObjectIdGetDatum(partRelid);
			values[Anum_pg_inherits_inhparent - 1] =
				ObjectIdGetDatum(parentOid);
			values[Anum_pg_inherits_inhseqno - 1] = Int32GetDatum(1);
			memset(isnull, false, sizeof(isnull));

			tuple = heap_form_tuple(RelationGetDescr(pg_inherits),
									values, isnull);
			CatalogTupleInsert(pg_inherits, tuple);

			fix_dependencies = true;
		}
	}
	else
	{
		Form_pg_inherits inhForm = (Form_pg_inherits) GETSTRUCT(tuple);

		if (parentOid == InvalidOid)
		{
			/*
			 * There exists a pg_inherits row, which we want to clear; do so.
			 */
			CatalogTupleDelete(pg_inherits, &tuple->t_self);
			fix_dependencies = true;
		}
		else
		{
			/*
			 * A pg_inherits row exists.  If it's the same we want, then we're
			 * good; if it differs, that amounts to a corrupt catalog and
			 * should not happen.
			 */
			if (inhForm->inhparent != parentOid)
			{
				/* unexpected: we should not get called in this case */
				elog(ERROR, "bogus pg_inherit row: inhrelid %u inhparent %u",
					 inhForm->inhrelid, inhForm->inhparent);
			}

			/* already in the right state */
			fix_dependencies = false;
		}
	}

	/* done with pg_inherits */
	systable_endscan(scan);
	relation_close(pg_inherits, RowExclusiveLock);

	/* set relhassubclass if an index partition has been added to the parent */
	if (OidIsValid(parentOid))
		SetRelationHasSubclass(parentOid, true);

	/* set relispartition correctly on the partition */
	update_relispartition(partRelid, OidIsValid(parentOid));

	if (fix_dependencies)
	{
		/*
		 * Insert/delete pg_depend rows.  If setting a parent, add PARTITION
		 * dependencies on the parent index and the table; if removing a
		 * parent, delete PARTITION dependencies.
		 */
		if (OidIsValid(parentOid))
		{
			ObjectAddress partIdx;
			ObjectAddress parentIdx;
			ObjectAddress partitionTbl;

			ObjectAddressSet(partIdx, RelationRelationId, partRelid);
			ObjectAddressSet(parentIdx, RelationRelationId, parentOid);
			ObjectAddressSet(partitionTbl, RelationRelationId,
							 partitionIdx->rd_index->indrelid);
			recordDependencyOn(&partIdx, &parentIdx,
							   DEPENDENCY_PARTITION_PRI);
			recordDependencyOn(&partIdx, &partitionTbl,
							   DEPENDENCY_PARTITION_SEC);
		}
		else
		{
			deleteDependencyRecordsForClass(RelationRelationId, partRelid,
											RelationRelationId,
											DEPENDENCY_PARTITION_PRI);
			deleteDependencyRecordsForClass(RelationRelationId, partRelid,
											RelationRelationId,
											DEPENDENCY_PARTITION_SEC);
		}

		/* make our updates visible */
		CommandCounterIncrement();
	}
}