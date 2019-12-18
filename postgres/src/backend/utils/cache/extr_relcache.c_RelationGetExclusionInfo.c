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
typedef  scalar_t__ uint16 ;
struct TYPE_13__ {scalar_t__ contype; scalar_t__ conindid; } ;
struct TYPE_12__ {scalar_t__* rd_exclstrats; scalar_t__* rd_exclops; scalar_t__* rd_exclprocs; int /*<<< orphan*/  rd_indexcxt; int /*<<< orphan*/ * rd_opfamily; int /*<<< orphan*/  rd_att; TYPE_1__* rd_index; } ;
struct TYPE_11__ {int /*<<< orphan*/  indrelid; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  TYPE_2__* Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__* Form_pg_constraint ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 scalar_t__* ARR_DATA_PTR (int /*<<< orphan*/ *) ; 
 int* ARR_DIMS (int /*<<< orphan*/ *) ; 
 scalar_t__ ARR_ELEMTYPE (int /*<<< orphan*/ *) ; 
 scalar_t__ ARR_HASNULL (int /*<<< orphan*/ *) ; 
 int ARR_NDIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_constraint_conexclop ; 
 int /*<<< orphan*/  Anum_pg_constraint_conrelid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 scalar_t__ CONSTRAINT_EXCLUSION ; 
 int /*<<< orphan*/  ConstraintRelationId ; 
 int /*<<< orphan*/  ConstraintRelidTypidNameIndexId ; 
 int /*<<< orphan*/ * DatumGetArrayTypeP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int IndexRelationGetNumberOfKeyAttributes (TYPE_2__*) ; 
 scalar_t__ InvalidStrategy ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ OIDOID ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_2__*) ; 
 scalar_t__ RelationGetRelid (TYPE_2__*) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fastgetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ get_op_opfamily_strategy (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ get_opcode (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  systable_beginscan (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
RelationGetExclusionInfo(Relation indexRelation,
						 Oid **operators,
						 Oid **procs,
						 uint16 **strategies)
{
	int			indnkeyatts;
	Oid		   *ops;
	Oid		   *funcs;
	uint16	   *strats;
	Relation	conrel;
	SysScanDesc conscan;
	ScanKeyData skey[1];
	HeapTuple	htup;
	bool		found;
	MemoryContext oldcxt;
	int			i;

	indnkeyatts = IndexRelationGetNumberOfKeyAttributes(indexRelation);

	/* Allocate result space in caller context */
	*operators = ops = (Oid *) palloc(sizeof(Oid) * indnkeyatts);
	*procs = funcs = (Oid *) palloc(sizeof(Oid) * indnkeyatts);
	*strategies = strats = (uint16 *) palloc(sizeof(uint16) * indnkeyatts);

	/* Quick exit if we have the data cached already */
	if (indexRelation->rd_exclstrats != NULL)
	{
		memcpy(ops, indexRelation->rd_exclops, sizeof(Oid) * indnkeyatts);
		memcpy(funcs, indexRelation->rd_exclprocs, sizeof(Oid) * indnkeyatts);
		memcpy(strats, indexRelation->rd_exclstrats, sizeof(uint16) * indnkeyatts);
		return;
	}

	/*
	 * Search pg_constraint for the constraint associated with the index. To
	 * make this not too painfully slow, we use the index on conrelid; that
	 * will hold the parent relation's OID not the index's own OID.
	 *
	 * Note: if we wanted to rely on the constraint name matching the index's
	 * name, we could just do a direct lookup using pg_constraint's unique
	 * index.  For the moment it doesn't seem worth requiring that.
	 */
	ScanKeyInit(&skey[0],
				Anum_pg_constraint_conrelid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(indexRelation->rd_index->indrelid));

	conrel = table_open(ConstraintRelationId, AccessShareLock);
	conscan = systable_beginscan(conrel, ConstraintRelidTypidNameIndexId, true,
								 NULL, 1, skey);
	found = false;

	while (HeapTupleIsValid(htup = systable_getnext(conscan)))
	{
		Form_pg_constraint conform = (Form_pg_constraint) GETSTRUCT(htup);
		Datum		val;
		bool		isnull;
		ArrayType  *arr;
		int			nelem;

		/* We want the exclusion constraint owning the index */
		if (conform->contype != CONSTRAINT_EXCLUSION ||
			conform->conindid != RelationGetRelid(indexRelation))
			continue;

		/* There should be only one */
		if (found)
			elog(ERROR, "unexpected exclusion constraint record found for rel %s",
				 RelationGetRelationName(indexRelation));
		found = true;

		/* Extract the operator OIDS from conexclop */
		val = fastgetattr(htup,
						  Anum_pg_constraint_conexclop,
						  conrel->rd_att, &isnull);
		if (isnull)
			elog(ERROR, "null conexclop for rel %s",
				 RelationGetRelationName(indexRelation));

		arr = DatumGetArrayTypeP(val);	/* ensure not toasted */
		nelem = ARR_DIMS(arr)[0];
		if (ARR_NDIM(arr) != 1 ||
			nelem != indnkeyatts ||
			ARR_HASNULL(arr) ||
			ARR_ELEMTYPE(arr) != OIDOID)
			elog(ERROR, "conexclop is not a 1-D Oid array");

		memcpy(ops, ARR_DATA_PTR(arr), sizeof(Oid) * indnkeyatts);
	}

	systable_endscan(conscan);
	table_close(conrel, AccessShareLock);

	if (!found)
		elog(ERROR, "exclusion constraint record missing for rel %s",
			 RelationGetRelationName(indexRelation));

	/* We need the func OIDs and strategy numbers too */
	for (i = 0; i < indnkeyatts; i++)
	{
		funcs[i] = get_opcode(ops[i]);
		strats[i] = get_op_opfamily_strategy(ops[i],
											 indexRelation->rd_opfamily[i]);
		/* shouldn't fail, since it was checked at index creation */
		if (strats[i] == InvalidStrategy)
			elog(ERROR, "could not find strategy for operator %u in family %u",
				 ops[i], indexRelation->rd_opfamily[i]);
	}

	/* Save a copy of the results in the relcache entry. */
	oldcxt = MemoryContextSwitchTo(indexRelation->rd_indexcxt);
	indexRelation->rd_exclops = (Oid *) palloc(sizeof(Oid) * indnkeyatts);
	indexRelation->rd_exclprocs = (Oid *) palloc(sizeof(Oid) * indnkeyatts);
	indexRelation->rd_exclstrats = (uint16 *) palloc(sizeof(uint16) * indnkeyatts);
	memcpy(indexRelation->rd_exclops, ops, sizeof(Oid) * indnkeyatts);
	memcpy(indexRelation->rd_exclprocs, funcs, sizeof(Oid) * indnkeyatts);
	memcpy(indexRelation->rd_exclstrats, strats, sizeof(uint16) * indnkeyatts);
	MemoryContextSwitchTo(oldcxt);
}