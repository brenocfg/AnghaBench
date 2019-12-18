#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nulls ;
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_4__ {int /*<<< orphan*/  rd_att; } ;
typedef  int /*<<< orphan*/  SharedDependencyType ;
typedef  TYPE_1__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int Anum_pg_shdepend_classid ; 
 int Anum_pg_shdepend_dbid ; 
 int Anum_pg_shdepend_deptype ; 
 int Anum_pg_shdepend_objid ; 
 int Anum_pg_shdepend_objsubid ; 
 int Anum_pg_shdepend_refclassid ; 
 int Anum_pg_shdepend_refobjid ; 
 int /*<<< orphan*/  CatalogTupleInsert (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CharGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int Natts_pg_shdepend ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  classIdGetDbId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  shdepLockAndCheckObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
shdepAddDependency(Relation sdepRel,
				   Oid classId, Oid objectId, int32 objsubId,
				   Oid refclassId, Oid refobjId,
				   SharedDependencyType deptype)
{
	HeapTuple	tup;
	Datum		values[Natts_pg_shdepend];
	bool		nulls[Natts_pg_shdepend];

	/*
	 * Make sure the object doesn't go away while we record the dependency on
	 * it.  DROP routines should lock the object exclusively before they check
	 * shared dependencies.
	 */
	shdepLockAndCheckObject(refclassId, refobjId);

	memset(nulls, false, sizeof(nulls));

	/*
	 * Form the new tuple and record the dependency.
	 */
	values[Anum_pg_shdepend_dbid - 1] = ObjectIdGetDatum(classIdGetDbId(classId));
	values[Anum_pg_shdepend_classid - 1] = ObjectIdGetDatum(classId);
	values[Anum_pg_shdepend_objid - 1] = ObjectIdGetDatum(objectId);
	values[Anum_pg_shdepend_objsubid - 1] = Int32GetDatum(objsubId);

	values[Anum_pg_shdepend_refclassid - 1] = ObjectIdGetDatum(refclassId);
	values[Anum_pg_shdepend_refobjid - 1] = ObjectIdGetDatum(refobjId);
	values[Anum_pg_shdepend_deptype - 1] = CharGetDatum(deptype);

	tup = heap_form_tuple(sdepRel->rd_att, values, nulls);

	CatalogTupleInsert(sdepRel, tup);

	/* clean up */
	heap_freetuple(tup);
}