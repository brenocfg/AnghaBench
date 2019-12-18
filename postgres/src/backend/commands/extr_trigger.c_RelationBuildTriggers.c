#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16 ;
typedef  int /*<<< orphan*/  bytea ;
struct TYPE_19__ {int numtriggers; TYPE_3__* triggers; } ;
typedef  TYPE_2__ TriggerDesc ;
struct TYPE_20__ {int tgnargs; int tgnattr; char** tgargs; int /*<<< orphan*/ * tgqual; int /*<<< orphan*/ * tgnewtable; int /*<<< orphan*/ * tgoldtable; int /*<<< orphan*/ * tgattr; int /*<<< orphan*/  tginitdeferred; int /*<<< orphan*/  tgdeferrable; int /*<<< orphan*/  tgconstraint; int /*<<< orphan*/  tgconstrindid; int /*<<< orphan*/  tgconstrrelid; int /*<<< orphan*/  tgisinternal; int /*<<< orphan*/  tgenabled; int /*<<< orphan*/  tgtype; int /*<<< orphan*/  tgfoid; void* tgname; int /*<<< orphan*/  tgoid; } ;
typedef  TYPE_3__ Trigger ;
struct TYPE_18__ {int dim1; int /*<<< orphan*/  values; } ;
struct TYPE_22__ {int tgnargs; TYPE_1__ tgattr; int /*<<< orphan*/  tginitdeferred; int /*<<< orphan*/  tgdeferrable; int /*<<< orphan*/  tgconstraint; int /*<<< orphan*/  tgconstrindid; int /*<<< orphan*/  tgconstrrelid; int /*<<< orphan*/  tgisinternal; int /*<<< orphan*/  tgenabled; int /*<<< orphan*/  tgtype; int /*<<< orphan*/  tgfoid; int /*<<< orphan*/  tgname; int /*<<< orphan*/  oid; } ;
struct TYPE_21__ {int /*<<< orphan*/  trigdesc; int /*<<< orphan*/  rd_att; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  TYPE_4__* Relation ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_5__* Form_pg_trigger ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_trigger_tgargs ; 
 int /*<<< orphan*/  Anum_pg_trigger_tgnewtable ; 
 int /*<<< orphan*/  Anum_pg_trigger_tgoldtable ; 
 int /*<<< orphan*/  Anum_pg_trigger_tgqual ; 
 int /*<<< orphan*/  Anum_pg_trigger_tgrelid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CacheMemoryContext ; 
 int /*<<< orphan*/  CopyTriggerDesc (TYPE_2__*) ; 
 int /*<<< orphan*/ * DatumGetByteaPP (int /*<<< orphan*/ ) ; 
 void* DatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  FreeTriggerDesc (TYPE_2__*) ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_4__*) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_4__*) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTriggerFlags (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/ * TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TriggerRelationId ; 
 int /*<<< orphan*/  TriggerRelidNameIndexId ; 
 scalar_t__ VARDATA_ANY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fastgetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nameout ; 
 scalar_t__ palloc (int) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  pfree (TYPE_3__*) ; 
 char* pstrdup (char*) ; 
 scalar_t__ repalloc (TYPE_3__*,int) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  systable_beginscan (TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
RelationBuildTriggers(Relation relation)
{
	TriggerDesc *trigdesc;
	int			numtrigs;
	int			maxtrigs;
	Trigger    *triggers;
	Relation	tgrel;
	ScanKeyData skey;
	SysScanDesc tgscan;
	HeapTuple	htup;
	MemoryContext oldContext;
	int			i;

	/*
	 * Allocate a working array to hold the triggers (the array is extended if
	 * necessary)
	 */
	maxtrigs = 16;
	triggers = (Trigger *) palloc(maxtrigs * sizeof(Trigger));
	numtrigs = 0;

	/*
	 * Note: since we scan the triggers using TriggerRelidNameIndexId, we will
	 * be reading the triggers in name order, except possibly during
	 * emergency-recovery operations (ie, IgnoreSystemIndexes). This in turn
	 * ensures that triggers will be fired in name order.
	 */
	ScanKeyInit(&skey,
				Anum_pg_trigger_tgrelid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(RelationGetRelid(relation)));

	tgrel = table_open(TriggerRelationId, AccessShareLock);
	tgscan = systable_beginscan(tgrel, TriggerRelidNameIndexId, true,
								NULL, 1, &skey);

	while (HeapTupleIsValid(htup = systable_getnext(tgscan)))
	{
		Form_pg_trigger pg_trigger = (Form_pg_trigger) GETSTRUCT(htup);
		Trigger    *build;
		Datum		datum;
		bool		isnull;

		if (numtrigs >= maxtrigs)
		{
			maxtrigs *= 2;
			triggers = (Trigger *) repalloc(triggers, maxtrigs * sizeof(Trigger));
		}
		build = &(triggers[numtrigs]);

		build->tgoid = pg_trigger->oid;
		build->tgname = DatumGetCString(DirectFunctionCall1(nameout,
															NameGetDatum(&pg_trigger->tgname)));
		build->tgfoid = pg_trigger->tgfoid;
		build->tgtype = pg_trigger->tgtype;
		build->tgenabled = pg_trigger->tgenabled;
		build->tgisinternal = pg_trigger->tgisinternal;
		build->tgconstrrelid = pg_trigger->tgconstrrelid;
		build->tgconstrindid = pg_trigger->tgconstrindid;
		build->tgconstraint = pg_trigger->tgconstraint;
		build->tgdeferrable = pg_trigger->tgdeferrable;
		build->tginitdeferred = pg_trigger->tginitdeferred;
		build->tgnargs = pg_trigger->tgnargs;
		/* tgattr is first var-width field, so OK to access directly */
		build->tgnattr = pg_trigger->tgattr.dim1;
		if (build->tgnattr > 0)
		{
			build->tgattr = (int16 *) palloc(build->tgnattr * sizeof(int16));
			memcpy(build->tgattr, &(pg_trigger->tgattr.values),
				   build->tgnattr * sizeof(int16));
		}
		else
			build->tgattr = NULL;
		if (build->tgnargs > 0)
		{
			bytea	   *val;
			char	   *p;

			val = DatumGetByteaPP(fastgetattr(htup,
											  Anum_pg_trigger_tgargs,
											  tgrel->rd_att, &isnull));
			if (isnull)
				elog(ERROR, "tgargs is null in trigger for relation \"%s\"",
					 RelationGetRelationName(relation));
			p = (char *) VARDATA_ANY(val);
			build->tgargs = (char **) palloc(build->tgnargs * sizeof(char *));
			for (i = 0; i < build->tgnargs; i++)
			{
				build->tgargs[i] = pstrdup(p);
				p += strlen(p) + 1;
			}
		}
		else
			build->tgargs = NULL;

		datum = fastgetattr(htup, Anum_pg_trigger_tgoldtable,
							tgrel->rd_att, &isnull);
		if (!isnull)
			build->tgoldtable =
				DatumGetCString(DirectFunctionCall1(nameout, datum));
		else
			build->tgoldtable = NULL;

		datum = fastgetattr(htup, Anum_pg_trigger_tgnewtable,
							tgrel->rd_att, &isnull);
		if (!isnull)
			build->tgnewtable =
				DatumGetCString(DirectFunctionCall1(nameout, datum));
		else
			build->tgnewtable = NULL;

		datum = fastgetattr(htup, Anum_pg_trigger_tgqual,
							tgrel->rd_att, &isnull);
		if (!isnull)
			build->tgqual = TextDatumGetCString(datum);
		else
			build->tgqual = NULL;

		numtrigs++;
	}

	systable_endscan(tgscan);
	table_close(tgrel, AccessShareLock);

	/* There might not be any triggers */
	if (numtrigs == 0)
	{
		pfree(triggers);
		return;
	}

	/* Build trigdesc */
	trigdesc = (TriggerDesc *) palloc0(sizeof(TriggerDesc));
	trigdesc->triggers = triggers;
	trigdesc->numtriggers = numtrigs;
	for (i = 0; i < numtrigs; i++)
		SetTriggerFlags(trigdesc, &(triggers[i]));

	/* Copy completed trigdesc into cache storage */
	oldContext = MemoryContextSwitchTo(CacheMemoryContext);
	relation->trigdesc = CopyTriggerDesc(trigdesc);
	MemoryContextSwitchTo(oldContext);

	/* Release working memory */
	FreeTriggerDesc(trigdesc);
}