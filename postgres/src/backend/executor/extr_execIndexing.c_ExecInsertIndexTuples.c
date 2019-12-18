#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
struct TYPE_27__ {scalar_t__ tts_tableOid; int /*<<< orphan*/  tts_tid; } ;
typedef  TYPE_2__ TupleTableSlot ;
struct TYPE_32__ {TYPE_3__* es_result_relation_info; } ;
struct TYPE_31__ {TYPE_2__* ecxt_scantuple; } ;
struct TYPE_30__ {int /*<<< orphan*/ * ii_ExclusionOps; int /*<<< orphan*/ * ii_PredicateState; int /*<<< orphan*/ * ii_Predicate; int /*<<< orphan*/  ii_ReadyForInserts; } ;
struct TYPE_29__ {TYPE_1__* rd_index; } ;
struct TYPE_28__ {int ri_NumIndices; TYPE_4__* ri_RelationDesc; TYPE_6__** ri_IndexRelationInfo; TYPE_4__** ri_IndexRelationDescs; } ;
struct TYPE_26__ {scalar_t__ indimmediate; int /*<<< orphan*/  indisunique; int /*<<< orphan*/  indexrelid; } ;
typedef  TYPE_3__ ResultRelInfo ;
typedef  TYPE_4__** RelationPtr ;
typedef  TYPE_4__* Relation ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  scalar_t__ IndexUniqueCheck ;
typedef  TYPE_6__ IndexInfo ;
typedef  int /*<<< orphan*/  ExprState ;
typedef  TYPE_7__ ExprContext ;
typedef  TYPE_8__ EState ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  CEOUC_WAIT_MODE ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CEOUC_LIVELOCK_PREVENTING_WAIT ; 
 int /*<<< orphan*/  CEOUC_NOWAIT ; 
 int /*<<< orphan*/  CEOUC_WAIT ; 
 int /*<<< orphan*/ * ExecPrepareQual (int /*<<< orphan*/ *,TYPE_8__*) ; 
 int /*<<< orphan*/  ExecQual (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  FormIndexDatum (TYPE_6__*,TYPE_2__*,TYPE_8__*,int /*<<< orphan*/ *,int*) ; 
 TYPE_7__* GetPerTupleExprContext (TYPE_8__*) ; 
 int INDEX_MAX_KEYS ; 
 int ItemPointerIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ RelationGetRelid (TYPE_4__*) ; 
 scalar_t__ UNIQUE_CHECK_NO ; 
 scalar_t__ UNIQUE_CHECK_PARTIAL ; 
 scalar_t__ UNIQUE_CHECK_YES ; 
 int check_exclusion_or_unique_constraint (TYPE_4__*,TYPE_4__*,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,TYPE_8__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int index_insert (TYPE_4__*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,TYPE_4__*,scalar_t__,TYPE_6__*) ; 
 int /*<<< orphan*/ * lappend_oid (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ list_member_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

List *
ExecInsertIndexTuples(TupleTableSlot *slot,
					  EState *estate,
					  bool noDupErr,
					  bool *specConflict,
					  List *arbiterIndexes)
{
	ItemPointer tupleid = &slot->tts_tid;
	List	   *result = NIL;
	ResultRelInfo *resultRelInfo;
	int			i;
	int			numIndices;
	RelationPtr relationDescs;
	Relation	heapRelation;
	IndexInfo **indexInfoArray;
	ExprContext *econtext;
	Datum		values[INDEX_MAX_KEYS];
	bool		isnull[INDEX_MAX_KEYS];

	Assert(ItemPointerIsValid(tupleid));

	/*
	 * Get information from the result relation info structure.
	 */
	resultRelInfo = estate->es_result_relation_info;
	numIndices = resultRelInfo->ri_NumIndices;
	relationDescs = resultRelInfo->ri_IndexRelationDescs;
	indexInfoArray = resultRelInfo->ri_IndexRelationInfo;
	heapRelation = resultRelInfo->ri_RelationDesc;

	/* Sanity check: slot must belong to the same rel as the resultRelInfo. */
	Assert(slot->tts_tableOid == RelationGetRelid(heapRelation));

	/*
	 * We will use the EState's per-tuple context for evaluating predicates
	 * and index expressions (creating it if it's not already there).
	 */
	econtext = GetPerTupleExprContext(estate);

	/* Arrange for econtext's scan tuple to be the tuple under test */
	econtext->ecxt_scantuple = slot;

	/*
	 * for each index, form and insert the index tuple
	 */
	for (i = 0; i < numIndices; i++)
	{
		Relation	indexRelation = relationDescs[i];
		IndexInfo  *indexInfo;
		bool		applyNoDupErr;
		IndexUniqueCheck checkUnique;
		bool		satisfiesConstraint;

		if (indexRelation == NULL)
			continue;

		indexInfo = indexInfoArray[i];

		/* If the index is marked as read-only, ignore it */
		if (!indexInfo->ii_ReadyForInserts)
			continue;

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

		/* Check whether to apply noDupErr to this index */
		applyNoDupErr = noDupErr &&
			(arbiterIndexes == NIL ||
			 list_member_oid(arbiterIndexes,
							 indexRelation->rd_index->indexrelid));

		/*
		 * The index AM does the actual insertion, plus uniqueness checking.
		 *
		 * For an immediate-mode unique index, we just tell the index AM to
		 * throw error if not unique.
		 *
		 * For a deferrable unique index, we tell the index AM to just detect
		 * possible non-uniqueness, and we add the index OID to the result
		 * list if further checking is needed.
		 *
		 * For a speculative insertion (used by INSERT ... ON CONFLICT), do
		 * the same as for a deferrable unique index.
		 */
		if (!indexRelation->rd_index->indisunique)
			checkUnique = UNIQUE_CHECK_NO;
		else if (applyNoDupErr)
			checkUnique = UNIQUE_CHECK_PARTIAL;
		else if (indexRelation->rd_index->indimmediate)
			checkUnique = UNIQUE_CHECK_YES;
		else
			checkUnique = UNIQUE_CHECK_PARTIAL;

		satisfiesConstraint =
			index_insert(indexRelation, /* index relation */
						 values,	/* array of index Datums */
						 isnull,	/* null flags */
						 tupleid,	/* tid of heap tuple */
						 heapRelation,	/* heap relation */
						 checkUnique,	/* type of uniqueness check to do */
						 indexInfo);	/* index AM may need this */

		/*
		 * If the index has an associated exclusion constraint, check that.
		 * This is simpler than the process for uniqueness checks since we
		 * always insert first and then check.  If the constraint is deferred,
		 * we check now anyway, but don't throw error on violation or wait for
		 * a conclusive outcome from a concurrent insertion; instead we'll
		 * queue a recheck event.  Similarly, noDupErr callers (speculative
		 * inserters) will recheck later, and wait for a conclusive outcome
		 * then.
		 *
		 * An index for an exclusion constraint can't also be UNIQUE (not an
		 * essential property, we just don't allow it in the grammar), so no
		 * need to preserve the prior state of satisfiesConstraint.
		 */
		if (indexInfo->ii_ExclusionOps != NULL)
		{
			bool		violationOK;
			CEOUC_WAIT_MODE waitMode;

			if (applyNoDupErr)
			{
				violationOK = true;
				waitMode = CEOUC_LIVELOCK_PREVENTING_WAIT;
			}
			else if (!indexRelation->rd_index->indimmediate)
			{
				violationOK = true;
				waitMode = CEOUC_NOWAIT;
			}
			else
			{
				violationOK = false;
				waitMode = CEOUC_WAIT;
			}

			satisfiesConstraint =
				check_exclusion_or_unique_constraint(heapRelation,
													 indexRelation, indexInfo,
													 tupleid, values, isnull,
													 estate, false,
													 waitMode, violationOK, NULL);
		}

		if ((checkUnique == UNIQUE_CHECK_PARTIAL ||
			 indexInfo->ii_ExclusionOps != NULL) &&
			!satisfiesConstraint)
		{
			/*
			 * The tuple potentially violates the uniqueness or exclusion
			 * constraint, so make a note of the index so that we can re-check
			 * it later.  Speculative inserters are told if there was a
			 * speculative conflict, since that always requires a restart.
			 */
			result = lappend_oid(result, RelationGetRelid(indexRelation));
			if (indexRelation->rd_index->indimmediate && specConflict)
				*specConflict = true;
		}
	}

	return result;
}