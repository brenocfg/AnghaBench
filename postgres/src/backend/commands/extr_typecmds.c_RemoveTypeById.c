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
struct TYPE_8__ {scalar_t__ typtype; } ;
struct TYPE_7__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_type ;

/* Variables and functions */
 int /*<<< orphan*/  CatalogTupleDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EnumValuesDelete (int /*<<< orphan*/ ) ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RangeDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (TYPE_1__*) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_1__* SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPEOID ; 
 scalar_t__ TYPTYPE_ENUM ; 
 scalar_t__ TYPTYPE_RANGE ; 
 int /*<<< orphan*/  TypeRelationId ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
RemoveTypeById(Oid typeOid)
{
	Relation	relation;
	HeapTuple	tup;

	relation = table_open(TypeRelationId, RowExclusiveLock);

	tup = SearchSysCache1(TYPEOID, ObjectIdGetDatum(typeOid));
	if (!HeapTupleIsValid(tup))
		elog(ERROR, "cache lookup failed for type %u", typeOid);

	CatalogTupleDelete(relation, &tup->t_self);

	/*
	 * If it is an enum, delete the pg_enum entries too; we don't bother with
	 * making dependency entries for those, so it has to be done "by hand"
	 * here.
	 */
	if (((Form_pg_type) GETSTRUCT(tup))->typtype == TYPTYPE_ENUM)
		EnumValuesDelete(typeOid);

	/*
	 * If it is a range type, delete the pg_range entry too; we don't bother
	 * with making a dependency entry for that, so it has to be done "by hand"
	 * here.
	 */
	if (((Form_pg_type) GETSTRUCT(tup))->typtype == TYPTYPE_RANGE)
		RangeDelete(typeOid);

	ReleaseSysCache(tup);

	table_close(relation, RowExclusiveLock);
}