#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_1__* constr; } ;
struct TYPE_16__ {void* ccbin; void* ccname; int /*<<< orphan*/  ccnoinherit; int /*<<< orphan*/  ccvalid; } ;
struct TYPE_15__ {scalar_t__ contype; int /*<<< orphan*/  conname; int /*<<< orphan*/  connoinherit; int /*<<< orphan*/  convalidated; } ;
struct TYPE_14__ {TYPE_9__* rd_att; } ;
struct TYPE_13__ {int num_check; TYPE_4__* check; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__* Form_pg_constraint ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_4__ ConstrCheck ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_constraint_conbin ; 
 int /*<<< orphan*/  Anum_pg_constraint_conrelid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 scalar_t__ CONSTRAINT_CHECK ; 
 int /*<<< orphan*/  CacheMemoryContext ; 
 int /*<<< orphan*/  CheckConstraintCmp ; 
 int /*<<< orphan*/  ConstraintRelationId ; 
 int /*<<< orphan*/  ConstraintRelidTypidNameIndexId ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 void* MemoryContextStrdup (int /*<<< orphan*/ ,char*) ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_2__*) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  fastgetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_9__*,int*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  qsort (TYPE_4__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
CheckConstraintFetch(Relation relation)
{
	ConstrCheck *check = relation->rd_att->constr->check;
	int			ncheck = relation->rd_att->constr->num_check;
	Relation	conrel;
	SysScanDesc conscan;
	ScanKeyData skey[1];
	HeapTuple	htup;
	int			found = 0;

	ScanKeyInit(&skey[0],
				Anum_pg_constraint_conrelid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(RelationGetRelid(relation)));

	conrel = table_open(ConstraintRelationId, AccessShareLock);
	conscan = systable_beginscan(conrel, ConstraintRelidTypidNameIndexId, true,
								 NULL, 1, skey);

	while (HeapTupleIsValid(htup = systable_getnext(conscan)))
	{
		Form_pg_constraint conform = (Form_pg_constraint) GETSTRUCT(htup);
		Datum		val;
		bool		isnull;
		char	   *s;

		/* We want check constraints only */
		if (conform->contype != CONSTRAINT_CHECK)
			continue;

		if (found >= ncheck)
			elog(ERROR, "unexpected constraint record found for rel %s",
				 RelationGetRelationName(relation));

		check[found].ccvalid = conform->convalidated;
		check[found].ccnoinherit = conform->connoinherit;
		check[found].ccname = MemoryContextStrdup(CacheMemoryContext,
												  NameStr(conform->conname));

		/* Grab and test conbin is actually set */
		val = fastgetattr(htup,
						  Anum_pg_constraint_conbin,
						  conrel->rd_att, &isnull);
		if (isnull)
			elog(ERROR, "null conbin for rel %s",
				 RelationGetRelationName(relation));

		/* detoast and convert to cstring in caller's context */
		s = TextDatumGetCString(val);
		check[found].ccbin = MemoryContextStrdup(CacheMemoryContext, s);
		pfree(s);

		found++;
	}

	systable_endscan(conscan);
	table_close(conrel, AccessShareLock);

	if (found != ncheck)
		elog(ERROR, "%d constraint record(s) missing for rel %s",
			 ncheck - found, RelationGetRelationName(relation));

	/* Sort the records so that CHECKs are applied in a deterministic order */
	if (ncheck > 1)
		qsort(check, ncheck, sizeof(ConstrCheck), CheckConstraintCmp);
}