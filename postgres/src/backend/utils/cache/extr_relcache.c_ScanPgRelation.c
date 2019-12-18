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

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_class_oid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  ClassOidIndexId ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  GetCatalogSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetNonHistoricCatalogSnapshot (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ criticalRelcachesBuilt ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  heap_copytuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HeapTuple
ScanPgRelation(Oid targetRelId, bool indexOK, bool force_non_historic)
{
	HeapTuple	pg_class_tuple;
	Relation	pg_class_desc;
	SysScanDesc pg_class_scan;
	ScanKeyData key[1];
	Snapshot	snapshot;

	/*
	 * If something goes wrong during backend startup, we might find ourselves
	 * trying to read pg_class before we've selected a database.  That ain't
	 * gonna work, so bail out with a useful error message.  If this happens,
	 * it probably means a relcache entry that needs to be nailed isn't.
	 */
	if (!OidIsValid(MyDatabaseId))
		elog(FATAL, "cannot read pg_class without having selected a database");

	/*
	 * form a scan key
	 */
	ScanKeyInit(&key[0],
				Anum_pg_class_oid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(targetRelId));

	/*
	 * Open pg_class and fetch a tuple.  Force heap scan if we haven't yet
	 * built the critical relcache entries (this includes initdb and startup
	 * without a pg_internal.init file).  The caller can also force a heap
	 * scan by setting indexOK == false.
	 */
	pg_class_desc = table_open(RelationRelationId, AccessShareLock);

	/*
	 * The caller might need a tuple that's newer than the one the historic
	 * snapshot; currently the only case requiring to do so is looking up the
	 * relfilenode of non mapped system relations during decoding.
	 */
	if (force_non_historic)
		snapshot = GetNonHistoricCatalogSnapshot(RelationRelationId);
	else
		snapshot = GetCatalogSnapshot(RelationRelationId);

	pg_class_scan = systable_beginscan(pg_class_desc, ClassOidIndexId,
									   indexOK && criticalRelcachesBuilt,
									   snapshot,
									   1, key);

	pg_class_tuple = systable_getnext(pg_class_scan);

	/*
	 * Must copy tuple before releasing buffer.
	 */
	if (HeapTupleIsValid(pg_class_tuple))
		pg_class_tuple = heap_copytuple(pg_class_tuple);

	/* all done */
	systable_endscan(pg_class_scan);
	table_close(pg_class_desc, AccessShareLock);

	return pg_class_tuple;
}