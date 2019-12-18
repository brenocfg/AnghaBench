#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_28__ {char tgenabled; int /*<<< orphan*/  oid; int /*<<< orphan*/  tgname; int /*<<< orphan*/  tgtype; scalar_t__ tgisinternal; } ;
struct TYPE_27__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_26__ {int nparts; int /*<<< orphan*/ * oids; } ;
struct TYPE_25__ {TYPE_1__* rd_rel; } ;
struct TYPE_24__ {scalar_t__ relkind; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  TYPE_2__* Relation ;
typedef  TYPE_3__* PartitionDesc ;
typedef  int /*<<< orphan*/  LOCKMODE ;
typedef  TYPE_4__* HeapTuple ;
typedef  TYPE_5__* Form_pg_trigger ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_trigger_tgname ; 
 int /*<<< orphan*/  Anum_pg_trigger_tgrelid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CStringGetDatum (char const*) ; 
 int /*<<< orphan*/  CacheInvalidateRelcache (TYPE_2__*) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (TYPE_2__*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_NAMEEQ ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  GETSTRUCT (TYPE_4__*) ; 
 scalar_t__ HeapTupleIsValid (TYPE_4__*) ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ RELKIND_PARTITIONED_TABLE ; 
 TYPE_3__* RelationGetPartitionDesc (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_2__*) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRIGGER_FOR_ROW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TriggerRelationId ; 
 int /*<<< orphan*/  TriggerRelidNameIndexId ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,...) ; 
 TYPE_4__* heap_copytuple (TYPE_4__*) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_4__*) ; 
 TYPE_2__* relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superuser () ; 
 int /*<<< orphan*/  systable_beginscan (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 TYPE_4__* systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
EnableDisableTrigger(Relation rel, const char *tgname,
					 char fires_when, bool skip_system, LOCKMODE lockmode)
{
	Relation	tgrel;
	int			nkeys;
	ScanKeyData keys[2];
	SysScanDesc tgscan;
	HeapTuple	tuple;
	bool		found;
	bool		changed;

	/* Scan the relevant entries in pg_triggers */
	tgrel = table_open(TriggerRelationId, RowExclusiveLock);

	ScanKeyInit(&keys[0],
				Anum_pg_trigger_tgrelid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(RelationGetRelid(rel)));
	if (tgname)
	{
		ScanKeyInit(&keys[1],
					Anum_pg_trigger_tgname,
					BTEqualStrategyNumber, F_NAMEEQ,
					CStringGetDatum(tgname));
		nkeys = 2;
	}
	else
		nkeys = 1;

	tgscan = systable_beginscan(tgrel, TriggerRelidNameIndexId, true,
								NULL, nkeys, keys);

	found = changed = false;

	while (HeapTupleIsValid(tuple = systable_getnext(tgscan)))
	{
		Form_pg_trigger oldtrig = (Form_pg_trigger) GETSTRUCT(tuple);

		if (oldtrig->tgisinternal)
		{
			/* system trigger ... ok to process? */
			if (skip_system)
				continue;
			if (!superuser())
				ereport(ERROR,
						(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
						 errmsg("permission denied: \"%s\" is a system trigger",
								NameStr(oldtrig->tgname))));
		}

		found = true;

		if (oldtrig->tgenabled != fires_when)
		{
			/* need to change this one ... make a copy to scribble on */
			HeapTuple	newtup = heap_copytuple(tuple);
			Form_pg_trigger newtrig = (Form_pg_trigger) GETSTRUCT(newtup);

			newtrig->tgenabled = fires_when;

			CatalogTupleUpdate(tgrel, &newtup->t_self, newtup);

			heap_freetuple(newtup);

			/*
			 * When altering FOR EACH ROW triggers on a partitioned table, do
			 * the same on the partitions as well.
			 */
			if (rel->rd_rel->relkind == RELKIND_PARTITIONED_TABLE &&
				(TRIGGER_FOR_ROW(oldtrig->tgtype)))
			{
				PartitionDesc partdesc = RelationGetPartitionDesc(rel);
				int			i;

				for (i = 0; i < partdesc->nparts; i++)
				{
					Relation	part;

					part = relation_open(partdesc->oids[i], lockmode);
					EnableDisableTrigger(part, NameStr(oldtrig->tgname),
										 fires_when, skip_system, lockmode);
					table_close(part, NoLock);	/* keep lock till commit */
				}
			}

			changed = true;
		}

		InvokeObjectPostAlterHook(TriggerRelationId,
								  oldtrig->oid, 0);
	}

	systable_endscan(tgscan);

	table_close(tgrel, RowExclusiveLock);

	if (tgname && !found)
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("trigger \"%s\" for table \"%s\" does not exist",
						tgname, RelationGetRelationName(rel))));

	/*
	 * If we changed anything, broadcast a SI inval message to force each
	 * backend (including our own!) to rebuild relation's relcache entry.
	 * Otherwise they will fail to apply the change promptly.
	 */
	if (changed)
		CacheInvalidateRelcache(rel);
}