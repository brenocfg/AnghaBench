#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_85__   TYPE_9__ ;
typedef  struct TYPE_84__   TYPE_8__ ;
typedef  struct TYPE_83__   TYPE_7__ ;
typedef  struct TYPE_82__   TYPE_6__ ;
typedef  struct TYPE_81__   TYPE_5__ ;
typedef  struct TYPE_80__   TYPE_4__ ;
typedef  struct TYPE_79__   TYPE_3__ ;
typedef  struct TYPE_78__   TYPE_2__ ;
typedef  struct TYPE_77__   TYPE_24__ ;
typedef  struct TYPE_76__   TYPE_1__ ;
typedef  struct TYPE_75__   TYPE_11__ ;
typedef  struct TYPE_74__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  WCOKind ;
struct TYPE_81__ {int /*<<< orphan*/  tts_tid; void* tts_tableOid; } ;
typedef  TYPE_5__ TupleTableSlot ;
struct TYPE_82__ {scalar_t__ tcs_update_new_table; } ;
typedef  TYPE_6__ TransitionCaptureState ;
struct TYPE_77__ {scalar_t__ plan; } ;
struct TYPE_85__ {scalar_t__ operation; TYPE_6__* mt_transition_capture; TYPE_24__ ps; } ;
struct TYPE_84__ {TYPE_3__* rd_att; } ;
struct TYPE_83__ {scalar_t__ ri_NumIndices; scalar_t__ ri_projectReturning; int /*<<< orphan*/ * ri_WithCheckOptions; int /*<<< orphan*/ * ri_onConflictArbiterIndexes; TYPE_4__* ri_TrigDesc; int /*<<< orphan*/ * ri_PartitionRoot; scalar_t__ ri_PartitionCheck; TYPE_8__* ri_RelationDesc; TYPE_1__* ri_FdwRoutine; } ;
struct TYPE_80__ {scalar_t__ trig_insert_before_row; scalar_t__ trig_insert_instead_row; } ;
struct TYPE_79__ {TYPE_2__* constr; } ;
struct TYPE_78__ {scalar_t__ has_generated_stored; } ;
struct TYPE_76__ {TYPE_5__* (* ExecForeignInsert ) (TYPE_11__*,TYPE_7__*,TYPE_5__*,TYPE_5__*) ;} ;
struct TYPE_75__ {int /*<<< orphan*/  es_processed; int /*<<< orphan*/  es_output_cid; TYPE_7__* es_result_relation_info; } ;
struct TYPE_74__ {scalar_t__ onConflictAction; } ;
typedef  TYPE_7__ ResultRelInfo ;
typedef  TYPE_8__* Relation ;
typedef  scalar_t__ OnConflictAction ;
typedef  TYPE_9__ ModifyTableState ;
typedef  TYPE_10__ ModifyTable ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  TYPE_11__ EState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CMD_UPDATE ; 
 int /*<<< orphan*/  ExecARInsertTriggers (TYPE_11__*,TYPE_7__*,TYPE_5__*,int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  ExecARUpdateTriggers (TYPE_11__*,TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  ExecBRInsertTriggers (TYPE_11__*,TYPE_7__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ExecCheckIndexConstraints (TYPE_5__*,TYPE_11__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecCheckTIDVisible (TYPE_11__*,TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecComputeStoredGenerated (TYPE_11__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ExecConstraints (TYPE_7__*,TYPE_5__*,TYPE_11__*) ; 
 int /*<<< orphan*/  ExecGetReturningSlot (TYPE_11__*,TYPE_7__*) ; 
 int /*<<< orphan*/  ExecIRInsertTriggers (TYPE_11__*,TYPE_7__*,TYPE_5__*) ; 
 int /*<<< orphan*/ * ExecInsertIndexTuples (TYPE_5__*,TYPE_11__*,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecMaterializeSlot (TYPE_5__*) ; 
 scalar_t__ ExecOnConflictUpdate (TYPE_9__*,TYPE_7__*,int /*<<< orphan*/ *,TYPE_5__*,TYPE_5__*,TYPE_11__*,int,TYPE_5__**) ; 
 int /*<<< orphan*/  ExecPartitionCheck (TYPE_7__*,TYPE_5__*,TYPE_11__*,int) ; 
 TYPE_5__* ExecProcessReturning (TYPE_7__*,TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ExecWithCheckOptions (int /*<<< orphan*/ ,TYPE_7__*,TYPE_5__*,TYPE_11__*) ; 
 int /*<<< orphan*/  GetCurrentTransactionId () ; 
 int /*<<< orphan*/  InstrCountTuples2 (TYPE_24__*,int) ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ ONCONFLICT_NONE ; 
 scalar_t__ ONCONFLICT_NOTHING ; 
 scalar_t__ ONCONFLICT_UPDATE ; 
 void* RelationGetRelid (TYPE_8__*) ; 
 int /*<<< orphan*/  SpeculativeInsertionLockAcquire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpeculativeInsertionLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WCO_RLS_INSERT_CHECK ; 
 int /*<<< orphan*/  WCO_RLS_UPDATE_CHECK ; 
 int /*<<< orphan*/  WCO_VIEW_CHECK ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setLastTid (int /*<<< orphan*/ *) ; 
 TYPE_5__* stub1 (TYPE_11__*,TYPE_7__*,TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  table_tuple_complete_speculative (TYPE_8__*,TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  table_tuple_insert (TYPE_8__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_tuple_insert_speculative (TYPE_8__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static TupleTableSlot *
ExecInsert(ModifyTableState *mtstate,
		   TupleTableSlot *slot,
		   TupleTableSlot *planSlot,
		   EState *estate,
		   bool canSetTag)
{
	ResultRelInfo *resultRelInfo;
	Relation	resultRelationDesc;
	List	   *recheckIndexes = NIL;
	TupleTableSlot *result = NULL;
	TransitionCaptureState *ar_insert_trig_tcs;
	ModifyTable *node = (ModifyTable *) mtstate->ps.plan;
	OnConflictAction onconflict = node->onConflictAction;

	ExecMaterializeSlot(slot);

	/*
	 * get information on the (current) result relation
	 */
	resultRelInfo = estate->es_result_relation_info;
	resultRelationDesc = resultRelInfo->ri_RelationDesc;

	/*
	 * BEFORE ROW INSERT Triggers.
	 *
	 * Note: We fire BEFORE ROW TRIGGERS for every attempted insertion in an
	 * INSERT ... ON CONFLICT statement.  We cannot check for constraint
	 * violations before firing these triggers, because they can change the
	 * values to insert.  Also, they can run arbitrary user-defined code with
	 * side-effects that we can't cancel by just not inserting the tuple.
	 */
	if (resultRelInfo->ri_TrigDesc &&
		resultRelInfo->ri_TrigDesc->trig_insert_before_row)
	{
		if (!ExecBRInsertTriggers(estate, resultRelInfo, slot))
			return NULL;		/* "do nothing" */
	}

	/* INSTEAD OF ROW INSERT Triggers */
	if (resultRelInfo->ri_TrigDesc &&
		resultRelInfo->ri_TrigDesc->trig_insert_instead_row)
	{
		if (!ExecIRInsertTriggers(estate, resultRelInfo, slot))
			return NULL;		/* "do nothing" */
	}
	else if (resultRelInfo->ri_FdwRoutine)
	{
		/*
		 * Compute stored generated columns
		 */
		if (resultRelationDesc->rd_att->constr &&
			resultRelationDesc->rd_att->constr->has_generated_stored)
			ExecComputeStoredGenerated(estate, slot);

		/*
		 * insert into foreign table: let the FDW do it
		 */
		slot = resultRelInfo->ri_FdwRoutine->ExecForeignInsert(estate,
															   resultRelInfo,
															   slot,
															   planSlot);

		if (slot == NULL)		/* "do nothing" */
			return NULL;

		/*
		 * AFTER ROW Triggers or RETURNING expressions might reference the
		 * tableoid column, so (re-)initialize tts_tableOid before evaluating
		 * them.
		 */
		slot->tts_tableOid = RelationGetRelid(resultRelInfo->ri_RelationDesc);

	}
	else
	{
		WCOKind		wco_kind;

		/*
		 * Constraints might reference the tableoid column, so (re-)initialize
		 * tts_tableOid before evaluating them.
		 */
		slot->tts_tableOid = RelationGetRelid(resultRelationDesc);

		/*
		 * Compute stored generated columns
		 */
		if (resultRelationDesc->rd_att->constr &&
			resultRelationDesc->rd_att->constr->has_generated_stored)
			ExecComputeStoredGenerated(estate, slot);

		/*
		 * Check any RLS WITH CHECK policies.
		 *
		 * Normally we should check INSERT policies. But if the insert is the
		 * result of a partition key update that moved the tuple to a new
		 * partition, we should instead check UPDATE policies, because we are
		 * executing policies defined on the target table, and not those
		 * defined on the child partitions.
		 */
		wco_kind = (mtstate->operation == CMD_UPDATE) ?
			WCO_RLS_UPDATE_CHECK : WCO_RLS_INSERT_CHECK;

		/*
		 * ExecWithCheckOptions() will skip any WCOs which are not of the kind
		 * we are looking for at this point.
		 */
		if (resultRelInfo->ri_WithCheckOptions != NIL)
			ExecWithCheckOptions(wco_kind, resultRelInfo, slot, estate);

		/*
		 * Check the constraints of the tuple.
		 */
		if (resultRelationDesc->rd_att->constr)
			ExecConstraints(resultRelInfo, slot, estate);

		/*
		 * Also check the tuple against the partition constraint, if there is
		 * one; except that if we got here via tuple-routing, we don't need to
		 * if there's no BR trigger defined on the partition.
		 */
		if (resultRelInfo->ri_PartitionCheck &&
			(resultRelInfo->ri_PartitionRoot == NULL ||
			 (resultRelInfo->ri_TrigDesc &&
			  resultRelInfo->ri_TrigDesc->trig_insert_before_row)))
			ExecPartitionCheck(resultRelInfo, slot, estate, true);

		if (onconflict != ONCONFLICT_NONE && resultRelInfo->ri_NumIndices > 0)
		{
			/* Perform a speculative insertion. */
			uint32		specToken;
			ItemPointerData conflictTid;
			bool		specConflict;
			List	   *arbiterIndexes;

			arbiterIndexes = resultRelInfo->ri_onConflictArbiterIndexes;

			/*
			 * Do a non-conclusive check for conflicts first.
			 *
			 * We're not holding any locks yet, so this doesn't guarantee that
			 * the later insert won't conflict.  But it avoids leaving behind
			 * a lot of canceled speculative insertions, if you run a lot of
			 * INSERT ON CONFLICT statements that do conflict.
			 *
			 * We loop back here if we find a conflict below, either during
			 * the pre-check, or when we re-check after inserting the tuple
			 * speculatively.
			 */
	vlock:
			specConflict = false;
			if (!ExecCheckIndexConstraints(slot, estate, &conflictTid,
										   arbiterIndexes))
			{
				/* committed conflict tuple found */
				if (onconflict == ONCONFLICT_UPDATE)
				{
					/*
					 * In case of ON CONFLICT DO UPDATE, execute the UPDATE
					 * part.  Be prepared to retry if the UPDATE fails because
					 * of another concurrent UPDATE/DELETE to the conflict
					 * tuple.
					 */
					TupleTableSlot *returning = NULL;

					if (ExecOnConflictUpdate(mtstate, resultRelInfo,
											 &conflictTid, planSlot, slot,
											 estate, canSetTag, &returning))
					{
						InstrCountTuples2(&mtstate->ps, 1);
						return returning;
					}
					else
						goto vlock;
				}
				else
				{
					/*
					 * In case of ON CONFLICT DO NOTHING, do nothing. However,
					 * verify that the tuple is visible to the executor's MVCC
					 * snapshot at higher isolation levels.
					 *
					 * Using ExecGetReturningSlot() to store the tuple for the
					 * recheck isn't that pretty, but we can't trivially use
					 * the input slot, because it might not be of a compatible
					 * type. As there's no conflicting usage of
					 * ExecGetReturningSlot() in the DO NOTHING case...
					 */
					Assert(onconflict == ONCONFLICT_NOTHING);
					ExecCheckTIDVisible(estate, resultRelInfo, &conflictTid,
										ExecGetReturningSlot(estate, resultRelInfo));
					InstrCountTuples2(&mtstate->ps, 1);
					return NULL;
				}
			}

			/*
			 * Before we start insertion proper, acquire our "speculative
			 * insertion lock".  Others can use that to wait for us to decide
			 * if we're going to go ahead with the insertion, instead of
			 * waiting for the whole transaction to complete.
			 */
			specToken = SpeculativeInsertionLockAcquire(GetCurrentTransactionId());

			/* insert the tuple, with the speculative token */
			table_tuple_insert_speculative(resultRelationDesc, slot,
										   estate->es_output_cid,
										   0,
										   NULL,
										   specToken);

			/* insert index entries for tuple */
			recheckIndexes = ExecInsertIndexTuples(slot, estate, true,
												   &specConflict,
												   arbiterIndexes);

			/* adjust the tuple's state accordingly */
			table_tuple_complete_speculative(resultRelationDesc, slot,
											 specToken, !specConflict);

			/*
			 * Wake up anyone waiting for our decision.  They will re-check
			 * the tuple, see that it's no longer speculative, and wait on our
			 * XID as if this was a regularly inserted tuple all along.  Or if
			 * we killed the tuple, they will see it's dead, and proceed as if
			 * the tuple never existed.
			 */
			SpeculativeInsertionLockRelease(GetCurrentTransactionId());

			/*
			 * If there was a conflict, start from the beginning.  We'll do
			 * the pre-check again, which will now find the conflicting tuple
			 * (unless it aborts before we get there).
			 */
			if (specConflict)
			{
				list_free(recheckIndexes);
				goto vlock;
			}

			/* Since there was no insertion conflict, we're done */
		}
		else
		{
			/* insert the tuple normally */
			table_tuple_insert(resultRelationDesc, slot,
							   estate->es_output_cid,
							   0, NULL);

			/* insert index entries for tuple */
			if (resultRelInfo->ri_NumIndices > 0)
				recheckIndexes = ExecInsertIndexTuples(slot, estate, false, NULL,
													   NIL);
		}
	}

	if (canSetTag)
	{
		(estate->es_processed)++;
		setLastTid(&slot->tts_tid);
	}

	/*
	 * If this insert is the result of a partition key update that moved the
	 * tuple to a new partition, put this row into the transition NEW TABLE,
	 * if there is one. We need to do this separately for DELETE and INSERT
	 * because they happen on different tables.
	 */
	ar_insert_trig_tcs = mtstate->mt_transition_capture;
	if (mtstate->operation == CMD_UPDATE && mtstate->mt_transition_capture
		&& mtstate->mt_transition_capture->tcs_update_new_table)
	{
		ExecARUpdateTriggers(estate, resultRelInfo, NULL,
							 NULL,
							 slot,
							 NULL,
							 mtstate->mt_transition_capture);

		/*
		 * We've already captured the NEW TABLE row, so make sure any AR
		 * INSERT trigger fired below doesn't capture it again.
		 */
		ar_insert_trig_tcs = NULL;
	}

	/* AFTER ROW INSERT Triggers */
	ExecARInsertTriggers(estate, resultRelInfo, slot, recheckIndexes,
						 ar_insert_trig_tcs);

	list_free(recheckIndexes);

	/*
	 * Check any WITH CHECK OPTION constraints from parent views.  We are
	 * required to do this after testing all constraints and uniqueness
	 * violations per the SQL spec, so we do it after actually inserting the
	 * record into the heap and all indexes.
	 *
	 * ExecWithCheckOptions will elog(ERROR) if a violation is found, so the
	 * tuple will never be seen, if it violates the WITH CHECK OPTION.
	 *
	 * ExecWithCheckOptions() will skip any WCOs which are not of the kind we
	 * are looking for at this point.
	 */
	if (resultRelInfo->ri_WithCheckOptions != NIL)
		ExecWithCheckOptions(WCO_VIEW_CHECK, resultRelInfo, slot, estate);

	/* Process RETURNING if present */
	if (resultRelInfo->ri_projectReturning)
		result = ExecProcessReturning(resultRelInfo, slot, planSlot);

	return result;
}