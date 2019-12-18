#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_26__ {TYPE_2__* es_result_relation_info; } ;
struct TYPE_25__ {int /*<<< orphan*/ * ecxt_scantuple; } ;
struct TYPE_24__ {int /*<<< orphan*/ * ii_PredicateState; int /*<<< orphan*/ * ii_Predicate; int /*<<< orphan*/  ii_ReadyForInserts; int /*<<< orphan*/  ii_ExclusionOps; int /*<<< orphan*/  ii_Unique; } ;
struct TYPE_23__ {TYPE_1__* rd_index; } ;
struct TYPE_22__ {int ri_NumIndices; TYPE_3__* ri_RelationDesc; TYPE_5__** ri_IndexRelationInfo; TYPE_3__** ri_IndexRelationDescs; } ;
struct TYPE_21__ {int /*<<< orphan*/  indimmediate; int /*<<< orphan*/  indexrelid; } ;
typedef  TYPE_2__ ResultRelInfo ;
typedef  TYPE_3__** RelationPtr ;
typedef  TYPE_3__* Relation ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  TYPE_5__ IndexInfo ;
typedef  int /*<<< orphan*/  ExprState ;
typedef  TYPE_6__ ExprContext ;
typedef  TYPE_7__ EState ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CEOUC_WAIT ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * ExecPrepareQual (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  ExecQual (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  FormIndexDatum (TYPE_5__*,int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ *,int*) ; 
 TYPE_6__* GetPerTupleExprContext (TYPE_7__*) ; 
 int INDEX_MAX_KEYS ; 
 int /*<<< orphan*/  ItemPointerSetInvalid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_3__*) ; 
 int check_exclusion_or_unique_constraint (TYPE_3__*,TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,TYPE_7__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  errtableconstraint (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_member_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool
ExecCheckIndexConstraints(TupleTableSlot *slot,
						  EState *estate, ItemPointer conflictTid,
						  List *arbiterIndexes)
{
	ResultRelInfo *resultRelInfo;
	int			i;
	int			numIndices;
	RelationPtr relationDescs;
	Relation	heapRelation;
	IndexInfo **indexInfoArray;
	ExprContext *econtext;
	Datum		values[INDEX_MAX_KEYS];
	bool		isnull[INDEX_MAX_KEYS];
	ItemPointerData invalidItemPtr;
	bool		checkedIndex = false;

	ItemPointerSetInvalid(conflictTid);
	ItemPointerSetInvalid(&invalidItemPtr);

	/*
	 * Get information from the result relation info structure.
	 */
	resultRelInfo = estate->es_result_relation_info;
	numIndices = resultRelInfo->ri_NumIndices;
	relationDescs = resultRelInfo->ri_IndexRelationDescs;
	indexInfoArray = resultRelInfo->ri_IndexRelationInfo;
	heapRelation = resultRelInfo->ri_RelationDesc;

	/*
	 * We will use the EState's per-tuple context for evaluating predicates
	 * and index expressions (creating it if it's not already there).
	 */
	econtext = GetPerTupleExprContext(estate);

	/* Arrange for econtext's scan tuple to be the tuple under test */
	econtext->ecxt_scantuple = slot;

	/*
	 * For each index, form index tuple and check if it satisfies the
	 * constraint.
	 */
	for (i = 0; i < numIndices; i++)
	{
		Relation	indexRelation = relationDescs[i];
		IndexInfo  *indexInfo;
		bool		satisfiesConstraint;

		if (indexRelation == NULL)
			continue;

		indexInfo = indexInfoArray[i];

		if (!indexInfo->ii_Unique && !indexInfo->ii_ExclusionOps)
			continue;

		/* If the index is marked as read-only, ignore it */
		if (!indexInfo->ii_ReadyForInserts)
			continue;

		/* When specific arbiter indexes requested, only examine them */
		if (arbiterIndexes != NIL &&
			!list_member_oid(arbiterIndexes,
							 indexRelation->rd_index->indexrelid))
			continue;

		if (!indexRelation->rd_index->indimmediate)
			ereport(ERROR,
					(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
					 errmsg("ON CONFLICT does not support deferrable unique constraints/exclusion constraints as arbiters"),
					 errtableconstraint(heapRelation,
										RelationGetRelationName(indexRelation))));

		checkedIndex = true;

		/* Check for partial index */
		if (indexInfo->ii_Predicate != NIL)
		{
			ExprState  *predicate;

			/*
			 * If predicate state not set up yet, create it (in the estate's
			 * per-query context)
			 */
			predicate = indexInfo->ii_PredicateState;
			if (predicate == NULL)
			{
				predicate = ExecPrepareQual(indexInfo->ii_Predicate, estate);
				indexInfo->ii_PredicateState = predicate;
			}

			/* Skip this index-update if the predicate isn't satisfied */
			if (!ExecQual(predicate, econtext))
				continue;
		}

		/*
		 * FormIndexDatum fills in its values and isnull parameters with the
		 * appropriate values for the column(s) of the index.
		 */
		FormIndexDatum(indexInfo,
					   slot,
					   estate,
					   values,
					   isnull);

		satisfiesConstraint =
			check_exclusion_or_unique_constraint(heapRelation, indexRelation,
												 indexInfo, &invalidItemPtr,
												 values, isnull, estate, false,
												 CEOUC_WAIT, true,
												 conflictTid);
		if (!satisfiesConstraint)
			return false;
	}

	if (arbiterIndexes != NIL && !checkedIndex)
		elog(ERROR, "unexpected failure to find arbiter index");

	return true;
}