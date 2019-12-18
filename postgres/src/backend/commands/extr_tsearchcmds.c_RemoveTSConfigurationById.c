#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_ts_config_map_mapcfg ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CatalogTupleDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ HeapTupleIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (TYPE_1__*) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSCONFIGOID ; 
 int /*<<< orphan*/  TSConfigMapIndexId ; 
 int /*<<< orphan*/  TSConfigMapRelationId ; 
 int /*<<< orphan*/  TSConfigRelationId ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 TYPE_1__* systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
RemoveTSConfigurationById(Oid cfgId)
{
	Relation	relCfg,
				relMap;
	HeapTuple	tup;
	ScanKeyData skey;
	SysScanDesc scan;

	/* Remove the pg_ts_config entry */
	relCfg = table_open(TSConfigRelationId, RowExclusiveLock);

	tup = SearchSysCache1(TSCONFIGOID, ObjectIdGetDatum(cfgId));

	if (!HeapTupleIsValid(tup))
		elog(ERROR, "cache lookup failed for text search dictionary %u",
			 cfgId);

	CatalogTupleDelete(relCfg, &tup->t_self);

	ReleaseSysCache(tup);

	table_close(relCfg, RowExclusiveLock);

	/* Remove any pg_ts_config_map entries */
	relMap = table_open(TSConfigMapRelationId, RowExclusiveLock);

	ScanKeyInit(&skey,
				Anum_pg_ts_config_map_mapcfg,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(cfgId));

	scan = systable_beginscan(relMap, TSConfigMapIndexId, true,
							  NULL, 1, &skey);

	while (HeapTupleIsValid((tup = systable_getnext(scan))))
	{
		CatalogTupleDelete(relMap, &tup->t_self);
	}

	systable_endscan(scan);

	table_close(relMap, RowExclusiveLock);
}