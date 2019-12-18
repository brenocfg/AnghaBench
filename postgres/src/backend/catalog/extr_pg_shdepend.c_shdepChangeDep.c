#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nulls ;
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_12__ {scalar_t__ deptype; void* refobjid; void* refclassid; } ;
struct TYPE_11__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  scalar_t__ SharedDependencyType ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  void* Oid ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_shdepend ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int Anum_pg_shdepend_classid ; 
 int Anum_pg_shdepend_dbid ; 
 int Anum_pg_shdepend_deptype ; 
 int Anum_pg_shdepend_objid ; 
 int Anum_pg_shdepend_objsubid ; 
 int Anum_pg_shdepend_refclassid ; 
 int Anum_pg_shdepend_refobjid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CatalogTupleDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CatalogTupleInsert (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  CharGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int Natts_pg_shdepend ; 
 int /*<<< orphan*/  ObjectIdGetDatum (void*) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SharedDependDependerIndexId ; 
 void* classIdGetDbId (void*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,void*,void*,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* heap_copytuple (TYPE_1__*) ; 
 TYPE_1__* heap_form_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_1__*) ; 
 scalar_t__ isSharedObjectPinned (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  shdepLockAndCheckObject (void*,void*) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 TYPE_1__* systable_getnext (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
shdepChangeDep(Relation sdepRel,
			   Oid classid, Oid objid, int32 objsubid,
			   Oid refclassid, Oid refobjid,
			   SharedDependencyType deptype)
{
	Oid			dbid = classIdGetDbId(classid);
	HeapTuple	oldtup = NULL;
	HeapTuple	scantup;
	ScanKeyData key[4];
	SysScanDesc scan;

	/*
	 * Make sure the new referenced object doesn't go away while we record the
	 * dependency.
	 */
	shdepLockAndCheckObject(refclassid, refobjid);

	/*
	 * Look for a previous entry
	 */
	ScanKeyInit(&key[0],
				Anum_pg_shdepend_dbid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(dbid));
	ScanKeyInit(&key[1],
				Anum_pg_shdepend_classid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(classid));
	ScanKeyInit(&key[2],
				Anum_pg_shdepend_objid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(objid));
	ScanKeyInit(&key[3],
				Anum_pg_shdepend_objsubid,
				BTEqualStrategyNumber, F_INT4EQ,
				Int32GetDatum(objsubid));

	scan = systable_beginscan(sdepRel, SharedDependDependerIndexId, true,
							  NULL, 4, key);

	while ((scantup = systable_getnext(scan)) != NULL)
	{
		/* Ignore if not of the target dependency type */
		if (((Form_pg_shdepend) GETSTRUCT(scantup))->deptype != deptype)
			continue;
		/* Caller screwed up if multiple matches */
		if (oldtup)
			elog(ERROR,
				 "multiple pg_shdepend entries for object %u/%u/%d deptype %c",
				 classid, objid, objsubid, deptype);
		oldtup = heap_copytuple(scantup);
	}

	systable_endscan(scan);

	if (isSharedObjectPinned(refclassid, refobjid, sdepRel))
	{
		/* No new entry needed, so just delete existing entry if any */
		if (oldtup)
			CatalogTupleDelete(sdepRel, &oldtup->t_self);
	}
	else if (oldtup)
	{
		/* Need to update existing entry */
		Form_pg_shdepend shForm = (Form_pg_shdepend) GETSTRUCT(oldtup);

		/* Since oldtup is a copy, we can just modify it in-memory */
		shForm->refclassid = refclassid;
		shForm->refobjid = refobjid;

		CatalogTupleUpdate(sdepRel, &oldtup->t_self, oldtup);
	}
	else
	{
		/* Need to insert new entry */
		Datum		values[Natts_pg_shdepend];
		bool		nulls[Natts_pg_shdepend];

		memset(nulls, false, sizeof(nulls));

		values[Anum_pg_shdepend_dbid - 1] = ObjectIdGetDatum(dbid);
		values[Anum_pg_shdepend_classid - 1] = ObjectIdGetDatum(classid);
		values[Anum_pg_shdepend_objid - 1] = ObjectIdGetDatum(objid);
		values[Anum_pg_shdepend_objsubid - 1] = Int32GetDatum(objsubid);

		values[Anum_pg_shdepend_refclassid - 1] = ObjectIdGetDatum(refclassid);
		values[Anum_pg_shdepend_refobjid - 1] = ObjectIdGetDatum(refobjid);
		values[Anum_pg_shdepend_deptype - 1] = CharGetDatum(deptype);

		/*
		 * we are reusing oldtup just to avoid declaring a new variable, but
		 * it's certainly a new tuple
		 */
		oldtup = heap_form_tuple(RelationGetDescr(sdepRel), values, nulls);
		CatalogTupleInsert(sdepRel, oldtup);
	}

	if (oldtup)
		heap_freetuple(oldtup);
}