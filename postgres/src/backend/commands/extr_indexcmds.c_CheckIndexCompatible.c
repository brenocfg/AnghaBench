#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_15__ {scalar_t__* values; } ;
typedef  TYPE_1__ oidvector ;
typedef  int /*<<< orphan*/  int16 ;
struct TYPE_20__ {scalar_t__ oid; int /*<<< orphan*/  amhandler; } ;
struct TYPE_19__ {int indnkeyatts; scalar_t__ indisvalid; } ;
struct TYPE_18__ {int amcanorder; } ;
struct TYPE_17__ {scalar_t__* ii_ExclusionOps; } ;
struct TYPE_16__ {int /*<<< orphan*/  rd_att; } ;
struct TYPE_14__ {scalar_t__ atttypid; } ;
typedef  TYPE_2__* Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_3__ IndexInfo ;
typedef  TYPE_4__ IndexAmRoutine ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_5__* Form_pg_index ;
typedef  TYPE_6__* Form_pg_am ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  AMNAME ; 
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_index_indclass ; 
 int /*<<< orphan*/  Anum_pg_index_indcollation ; 
 int /*<<< orphan*/  Anum_pg_index_indexprs ; 
 int /*<<< orphan*/  Anum_pg_index_indpred ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ComputeIndexAttrs (TYPE_3__*,scalar_t__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,char const*,scalar_t__,int,int) ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 TYPE_4__* GetIndexAmRoutine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INDEXRELID ; 
 int INDEX_MAX_KEYS ; 
 scalar_t__ IndexGetRelation (scalar_t__,int) ; 
 scalar_t__ IsPolymorphicType (scalar_t__) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  PointerGetDatum (char const*) ; 
 int /*<<< orphan*/  RelationGetExclusionInfo (TYPE_2__*,scalar_t__**,scalar_t__**,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 TYPE_10__* TupleDescAttr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 scalar_t__ get_opclass_input_type (scalar_t__) ; 
 scalar_t__ heap_attisnull (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  index_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* index_open (scalar_t__,int /*<<< orphan*/ ) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 TYPE_3__* makeIndexInfo (int,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ memcmp (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  op_input_types (scalar_t__,scalar_t__*,scalar_t__*) ; 
 scalar_t__ palloc (int) ; 

bool
CheckIndexCompatible(Oid oldId,
					 const char *accessMethodName,
					 List *attributeList,
					 List *exclusionOpNames)
{
	bool		isconstraint;
	Oid		   *typeObjectId;
	Oid		   *collationObjectId;
	Oid		   *classObjectId;
	Oid			accessMethodId;
	Oid			relationId;
	HeapTuple	tuple;
	Form_pg_index indexForm;
	Form_pg_am	accessMethodForm;
	IndexAmRoutine *amRoutine;
	bool		amcanorder;
	int16	   *coloptions;
	IndexInfo  *indexInfo;
	int			numberOfAttributes;
	int			old_natts;
	bool		isnull;
	bool		ret = true;
	oidvector  *old_indclass;
	oidvector  *old_indcollation;
	Relation	irel;
	int			i;
	Datum		d;

	/* Caller should already have the relation locked in some way. */
	relationId = IndexGetRelation(oldId, false);

	/*
	 * We can pretend isconstraint = false unconditionally.  It only serves to
	 * decide the text of an error message that should never happen for us.
	 */
	isconstraint = false;

	numberOfAttributes = list_length(attributeList);
	Assert(numberOfAttributes > 0);
	Assert(numberOfAttributes <= INDEX_MAX_KEYS);

	/* look up the access method */
	tuple = SearchSysCache1(AMNAME, PointerGetDatum(accessMethodName));
	if (!HeapTupleIsValid(tuple))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("access method \"%s\" does not exist",
						accessMethodName)));
	accessMethodForm = (Form_pg_am) GETSTRUCT(tuple);
	accessMethodId = accessMethodForm->oid;
	amRoutine = GetIndexAmRoutine(accessMethodForm->amhandler);
	ReleaseSysCache(tuple);

	amcanorder = amRoutine->amcanorder;

	/*
	 * Compute the operator classes, collations, and exclusion operators for
	 * the new index, so we can test whether it's compatible with the existing
	 * one.  Note that ComputeIndexAttrs might fail here, but that's OK:
	 * DefineIndex would have called this function with the same arguments
	 * later on, and it would have failed then anyway.  Our attributeList
	 * contains only key attributes, thus we're filling ii_NumIndexAttrs and
	 * ii_NumIndexKeyAttrs with same value.
	 */
	indexInfo = makeIndexInfo(numberOfAttributes, numberOfAttributes,
							  accessMethodId, NIL, NIL, false, false, false);
	typeObjectId = (Oid *) palloc(numberOfAttributes * sizeof(Oid));
	collationObjectId = (Oid *) palloc(numberOfAttributes * sizeof(Oid));
	classObjectId = (Oid *) palloc(numberOfAttributes * sizeof(Oid));
	coloptions = (int16 *) palloc(numberOfAttributes * sizeof(int16));
	ComputeIndexAttrs(indexInfo,
					  typeObjectId, collationObjectId, classObjectId,
					  coloptions, attributeList,
					  exclusionOpNames, relationId,
					  accessMethodName, accessMethodId,
					  amcanorder, isconstraint);


	/* Get the soon-obsolete pg_index tuple. */
	tuple = SearchSysCache1(INDEXRELID, ObjectIdGetDatum(oldId));
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "cache lookup failed for index %u", oldId);
	indexForm = (Form_pg_index) GETSTRUCT(tuple);

	/*
	 * We don't assess expressions or predicates; assume incompatibility.
	 * Also, if the index is invalid for any reason, treat it as incompatible.
	 */
	if (!(heap_attisnull(tuple, Anum_pg_index_indpred, NULL) &&
		  heap_attisnull(tuple, Anum_pg_index_indexprs, NULL) &&
		  indexForm->indisvalid))
	{
		ReleaseSysCache(tuple);
		return false;
	}

	/* Any change in operator class or collation breaks compatibility. */
	old_natts = indexForm->indnkeyatts;
	Assert(old_natts == numberOfAttributes);

	d = SysCacheGetAttr(INDEXRELID, tuple, Anum_pg_index_indcollation, &isnull);
	Assert(!isnull);
	old_indcollation = (oidvector *) DatumGetPointer(d);

	d = SysCacheGetAttr(INDEXRELID, tuple, Anum_pg_index_indclass, &isnull);
	Assert(!isnull);
	old_indclass = (oidvector *) DatumGetPointer(d);

	ret = (memcmp(old_indclass->values, classObjectId,
				  old_natts * sizeof(Oid)) == 0 &&
		   memcmp(old_indcollation->values, collationObjectId,
				  old_natts * sizeof(Oid)) == 0);

	ReleaseSysCache(tuple);

	if (!ret)
		return false;

	/* For polymorphic opcintype, column type changes break compatibility. */
	irel = index_open(oldId, AccessShareLock);	/* caller probably has a lock */
	for (i = 0; i < old_natts; i++)
	{
		if (IsPolymorphicType(get_opclass_input_type(classObjectId[i])) &&
			TupleDescAttr(irel->rd_att, i)->atttypid != typeObjectId[i])
		{
			ret = false;
			break;
		}
	}

	/* Any change in exclusion operator selections breaks compatibility. */
	if (ret && indexInfo->ii_ExclusionOps != NULL)
	{
		Oid		   *old_operators,
				   *old_procs;
		uint16	   *old_strats;

		RelationGetExclusionInfo(irel, &old_operators, &old_procs, &old_strats);
		ret = memcmp(old_operators, indexInfo->ii_ExclusionOps,
					 old_natts * sizeof(Oid)) == 0;

		/* Require an exact input type match for polymorphic operators. */
		if (ret)
		{
			for (i = 0; i < old_natts && ret; i++)
			{
				Oid			left,
							right;

				op_input_types(indexInfo->ii_ExclusionOps[i], &left, &right);
				if ((IsPolymorphicType(left) || IsPolymorphicType(right)) &&
					TupleDescAttr(irel->rd_att, i)->atttypid != typeObjectId[i])
				{
					ret = false;
					break;
				}
			}
		}
	}

	index_close(irel, NoLock);
	return ret;
}