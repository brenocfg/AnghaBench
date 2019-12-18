#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_7__ {scalar_t__ refclassid; scalar_t__ refobjid; scalar_t__ deptype; } ;
struct TYPE_6__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  scalar_t__ SharedDependencyType ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Oid ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_shdepend ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_shdepend_classid ; 
 int /*<<< orphan*/  Anum_pg_shdepend_dbid ; 
 int /*<<< orphan*/  Anum_pg_shdepend_objid ; 
 int /*<<< orphan*/  Anum_pg_shdepend_objsubid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CatalogTupleDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  GETSTRUCT (TYPE_1__*) ; 
 scalar_t__ HeapTupleIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 scalar_t__ OidIsValid (scalar_t__) ; 
 scalar_t__ SHARED_DEPENDENCY_INVALID ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SharedDependDependerIndexId ; 
 scalar_t__ classIdGetDbId (scalar_t__) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 TYPE_1__* systable_getnext (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
shdepDropDependency(Relation sdepRel,
					Oid classId, Oid objectId, int32 objsubId,
					bool drop_subobjects,
					Oid refclassId, Oid refobjId,
					SharedDependencyType deptype)
{
	ScanKeyData key[4];
	int			nkeys;
	SysScanDesc scan;
	HeapTuple	tup;

	/* Scan for entries matching the dependent object */
	ScanKeyInit(&key[0],
				Anum_pg_shdepend_dbid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(classIdGetDbId(classId)));
	ScanKeyInit(&key[1],
				Anum_pg_shdepend_classid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(classId));
	ScanKeyInit(&key[2],
				Anum_pg_shdepend_objid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(objectId));
	if (drop_subobjects)
		nkeys = 3;
	else
	{
		ScanKeyInit(&key[3],
					Anum_pg_shdepend_objsubid,
					BTEqualStrategyNumber, F_INT4EQ,
					Int32GetDatum(objsubId));
		nkeys = 4;
	}

	scan = systable_beginscan(sdepRel, SharedDependDependerIndexId, true,
							  NULL, nkeys, key);

	while (HeapTupleIsValid(tup = systable_getnext(scan)))
	{
		Form_pg_shdepend shdepForm = (Form_pg_shdepend) GETSTRUCT(tup);

		/* Filter entries according to additional parameters */
		if (OidIsValid(refclassId) && shdepForm->refclassid != refclassId)
			continue;
		if (OidIsValid(refobjId) && shdepForm->refobjid != refobjId)
			continue;
		if (deptype != SHARED_DEPENDENCY_INVALID &&
			shdepForm->deptype != deptype)
			continue;

		/* OK, delete it */
		CatalogTupleDelete(sdepRel, &tup->t_self);
	}

	systable_endscan(scan);
}