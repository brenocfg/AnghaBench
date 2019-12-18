#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_1__* constr; } ;
struct TYPE_19__ {scalar_t__ adnum; int /*<<< orphan*/ * adbin; } ;
struct TYPE_18__ {scalar_t__ adnum; } ;
struct TYPE_17__ {int /*<<< orphan*/  attname; } ;
struct TYPE_16__ {TYPE_9__* rd_att; } ;
struct TYPE_15__ {int num_defval; TYPE_5__* defval; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__* Form_pg_attribute ;
typedef  TYPE_4__* Form_pg_attrdef ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_5__ AttrDefault ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_attrdef_adbin ; 
 int /*<<< orphan*/  Anum_pg_attrdef_adrelid ; 
 int /*<<< orphan*/  AttrDefaultIndexId ; 
 int /*<<< orphan*/  AttrDefaultRelationId ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CacheMemoryContext ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * MemoryContextStrdup (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_2__*) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 TYPE_3__* TupleDescAttr (TYPE_9__*,scalar_t__) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fastgetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_9__*,int*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  systable_beginscan (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
AttrDefaultFetch(Relation relation)
{
	AttrDefault *attrdef = relation->rd_att->constr->defval;
	int			ndef = relation->rd_att->constr->num_defval;
	Relation	adrel;
	SysScanDesc adscan;
	ScanKeyData skey;
	HeapTuple	htup;
	Datum		val;
	bool		isnull;
	int			found;
	int			i;

	ScanKeyInit(&skey,
				Anum_pg_attrdef_adrelid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(RelationGetRelid(relation)));

	adrel = table_open(AttrDefaultRelationId, AccessShareLock);
	adscan = systable_beginscan(adrel, AttrDefaultIndexId, true,
								NULL, 1, &skey);
	found = 0;

	while (HeapTupleIsValid(htup = systable_getnext(adscan)))
	{
		Form_pg_attrdef adform = (Form_pg_attrdef) GETSTRUCT(htup);
		Form_pg_attribute attr = TupleDescAttr(relation->rd_att, adform->adnum - 1);

		for (i = 0; i < ndef; i++)
		{
			if (adform->adnum != attrdef[i].adnum)
				continue;
			if (attrdef[i].adbin != NULL)
				elog(WARNING, "multiple attrdef records found for attr %s of rel %s",
					 NameStr(attr->attname),
					 RelationGetRelationName(relation));
			else
				found++;

			val = fastgetattr(htup,
							  Anum_pg_attrdef_adbin,
							  adrel->rd_att, &isnull);
			if (isnull)
				elog(WARNING, "null adbin for attr %s of rel %s",
					 NameStr(attr->attname),
					 RelationGetRelationName(relation));
			else
			{
				/* detoast and convert to cstring in caller's context */
				char	   *s = TextDatumGetCString(val);

				attrdef[i].adbin = MemoryContextStrdup(CacheMemoryContext, s);
				pfree(s);
			}
			break;
		}

		if (i >= ndef)
			elog(WARNING, "unexpected attrdef record found for attr %d of rel %s",
				 adform->adnum, RelationGetRelationName(relation));
	}

	systable_endscan(adscan);
	table_close(adrel, AccessShareLock);
}