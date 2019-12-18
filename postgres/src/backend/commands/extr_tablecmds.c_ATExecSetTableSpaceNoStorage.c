#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ reltablespace; } ;
struct TYPE_17__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_16__ {TYPE_1__* rd_rel; } ;
struct TYPE_15__ {scalar_t__ reltablespace; int /*<<< orphan*/  relkind; } ;
typedef  TYPE_2__* Relation ;
typedef  scalar_t__ Oid ;
typedef  TYPE_3__* HeapTuple ;
typedef  TYPE_4__* Form_pg_class ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (TYPE_2__*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_3__*) ; 
 scalar_t__ GLOBALTABLESPACE_OID ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_3__*) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ MyDatabaseTableSpace ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  RELKIND_HAS_STORAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELOID ; 
 scalar_t__ RelationGetRelid (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_3__* SearchSysCacheCopy1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_3__*) ; 
 int /*<<< orphan*/  table_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ATExecSetTableSpaceNoStorage(Relation rel, Oid newTableSpace)
{
	HeapTuple	tuple;
	Oid			oldTableSpace;
	Relation	pg_class;
	Form_pg_class rd_rel;
	Oid			reloid = RelationGetRelid(rel);

	/*
	 * Shouldn't be called on relations having storage; these are processed in
	 * phase 3.
	 */
	Assert(!RELKIND_HAS_STORAGE(rel->rd_rel->relkind));

	/* Can't allow a non-shared relation in pg_global */
	if (newTableSpace == GLOBALTABLESPACE_OID)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("only shared relations can be placed in pg_global tablespace")));

	/*
	 * No work if no change in tablespace.
	 */
	oldTableSpace = rel->rd_rel->reltablespace;
	if (newTableSpace == oldTableSpace ||
		(newTableSpace == MyDatabaseTableSpace && oldTableSpace == 0))
	{
		InvokeObjectPostAlterHook(RelationRelationId, reloid, 0);
		return;
	}

	/* Get a modifiable copy of the relation's pg_class row */
	pg_class = table_open(RelationRelationId, RowExclusiveLock);

	tuple = SearchSysCacheCopy1(RELOID, ObjectIdGetDatum(reloid));
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "cache lookup failed for relation %u", reloid);
	rd_rel = (Form_pg_class) GETSTRUCT(tuple);

	/* update the pg_class row */
	rd_rel->reltablespace = (newTableSpace == MyDatabaseTableSpace) ? InvalidOid : newTableSpace;
	CatalogTupleUpdate(pg_class, &tuple->t_self, tuple);

	InvokeObjectPostAlterHook(RelationRelationId, reloid, 0);

	heap_freetuple(tuple);

	table_close(pg_class, RowExclusiveLock);

	/* Make sure the reltablespace change is visible */
	CommandCounterIncrement();
}