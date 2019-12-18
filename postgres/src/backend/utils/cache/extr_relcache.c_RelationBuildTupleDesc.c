#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_14__ ;
typedef  struct TYPE_23__   TYPE_12__ ;

/* Type definitions */
struct TYPE_26__ {int has_not_null; int has_generated_stored; int num_defval; int num_check; int /*<<< orphan*/ * check; TYPE_5__* missing; TYPE_6__* defval; } ;
typedef  TYPE_2__ TupleConstr ;
struct TYPE_30__ {int adnum; int /*<<< orphan*/ * adbin; } ;
struct TYPE_29__ {int am_present; int /*<<< orphan*/  am_value; } ;
struct TYPE_28__ {int attnum; scalar_t__ attgenerated; int /*<<< orphan*/  attlen; int /*<<< orphan*/  attbyval; int /*<<< orphan*/  attalign; scalar_t__ atthasmissing; scalar_t__ atthasdef; scalar_t__ attnotnull; } ;
struct TYPE_27__ {TYPE_14__* rd_att; TYPE_1__* rd_rel; } ;
struct TYPE_25__ {int relnatts; int relchecks; int /*<<< orphan*/  reltype; } ;
struct TYPE_24__ {int tdtypmod; TYPE_2__* constr; int /*<<< orphan*/  tdtypeid; } ;
struct TYPE_23__ {int attcacheoff; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  TYPE_3__* Relation ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_4__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ConstrCheck ;
typedef  TYPE_5__ AttrMissing ;
typedef  TYPE_6__ AttrDefault ;

/* Variables and functions */
 int /*<<< orphan*/  ATTRIBUTE_FIXED_PART_SIZE ; 
 scalar_t__ ATTRIBUTE_GENERATED_STORED ; 
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_attribute_attmissingval ; 
 int /*<<< orphan*/  Anum_pg_attribute_attnum ; 
 int /*<<< orphan*/  Anum_pg_attribute_attrelid ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  AttrDefaultFetch (TYPE_3__*) ; 
 int /*<<< orphan*/  AttributeRelationId ; 
 int /*<<< orphan*/  AttributeRelidNumIndexId ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  BTGreaterStrategyNumber ; 
 int /*<<< orphan*/  CacheMemoryContext ; 
 int /*<<< orphan*/  CheckConstraintFetch (TYPE_3__*) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_INT2GT ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int16GetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ MemoryContextAllocZero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int RelationGetNumberOfAttributes (TYPE_3__*) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_3__*) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_3__*) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_12__* TupleDescAttr (TYPE_14__*,int) ; 
 int /*<<< orphan*/  array_get_element (int /*<<< orphan*/ ,int,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  criticalRelcachesBuilt ; 
 int /*<<< orphan*/  datumCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_getattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_14__*,int*) ; 
 int /*<<< orphan*/  memcpy (TYPE_12__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 
 scalar_t__ repalloc (TYPE_6__*,int) ; 
 int /*<<< orphan*/  systable_beginscan (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
RelationBuildTupleDesc(Relation relation)
{
	HeapTuple	pg_attribute_tuple;
	Relation	pg_attribute_desc;
	SysScanDesc pg_attribute_scan;
	ScanKeyData skey[2];
	int			need;
	TupleConstr *constr;
	AttrDefault *attrdef = NULL;
	AttrMissing *attrmiss = NULL;
	int			ndef = 0;

	/* copy some fields from pg_class row to rd_att */
	relation->rd_att->tdtypeid = relation->rd_rel->reltype;
	relation->rd_att->tdtypmod = -1;	/* unnecessary, but... */

	constr = (TupleConstr *) MemoryContextAlloc(CacheMemoryContext,
												sizeof(TupleConstr));
	constr->has_not_null = false;
	constr->has_generated_stored = false;

	/*
	 * Form a scan key that selects only user attributes (attnum > 0).
	 * (Eliminating system attribute rows at the index level is lots faster
	 * than fetching them.)
	 */
	ScanKeyInit(&skey[0],
				Anum_pg_attribute_attrelid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(RelationGetRelid(relation)));
	ScanKeyInit(&skey[1],
				Anum_pg_attribute_attnum,
				BTGreaterStrategyNumber, F_INT2GT,
				Int16GetDatum(0));

	/*
	 * Open pg_attribute and begin a scan.  Force heap scan if we haven't yet
	 * built the critical relcache entries (this includes initdb and startup
	 * without a pg_internal.init file).
	 */
	pg_attribute_desc = table_open(AttributeRelationId, AccessShareLock);
	pg_attribute_scan = systable_beginscan(pg_attribute_desc,
										   AttributeRelidNumIndexId,
										   criticalRelcachesBuilt,
										   NULL,
										   2, skey);

	/*
	 * add attribute data to relation->rd_att
	 */
	need = RelationGetNumberOfAttributes(relation);

	while (HeapTupleIsValid(pg_attribute_tuple = systable_getnext(pg_attribute_scan)))
	{
		Form_pg_attribute attp;
		int			attnum;

		attp = (Form_pg_attribute) GETSTRUCT(pg_attribute_tuple);

		attnum = attp->attnum;
		if (attnum <= 0 || attnum > RelationGetNumberOfAttributes(relation))
			elog(ERROR, "invalid attribute number %d for %s",
				 attp->attnum, RelationGetRelationName(relation));


		memcpy(TupleDescAttr(relation->rd_att, attnum - 1),
			   attp,
			   ATTRIBUTE_FIXED_PART_SIZE);

		/* Update constraint/default info */
		if (attp->attnotnull)
			constr->has_not_null = true;
		if (attp->attgenerated == ATTRIBUTE_GENERATED_STORED)
			constr->has_generated_stored = true;

		/* If the column has a default, fill it into the attrdef array */
		if (attp->atthasdef)
		{
			if (attrdef == NULL)
				attrdef = (AttrDefault *)
					MemoryContextAllocZero(CacheMemoryContext,
										   RelationGetNumberOfAttributes(relation) *
										   sizeof(AttrDefault));
			attrdef[ndef].adnum = attnum;
			attrdef[ndef].adbin = NULL;

			ndef++;
		}

		/* Likewise for a missing value */
		if (attp->atthasmissing)
		{
			Datum		missingval;
			bool		missingNull;

			/* Do we have a missing value? */
			missingval = heap_getattr(pg_attribute_tuple,
									  Anum_pg_attribute_attmissingval,
									  pg_attribute_desc->rd_att,
									  &missingNull);
			if (!missingNull)
			{
				/* Yes, fetch from the array */
				MemoryContext oldcxt;
				bool		is_null;
				int			one = 1;
				Datum		missval;

				if (attrmiss == NULL)
					attrmiss = (AttrMissing *)
						MemoryContextAllocZero(CacheMemoryContext,
											   relation->rd_rel->relnatts *
											   sizeof(AttrMissing));

				missval = array_get_element(missingval,
											1,
											&one,
											-1,
											attp->attlen,
											attp->attbyval,
											attp->attalign,
											&is_null);
				Assert(!is_null);
				if (attp->attbyval)
				{
					/* for copy by val just copy the datum direct */
					attrmiss[attnum - 1].am_value = missval;
				}
				else
				{
					/* otherwise copy in the correct context */
					oldcxt = MemoryContextSwitchTo(CacheMemoryContext);
					attrmiss[attnum - 1].am_value = datumCopy(missval,
															  attp->attbyval,
															  attp->attlen);
					MemoryContextSwitchTo(oldcxt);
				}
				attrmiss[attnum - 1].am_present = true;
			}
		}
		need--;
		if (need == 0)
			break;
	}

	/*
	 * end the scan and close the attribute relation
	 */
	systable_endscan(pg_attribute_scan);
	table_close(pg_attribute_desc, AccessShareLock);

	if (need != 0)
		elog(ERROR, "catalog is missing %d attribute(s) for relid %u",
			 need, RelationGetRelid(relation));

	/*
	 * The attcacheoff values we read from pg_attribute should all be -1
	 * ("unknown").  Verify this if assert checking is on.  They will be
	 * computed when and if needed during tuple access.
	 */
#ifdef USE_ASSERT_CHECKING
	{
		int			i;

		for (i = 0; i < RelationGetNumberOfAttributes(relation); i++)
			Assert(TupleDescAttr(relation->rd_att, i)->attcacheoff == -1);
	}
#endif

	/*
	 * However, we can easily set the attcacheoff value for the first
	 * attribute: it must be zero.  This eliminates the need for special cases
	 * for attnum=1 that used to exist in fastgetattr() and index_getattr().
	 */
	if (RelationGetNumberOfAttributes(relation) > 0)
		TupleDescAttr(relation->rd_att, 0)->attcacheoff = 0;

	/*
	 * Set up constraint/default info
	 */
	if (constr->has_not_null || ndef > 0 ||
		attrmiss || relation->rd_rel->relchecks)
	{
		relation->rd_att->constr = constr;

		if (ndef > 0)			/* DEFAULTs */
		{
			if (ndef < RelationGetNumberOfAttributes(relation))
				constr->defval = (AttrDefault *)
					repalloc(attrdef, ndef * sizeof(AttrDefault));
			else
				constr->defval = attrdef;
			constr->num_defval = ndef;
			AttrDefaultFetch(relation);
		}
		else
			constr->num_defval = 0;

		constr->missing = attrmiss;

		if (relation->rd_rel->relchecks > 0)	/* CHECKs */
		{
			constr->num_check = relation->rd_rel->relchecks;
			constr->check = (ConstrCheck *)
				MemoryContextAllocZero(CacheMemoryContext,
									   constr->num_check * sizeof(ConstrCheck));
			CheckConstraintFetch(relation);
		}
		else
			constr->num_check = 0;
	}
	else
	{
		pfree(constr);
		relation->rd_att->constr = NULL;
	}
}