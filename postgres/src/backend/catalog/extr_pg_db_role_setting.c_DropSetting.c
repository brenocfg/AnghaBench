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
typedef  int /*<<< orphan*/  TableScanDesc ;
struct TYPE_4__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_db_role_setting_setdatabase ; 
 int /*<<< orphan*/  Anum_pg_db_role_setting_setrole ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CatalogTupleDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DbRoleSettingRelationId ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 scalar_t__ HeapTupleIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* heap_getnext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_beginscan_catalog (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
DropSetting(Oid databaseid, Oid roleid)
{
	Relation	relsetting;
	TableScanDesc scan;
	ScanKeyData keys[2];
	HeapTuple	tup;
	int			numkeys = 0;

	relsetting = table_open(DbRoleSettingRelationId, RowExclusiveLock);

	if (OidIsValid(databaseid))
	{
		ScanKeyInit(&keys[numkeys],
					Anum_pg_db_role_setting_setdatabase,
					BTEqualStrategyNumber,
					F_OIDEQ,
					ObjectIdGetDatum(databaseid));
		numkeys++;
	}
	if (OidIsValid(roleid))
	{
		ScanKeyInit(&keys[numkeys],
					Anum_pg_db_role_setting_setrole,
					BTEqualStrategyNumber,
					F_OIDEQ,
					ObjectIdGetDatum(roleid));
		numkeys++;
	}

	scan = table_beginscan_catalog(relsetting, numkeys, keys);
	while (HeapTupleIsValid(tup = heap_getnext(scan, ForwardScanDirection)))
	{
		CatalogTupleDelete(relsetting, &tup->t_self);
	}
	table_endscan(scan);

	table_close(relsetting, RowExclusiveLock);
}