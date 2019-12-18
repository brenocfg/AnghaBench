#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ connamespace; int /*<<< orphan*/  oid; } ;
struct TYPE_13__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_12__ {int /*<<< orphan*/  objectId; scalar_t__ objectSubId; int /*<<< orphan*/  classId; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  ObjectAddresses ;
typedef  TYPE_1__ ObjectAddress ;
typedef  TYPE_2__* HeapTuple ;
typedef  TYPE_3__* Form_pg_constraint ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_constraint_conrelid ; 
 int /*<<< orphan*/  Anum_pg_constraint_contypid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ConstraintRelationId ; 
 int /*<<< orphan*/  ConstraintRelidTypidNameIndexId ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ GETSTRUCT (TYPE_2__*) ; 
 scalar_t__ HeapTupleIsValid (TYPE_2__*) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_exact_object_address (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* heap_copytuple (TYPE_2__*) ; 
 scalar_t__ object_address_present (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 TYPE_2__* systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
AlterConstraintNamespaces(Oid ownerId, Oid oldNspId,
						  Oid newNspId, bool isType, ObjectAddresses *objsMoved)
{
	Relation	conRel;
	ScanKeyData key[2];
	SysScanDesc scan;
	HeapTuple	tup;

	conRel = table_open(ConstraintRelationId, RowExclusiveLock);

	ScanKeyInit(&key[0],
				Anum_pg_constraint_conrelid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(isType ? InvalidOid : ownerId));
	ScanKeyInit(&key[1],
				Anum_pg_constraint_contypid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(isType ? ownerId : InvalidOid));

	scan = systable_beginscan(conRel, ConstraintRelidTypidNameIndexId, true,
							  NULL, 2, key);

	while (HeapTupleIsValid((tup = systable_getnext(scan))))
	{
		Form_pg_constraint conform = (Form_pg_constraint) GETSTRUCT(tup);
		ObjectAddress thisobj;

		thisobj.classId = ConstraintRelationId;
		thisobj.objectId = conform->oid;
		thisobj.objectSubId = 0;

		if (object_address_present(&thisobj, objsMoved))
			continue;

		/* Don't update if the object is already part of the namespace */
		if (conform->connamespace == oldNspId && oldNspId != newNspId)
		{
			tup = heap_copytuple(tup);
			conform = (Form_pg_constraint) GETSTRUCT(tup);

			conform->connamespace = newNspId;

			CatalogTupleUpdate(conRel, &tup->t_self, tup);

			/*
			 * Note: currently, the constraint will not have its own
			 * dependency on the namespace, so we don't need to do
			 * changeDependencyFor().
			 */
		}

		InvokeObjectPostAlterHook(ConstraintRelationId, thisobj.objectId, 0);

		add_exact_object_address(&thisobj, objsMoved);
	}

	systable_endscan(scan);

	table_close(conRel, RowExclusiveLock);
}