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
typedef  int /*<<< orphan*/  new_val ;
typedef  int /*<<< orphan*/  new_repl ;
typedef  int /*<<< orphan*/  new_null ;
struct TYPE_16__ {int relispartition; } ;
struct TYPE_15__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_14__ {scalar_t__ is_default; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ PartitionBoundSpec ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__* HeapTuple ;
typedef  TYPE_3__* Form_pg_class ;
typedef  int Datum ;

/* Variables and functions */
 int Anum_pg_class_relpartbound ; 
 int /*<<< orphan*/  Assert (int) ; 
 int CStringGetTextDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CacheInvalidateRelcache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CacheInvalidateRelcacheByRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_2__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_2__*) ; 
 int Natts_pg_class ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELOID ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetPartitionDesc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_2__* SearchSysCacheCopy1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,TYPE_2__*,int,int*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_default_oid_from_partdesc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_2__*) ; 
 TYPE_2__* heap_modify_tuple (TYPE_2__*,int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  nodeToString (TYPE_1__*) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_default_partition_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
StorePartitionBound(Relation rel, Relation parent, PartitionBoundSpec *bound)
{
	Relation	classRel;
	HeapTuple	tuple,
				newtuple;
	Datum		new_val[Natts_pg_class];
	bool		new_null[Natts_pg_class],
				new_repl[Natts_pg_class];
	Oid			defaultPartOid;

	/* Update pg_class tuple */
	classRel = table_open(RelationRelationId, RowExclusiveLock);
	tuple = SearchSysCacheCopy1(RELOID,
								ObjectIdGetDatum(RelationGetRelid(rel)));
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "cache lookup failed for relation %u",
			 RelationGetRelid(rel));

#ifdef USE_ASSERT_CHECKING
	{
		Form_pg_class classForm;
		bool		isnull;

		classForm = (Form_pg_class) GETSTRUCT(tuple);
		Assert(!classForm->relispartition);
		(void) SysCacheGetAttr(RELOID, tuple, Anum_pg_class_relpartbound,
							   &isnull);
		Assert(isnull);
	}
#endif

	/* Fill in relpartbound value */
	memset(new_val, 0, sizeof(new_val));
	memset(new_null, false, sizeof(new_null));
	memset(new_repl, false, sizeof(new_repl));
	new_val[Anum_pg_class_relpartbound - 1] = CStringGetTextDatum(nodeToString(bound));
	new_null[Anum_pg_class_relpartbound - 1] = false;
	new_repl[Anum_pg_class_relpartbound - 1] = true;
	newtuple = heap_modify_tuple(tuple, RelationGetDescr(classRel),
								 new_val, new_null, new_repl);
	/* Also set the flag */
	((Form_pg_class) GETSTRUCT(newtuple))->relispartition = true;
	CatalogTupleUpdate(classRel, &newtuple->t_self, newtuple);
	heap_freetuple(newtuple);
	table_close(classRel, RowExclusiveLock);

	/*
	 * If we're storing bounds for the default partition, update
	 * pg_partitioned_table too.
	 */
	if (bound->is_default)
		update_default_partition_oid(RelationGetRelid(parent),
									 RelationGetRelid(rel));

	/* Make these updates visible */
	CommandCounterIncrement();

	/*
	 * The partition constraint for the default partition depends on the
	 * partition bounds of every other partition, so we must invalidate the
	 * relcache entry for that partition every time a partition is added or
	 * removed.
	 */
	defaultPartOid = get_default_oid_from_partdesc(RelationGetPartitionDesc(parent));
	if (OidIsValid(defaultPartOid))
		CacheInvalidateRelcacheByRelid(defaultPartOid);

	CacheInvalidateRelcache(parent);
}