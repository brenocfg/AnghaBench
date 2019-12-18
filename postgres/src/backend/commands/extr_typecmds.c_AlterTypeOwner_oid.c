#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ typtype; int /*<<< orphan*/  typrelid; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_type ;

/* Variables and functions */
 int /*<<< orphan*/  ATExecChangeOwner (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  AlterTypeOwnerInternal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPEOID ; 
 scalar_t__ TYPTYPE_COMPOSITE ; 
 int /*<<< orphan*/  TypeRelationId ; 
 int /*<<< orphan*/  changeDependencyOnOwner (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
AlterTypeOwner_oid(Oid typeOid, Oid newOwnerId, bool hasDependEntry)
{
	Relation	rel;
	HeapTuple	tup;
	Form_pg_type typTup;

	rel = table_open(TypeRelationId, RowExclusiveLock);

	tup = SearchSysCache1(TYPEOID, ObjectIdGetDatum(typeOid));
	if (!HeapTupleIsValid(tup))
		elog(ERROR, "cache lookup failed for type %u", typeOid);
	typTup = (Form_pg_type) GETSTRUCT(tup);

	/*
	 * If it's a composite type, invoke ATExecChangeOwner so that we fix up
	 * the pg_class entry properly.  That will call back to
	 * AlterTypeOwnerInternal to take care of the pg_type entry(s).
	 */
	if (typTup->typtype == TYPTYPE_COMPOSITE)
		ATExecChangeOwner(typTup->typrelid, newOwnerId, true, AccessExclusiveLock);
	else
		AlterTypeOwnerInternal(typeOid, newOwnerId);

	/* Update owner dependency reference */
	if (hasDependEntry)
		changeDependencyOnOwner(TypeRelationId, typeOid, newOwnerId);

	InvokeObjectPostAlterHook(TypeRelationId, typeOid, 0);

	ReleaseSysCache(tup);
	table_close(rel, RowExclusiveLock);
}