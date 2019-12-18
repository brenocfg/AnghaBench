#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  oidvector ;
typedef  int /*<<< orphan*/  nulls ;
typedef  int /*<<< orphan*/  int2vector ;
typedef  int int16 ;
struct TYPE_16__ {scalar_t__ objectSubId; void* objectId; void* classId; } ;
struct TYPE_15__ {TYPE_1__* rd_rel; } ;
struct TYPE_14__ {scalar_t__ relkind; } ;
typedef  TYPE_2__* Relation ;
typedef  scalar_t__ Oid ;
typedef  TYPE_3__ ObjectAddress ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  scalar_t__ Datum ;
typedef  scalar_t__ AttrNumber ;

/* Variables and functions */
 int Anum_pg_partitioned_table_partattrs ; 
 int Anum_pg_partitioned_table_partclass ; 
 int Anum_pg_partitioned_table_partcollation ; 
 int Anum_pg_partitioned_table_partdefid ; 
 int Anum_pg_partitioned_table_partexprs ; 
 int Anum_pg_partitioned_table_partnatts ; 
 int Anum_pg_partitioned_table_partrelid ; 
 int Anum_pg_partitioned_table_partstrat ; 
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CStringGetTextDatum (char*) ; 
 int /*<<< orphan*/  CacheInvalidateRelcache (TYPE_2__*) ; 
 int /*<<< orphan*/  CatalogTupleInsert (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ CharGetDatum (char) ; 
 void* CollationRelationId ; 
 scalar_t__ DEFAULT_COLLATION_OID ; 
 int /*<<< orphan*/  DEPENDENCY_INTERNAL ; 
 int /*<<< orphan*/  DEPENDENCY_NORMAL ; 
 scalar_t__ Int16GetDatum (int) ; 
 void* InvalidOid ; 
 int /*<<< orphan*/  MemSet (int*,int,int) ; 
 int Natts_pg_partitioned_table ; 
 scalar_t__ ObjectIdGetDatum (void*) ; 
 scalar_t__ OidIsValid (scalar_t__) ; 
 void* OperatorClassRelationId ; 
 int /*<<< orphan*/  PartitionedRelationId ; 
 scalar_t__ PointerGetDatum (int /*<<< orphan*/ *) ; 
 scalar_t__ RELKIND_PARTITIONED_TABLE ; 
 int /*<<< orphan*/  RelationGetDescr (TYPE_2__*) ; 
 void* RelationGetRelid (TYPE_2__*) ; 
 void* RelationRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/ * buildint2vector (scalar_t__*,int) ; 
 int /*<<< orphan*/ * buildoidvector (scalar_t__*,int) ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 char* nodeToString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  recordDependencyOn (TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recordDependencyOnSingleRelExpr (TYPE_3__*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  table_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
StorePartitionKey(Relation rel,
				  char strategy,
				  int16 partnatts,
				  AttrNumber *partattrs,
				  List *partexprs,
				  Oid *partopclass,
				  Oid *partcollation)
{
	int			i;
	int2vector *partattrs_vec;
	oidvector  *partopclass_vec;
	oidvector  *partcollation_vec;
	Datum		partexprDatum;
	Relation	pg_partitioned_table;
	HeapTuple	tuple;
	Datum		values[Natts_pg_partitioned_table];
	bool		nulls[Natts_pg_partitioned_table];
	ObjectAddress myself;
	ObjectAddress referenced;

	Assert(rel->rd_rel->relkind == RELKIND_PARTITIONED_TABLE);

	/* Copy the partition attribute numbers, opclass OIDs into arrays */
	partattrs_vec = buildint2vector(partattrs, partnatts);
	partopclass_vec = buildoidvector(partopclass, partnatts);
	partcollation_vec = buildoidvector(partcollation, partnatts);

	/* Convert the expressions (if any) to a text datum */
	if (partexprs)
	{
		char	   *exprString;

		exprString = nodeToString(partexprs);
		partexprDatum = CStringGetTextDatum(exprString);
		pfree(exprString);
	}
	else
		partexprDatum = (Datum) 0;

	pg_partitioned_table = table_open(PartitionedRelationId, RowExclusiveLock);

	MemSet(nulls, false, sizeof(nulls));

	/* Only this can ever be NULL */
	if (!partexprDatum)
		nulls[Anum_pg_partitioned_table_partexprs - 1] = true;

	values[Anum_pg_partitioned_table_partrelid - 1] = ObjectIdGetDatum(RelationGetRelid(rel));
	values[Anum_pg_partitioned_table_partstrat - 1] = CharGetDatum(strategy);
	values[Anum_pg_partitioned_table_partnatts - 1] = Int16GetDatum(partnatts);
	values[Anum_pg_partitioned_table_partdefid - 1] = ObjectIdGetDatum(InvalidOid);
	values[Anum_pg_partitioned_table_partattrs - 1] = PointerGetDatum(partattrs_vec);
	values[Anum_pg_partitioned_table_partclass - 1] = PointerGetDatum(partopclass_vec);
	values[Anum_pg_partitioned_table_partcollation - 1] = PointerGetDatum(partcollation_vec);
	values[Anum_pg_partitioned_table_partexprs - 1] = partexprDatum;

	tuple = heap_form_tuple(RelationGetDescr(pg_partitioned_table), values, nulls);

	CatalogTupleInsert(pg_partitioned_table, tuple);
	table_close(pg_partitioned_table, RowExclusiveLock);

	/* Mark this relation as dependent on a few things as follows */
	myself.classId = RelationRelationId;
	myself.objectId = RelationGetRelid(rel);
	myself.objectSubId = 0;

	/* Operator class and collation per key column */
	for (i = 0; i < partnatts; i++)
	{
		referenced.classId = OperatorClassRelationId;
		referenced.objectId = partopclass[i];
		referenced.objectSubId = 0;

		recordDependencyOn(&myself, &referenced, DEPENDENCY_NORMAL);

		/* The default collation is pinned, so don't bother recording it */
		if (OidIsValid(partcollation[i]) &&
			partcollation[i] != DEFAULT_COLLATION_OID)
		{
			referenced.classId = CollationRelationId;
			referenced.objectId = partcollation[i];
			referenced.objectSubId = 0;

			recordDependencyOn(&myself, &referenced, DEPENDENCY_NORMAL);
		}
	}

	/*
	 * The partitioning columns are made internally dependent on the table,
	 * because we cannot drop any of them without dropping the whole table.
	 * (ATExecDropColumn independently enforces that, but it's not bulletproof
	 * so we need the dependencies too.)
	 */
	for (i = 0; i < partnatts; i++)
	{
		if (partattrs[i] == 0)
			continue;			/* ignore expressions here */

		referenced.classId = RelationRelationId;
		referenced.objectId = RelationGetRelid(rel);
		referenced.objectSubId = partattrs[i];

		recordDependencyOn(&referenced, &myself, DEPENDENCY_INTERNAL);
	}

	/*
	 * Also consider anything mentioned in partition expressions.  External
	 * references (e.g. functions) get NORMAL dependencies.  Table columns
	 * mentioned in the expressions are handled the same as plain partitioning
	 * columns, i.e. they become internally dependent on the whole table.
	 */
	if (partexprs)
		recordDependencyOnSingleRelExpr(&myself,
										(Node *) partexprs,
										RelationGetRelid(rel),
										DEPENDENCY_NORMAL,
										DEPENDENCY_INTERNAL,
										true /* reverse the self-deps */ );

	/*
	 * We must invalidate the relcache so that the next
	 * CommandCounterIncrement() will cause the same to be rebuilt using the
	 * information in just created catalog entry.
	 */
	CacheInvalidateRelcache(rel);
}