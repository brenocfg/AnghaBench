#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char prokind; } ;
struct TYPE_7__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_proc ;

/* Variables and functions */
 int /*<<< orphan*/  AGGFNOID ; 
 int /*<<< orphan*/  AggregateRelationId ; 
 int /*<<< orphan*/  CatalogTupleDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCOID ; 
 char PROKIND_AGGREGATE ; 
 int /*<<< orphan*/  ProcedureRelationId ; 
 int /*<<< orphan*/  ReleaseSysCache (TYPE_1__*) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_1__* SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
RemoveFunctionById(Oid funcOid)
{
	Relation	relation;
	HeapTuple	tup;
	char		prokind;

	/*
	 * Delete the pg_proc tuple.
	 */
	relation = table_open(ProcedureRelationId, RowExclusiveLock);

	tup = SearchSysCache1(PROCOID, ObjectIdGetDatum(funcOid));
	if (!HeapTupleIsValid(tup)) /* should not happen */
		elog(ERROR, "cache lookup failed for function %u", funcOid);

	prokind = ((Form_pg_proc) GETSTRUCT(tup))->prokind;

	CatalogTupleDelete(relation, &tup->t_self);

	ReleaseSysCache(tup);

	table_close(relation, RowExclusiveLock);

	/*
	 * If there's a pg_aggregate tuple, delete that too.
	 */
	if (prokind == PROKIND_AGGREGATE)
	{
		relation = table_open(AggregateRelationId, RowExclusiveLock);

		tup = SearchSysCache1(AGGFNOID, ObjectIdGetDatum(funcOid));
		if (!HeapTupleIsValid(tup)) /* should not happen */
			elog(ERROR, "cache lookup failed for pg_aggregate tuple for function %u", funcOid);

		CatalogTupleDelete(relation, &tup->t_self);

		ReleaseSysCache(tup);

		table_close(relation, RowExclusiveLock);
	}
}