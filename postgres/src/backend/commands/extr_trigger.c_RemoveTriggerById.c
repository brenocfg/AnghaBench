#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  tgrelid; } ;
struct TYPE_17__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_16__ {TYPE_1__* rd_rel; } ;
struct TYPE_15__ {scalar_t__ relkind; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_3__* HeapTuple ;
typedef  TYPE_4__* Form_pg_trigger ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  Anum_pg_trigger_oid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CacheInvalidateRelcache (TYPE_2__*) ; 
 int /*<<< orphan*/  CatalogTupleDelete (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ GETSTRUCT (TYPE_3__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_3__*) ; 
 scalar_t__ IsSystemRelation (TYPE_2__*) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ RELKIND_FOREIGN_TABLE ; 
 scalar_t__ RELKIND_PARTITIONED_TABLE ; 
 scalar_t__ RELKIND_RELATION ; 
 scalar_t__ RELKIND_VIEW ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_2__*) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TriggerOidIndexId ; 
 int /*<<< orphan*/  TriggerRelationId ; 
 int /*<<< orphan*/  allowSystemTableMods ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 TYPE_3__* systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
RemoveTriggerById(Oid trigOid)
{
	Relation	tgrel;
	SysScanDesc tgscan;
	ScanKeyData skey[1];
	HeapTuple	tup;
	Oid			relid;
	Relation	rel;

	tgrel = table_open(TriggerRelationId, RowExclusiveLock);

	/*
	 * Find the trigger to delete.
	 */
	ScanKeyInit(&skey[0],
				Anum_pg_trigger_oid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(trigOid));

	tgscan = systable_beginscan(tgrel, TriggerOidIndexId, true,
								NULL, 1, skey);

	tup = systable_getnext(tgscan);
	if (!HeapTupleIsValid(tup))
		elog(ERROR, "could not find tuple for trigger %u", trigOid);

	/*
	 * Open and exclusive-lock the relation the trigger belongs to.
	 */
	relid = ((Form_pg_trigger) GETSTRUCT(tup))->tgrelid;

	rel = table_open(relid, AccessExclusiveLock);

	if (rel->rd_rel->relkind != RELKIND_RELATION &&
		rel->rd_rel->relkind != RELKIND_VIEW &&
		rel->rd_rel->relkind != RELKIND_FOREIGN_TABLE &&
		rel->rd_rel->relkind != RELKIND_PARTITIONED_TABLE)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("\"%s\" is not a table, view, or foreign table",
						RelationGetRelationName(rel))));

	if (!allowSystemTableMods && IsSystemRelation(rel))
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("permission denied: \"%s\" is a system catalog",
						RelationGetRelationName(rel))));

	/*
	 * Delete the pg_trigger tuple.
	 */
	CatalogTupleDelete(tgrel, &tup->t_self);

	systable_endscan(tgscan);
	table_close(tgrel, RowExclusiveLock);

	/*
	 * We do not bother to try to determine whether any other triggers remain,
	 * which would be needed in order to decide whether it's safe to clear the
	 * relation's relhastriggers.  (In any case, there might be a concurrent
	 * process adding new triggers.)  Instead, just force a relcache inval to
	 * make other backends (and this one too!) rebuild their relcache entries.
	 * There's no great harm in leaving relhastriggers true even if there are
	 * no triggers left.
	 */
	CacheInvalidateRelcache(rel);

	/* Keep lock on trigger's rel until end of xact */
	table_close(rel, NoLock);
}