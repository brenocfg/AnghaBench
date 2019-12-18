#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ coninhcount; scalar_t__ conparentid; int conislocal; } ;
struct TYPE_10__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_constraint ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CONSTROID ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ConstraintRelationId ; 
 int /*<<< orphan*/  DEPENDENCY_PARTITION_PRI ; 
 int /*<<< orphan*/  DEPENDENCY_PARTITION_SEC ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_1__*) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  ObjectAddressSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 scalar_t__ OidIsValid (scalar_t__) ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  ReleaseSysCache (TYPE_1__*) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_1__* SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deleteDependencyRecordsForClass (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 TYPE_1__* heap_copytuple (TYPE_1__*) ; 
 int /*<<< orphan*/  recordDependencyOn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ConstraintSetParentConstraint(Oid childConstrId,
							  Oid parentConstrId,
							  Oid childTableId)
{
	Relation	constrRel;
	Form_pg_constraint constrForm;
	HeapTuple	tuple,
				newtup;
	ObjectAddress depender;
	ObjectAddress referenced;

	constrRel = table_open(ConstraintRelationId, RowExclusiveLock);
	tuple = SearchSysCache1(CONSTROID, ObjectIdGetDatum(childConstrId));
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "cache lookup failed for constraint %u", childConstrId);
	newtup = heap_copytuple(tuple);
	constrForm = (Form_pg_constraint) GETSTRUCT(newtup);
	if (OidIsValid(parentConstrId))
	{
		/* don't allow setting parent for a constraint that already has one */
		Assert(constrForm->coninhcount == 0);
		if (constrForm->conparentid != InvalidOid)
			elog(ERROR, "constraint %u already has a parent constraint",
				 childConstrId);

		constrForm->conislocal = false;
		constrForm->coninhcount++;
		constrForm->conparentid = parentConstrId;

		CatalogTupleUpdate(constrRel, &tuple->t_self, newtup);

		ObjectAddressSet(depender, ConstraintRelationId, childConstrId);

		ObjectAddressSet(referenced, ConstraintRelationId, parentConstrId);
		recordDependencyOn(&depender, &referenced, DEPENDENCY_PARTITION_PRI);

		ObjectAddressSet(referenced, RelationRelationId, childTableId);
		recordDependencyOn(&depender, &referenced, DEPENDENCY_PARTITION_SEC);
	}
	else
	{
		constrForm->coninhcount--;
		constrForm->conislocal = true;
		constrForm->conparentid = InvalidOid;

		/* Make sure there's no further inheritance. */
		Assert(constrForm->coninhcount == 0);

		CatalogTupleUpdate(constrRel, &tuple->t_self, newtup);

		deleteDependencyRecordsForClass(ConstraintRelationId, childConstrId,
										ConstraintRelationId,
										DEPENDENCY_PARTITION_PRI);
		deleteDependencyRecordsForClass(ConstraintRelationId, childConstrId,
										RelationRelationId,
										DEPENDENCY_PARTITION_SEC);
	}

	ReleaseSysCache(tuple);
	table_close(constrRel, RowExclusiveLock);
}