#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  tgname; int /*<<< orphan*/  oid; } ;
struct TYPE_12__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_11__ {int /*<<< orphan*/  subname; int /*<<< orphan*/  newname; int /*<<< orphan*/  relation; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  TYPE_1__ RenameStmt ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  TYPE_2__* HeapTuple ;
typedef  TYPE_3__* Form_pg_trigger ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  Anum_pg_trigger_tgname ; 
 int /*<<< orphan*/  Anum_pg_trigger_tgrelid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CacheInvalidateRelcache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_OBJECT ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_NAMEEQ ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ GETSTRUCT (TYPE_2__*) ; 
 scalar_t__ HeapTupleIsValid (TYPE_2__*) ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectAddressSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RangeVarCallbackForRenameTrigger ; 
 int /*<<< orphan*/  RangeVarGetRelidExtended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TriggerRelationId ; 
 int /*<<< orphan*/  TriggerRelidNameIndexId ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* heap_copytuple (TYPE_2__*) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 TYPE_2__* systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ObjectAddress
renametrig(RenameStmt *stmt)
{
	Oid			tgoid;
	Relation	targetrel;
	Relation	tgrel;
	HeapTuple	tuple;
	SysScanDesc tgscan;
	ScanKeyData key[2];
	Oid			relid;
	ObjectAddress address;

	/*
	 * Look up name, check permissions, and acquire lock (which we will NOT
	 * release until end of transaction).
	 */
	relid = RangeVarGetRelidExtended(stmt->relation, AccessExclusiveLock,
									 0,
									 RangeVarCallbackForRenameTrigger,
									 NULL);

	/* Have lock already, so just need to build relcache entry. */
	targetrel = relation_open(relid, NoLock);

	/*
	 * Scan pg_trigger twice for existing triggers on relation.  We do this in
	 * order to ensure a trigger does not exist with newname (The unique index
	 * on tgrelid/tgname would complain anyway) and to ensure a trigger does
	 * exist with oldname.
	 *
	 * NOTE that this is cool only because we have AccessExclusiveLock on the
	 * relation, so the trigger set won't be changing underneath us.
	 */
	tgrel = table_open(TriggerRelationId, RowExclusiveLock);

	/*
	 * First pass -- look for name conflict
	 */
	ScanKeyInit(&key[0],
				Anum_pg_trigger_tgrelid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(relid));
	ScanKeyInit(&key[1],
				Anum_pg_trigger_tgname,
				BTEqualStrategyNumber, F_NAMEEQ,
				PointerGetDatum(stmt->newname));
	tgscan = systable_beginscan(tgrel, TriggerRelidNameIndexId, true,
								NULL, 2, key);
	if (HeapTupleIsValid(tuple = systable_getnext(tgscan)))
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_OBJECT),
				 errmsg("trigger \"%s\" for relation \"%s\" already exists",
						stmt->newname, RelationGetRelationName(targetrel))));
	systable_endscan(tgscan);

	/*
	 * Second pass -- look for trigger existing with oldname and update
	 */
	ScanKeyInit(&key[0],
				Anum_pg_trigger_tgrelid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(relid));
	ScanKeyInit(&key[1],
				Anum_pg_trigger_tgname,
				BTEqualStrategyNumber, F_NAMEEQ,
				PointerGetDatum(stmt->subname));
	tgscan = systable_beginscan(tgrel, TriggerRelidNameIndexId, true,
								NULL, 2, key);
	if (HeapTupleIsValid(tuple = systable_getnext(tgscan)))
	{
		Form_pg_trigger trigform;

		/*
		 * Update pg_trigger tuple with new tgname.
		 */
		tuple = heap_copytuple(tuple);	/* need a modifiable copy */
		trigform = (Form_pg_trigger) GETSTRUCT(tuple);
		tgoid = trigform->oid;

		namestrcpy(&trigform->tgname,
				   stmt->newname);

		CatalogTupleUpdate(tgrel, &tuple->t_self, tuple);

		InvokeObjectPostAlterHook(TriggerRelationId,
								  tgoid, 0);

		/*
		 * Invalidate relation's relcache entry so that other backends (and
		 * this one too!) are sent SI message to make them rebuild relcache
		 * entries.  (Ideally this should happen automatically...)
		 */
		CacheInvalidateRelcache(targetrel);
	}
	else
	{
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("trigger \"%s\" for table \"%s\" does not exist",
						stmt->subname, RelationGetRelationName(targetrel))));
	}

	ObjectAddressSet(address, TriggerRelationId, tgoid);

	systable_endscan(tgscan);

	table_close(tgrel, RowExclusiveLock);

	/*
	 * Close rel, but keep exclusive lock!
	 */
	relation_close(targetrel, NoLock);

	return address;
}