#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  GucSource ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_db_role_setting_setconfig ; 
 int /*<<< orphan*/  Anum_pg_db_role_setting_setdatabase ; 
 int /*<<< orphan*/  Anum_pg_db_role_setting_setrole ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/ * DatumGetArrayTypeP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DbRoleSettingDatidRolidIndexId ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  GUC_ACTION_SET ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGC_SUSET ; 
 int /*<<< orphan*/  ProcessGUCArray (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_getattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 

void
ApplySetting(Snapshot snapshot, Oid databaseid, Oid roleid,
			 Relation relsetting, GucSource source)
{
	SysScanDesc scan;
	ScanKeyData keys[2];
	HeapTuple	tup;

	ScanKeyInit(&keys[0],
				Anum_pg_db_role_setting_setdatabase,
				BTEqualStrategyNumber,
				F_OIDEQ,
				ObjectIdGetDatum(databaseid));
	ScanKeyInit(&keys[1],
				Anum_pg_db_role_setting_setrole,
				BTEqualStrategyNumber,
				F_OIDEQ,
				ObjectIdGetDatum(roleid));

	scan = systable_beginscan(relsetting, DbRoleSettingDatidRolidIndexId, true,
							  snapshot, 2, keys);
	while (HeapTupleIsValid(tup = systable_getnext(scan)))
	{
		bool		isnull;
		Datum		datum;

		datum = heap_getattr(tup, Anum_pg_db_role_setting_setconfig,
							 RelationGetDescr(relsetting), &isnull);
		if (!isnull)
		{
			ArrayType  *a = DatumGetArrayTypeP(datum);

			/*
			 * We process all the options at SUSET level.  We assume that the
			 * right to insert an option into pg_db_role_setting was checked
			 * when it was inserted.
			 */
			ProcessGUCArray(a, PGC_SUSET, source, GUC_ACTION_SET);
		}
	}

	systable_endscan(scan);
}