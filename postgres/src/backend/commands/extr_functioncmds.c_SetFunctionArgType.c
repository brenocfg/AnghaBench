#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__* values; } ;
struct TYPE_10__ {int pronargs; TYPE_1__ proargtypes; } ;
struct TYPE_9__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  TYPE_2__* HeapTuple ;
typedef  TYPE_3__* Form_pg_proc ;

/* Variables and functions */
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  DEPENDENCY_NORMAL ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_2__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_2__*) ; 
 scalar_t__ OPAQUEOID ; 
 int /*<<< orphan*/  ObjectAddressSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  PROCOID ; 
 int /*<<< orphan*/  ProcedureRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_2__* SearchSysCacheCopy1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TypeRelationId ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  recordDependencyOn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
SetFunctionArgType(Oid funcOid, int argIndex, Oid newArgType)
{
	Relation	pg_proc_rel;
	HeapTuple	tup;
	Form_pg_proc procForm;
	ObjectAddress func_address;
	ObjectAddress type_address;

	pg_proc_rel = table_open(ProcedureRelationId, RowExclusiveLock);

	tup = SearchSysCacheCopy1(PROCOID, ObjectIdGetDatum(funcOid));
	if (!HeapTupleIsValid(tup)) /* should not happen */
		elog(ERROR, "cache lookup failed for function %u", funcOid);
	procForm = (Form_pg_proc) GETSTRUCT(tup);

	if (argIndex < 0 || argIndex >= procForm->pronargs ||
		procForm->proargtypes.values[argIndex] != OPAQUEOID)
		elog(ERROR, "function %u doesn't take OPAQUE", funcOid);

	/* okay to overwrite copied tuple */
	procForm->proargtypes.values[argIndex] = newArgType;

	/* update the catalog and its indexes */
	CatalogTupleUpdate(pg_proc_rel, &tup->t_self, tup);

	table_close(pg_proc_rel, RowExclusiveLock);

	/*
	 * Also update the dependency to the new type. Opaque is a pinned type, so
	 * there is no old dependency record for it that we would need to remove.
	 */
	ObjectAddressSet(type_address, TypeRelationId, newArgType);
	ObjectAddressSet(func_address, ProcedureRelationId, funcOid);
	recordDependencyOn(&func_address, &type_address, DEPENDENCY_NORMAL);
}