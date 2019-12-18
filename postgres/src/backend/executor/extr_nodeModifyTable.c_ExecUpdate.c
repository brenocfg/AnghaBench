#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_100__   TYPE_9__ ;
typedef  struct TYPE_99__   TYPE_8__ ;
typedef  struct TYPE_98__   TYPE_81__ ;
typedef  struct TYPE_97__   TYPE_7__ ;
typedef  struct TYPE_96__   TYPE_6__ ;
typedef  struct TYPE_95__   TYPE_5__ ;
typedef  struct TYPE_94__   TYPE_4__ ;
typedef  struct TYPE_93__   TYPE_3__ ;
typedef  struct TYPE_92__   TYPE_2__ ;
typedef  struct TYPE_91__   TYPE_1__ ;
typedef  struct TYPE_90__   TYPE_13__ ;
typedef  struct TYPE_89__   TYPE_12__ ;
typedef  struct TYPE_88__   TYPE_11__ ;
typedef  struct TYPE_87__   TYPE_10__ ;

/* Type definitions */
struct TYPE_96__ {void* tts_tableOid; } ;
typedef  TYPE_6__ TupleTableSlot ;
struct TYPE_97__ {int /*<<< orphan*/  attrMap; } ;
typedef  TYPE_7__ TupleConversionMap ;
struct TYPE_100__ {scalar_t__ ri_NumIndices; scalar_t__ ri_projectReturning; int /*<<< orphan*/ * ri_WithCheckOptions; int /*<<< orphan*/  ri_junkFilter; int /*<<< orphan*/  ri_RangeTableIndex; scalar_t__ ri_PartitionCheck; TYPE_2__* ri_FdwRoutine; TYPE_1__* ri_TrigDesc; TYPE_10__* ri_RelationDesc; } ;
struct TYPE_99__ {int traversed; int /*<<< orphan*/  cmax; } ;
struct TYPE_98__ {TYPE_7__* tcs_map; int /*<<< orphan*/ * tcs_original_insert_tuple; } ;
struct TYPE_95__ {TYPE_4__* constr; } ;
struct TYPE_94__ {scalar_t__ has_generated_stored; } ;
struct TYPE_93__ {scalar_t__ plan; } ;
struct TYPE_92__ {TYPE_6__* (* ExecForeignUpdate ) (TYPE_13__*,TYPE_9__*,TYPE_6__*,TYPE_6__*) ;} ;
struct TYPE_91__ {scalar_t__ trig_update_instead_row; scalar_t__ trig_update_before_row; } ;
struct TYPE_90__ {int /*<<< orphan*/  es_processed; int /*<<< orphan*/  es_output_cid; int /*<<< orphan*/  es_snapshot; int /*<<< orphan*/  es_crosscheck_snapshot; TYPE_9__* es_result_relation_info; } ;
struct TYPE_89__ {scalar_t__ onConflictAction; } ;
struct TYPE_88__ {int mt_nplans; scalar_t__ operation; TYPE_81__* mt_transition_capture; TYPE_81__* mt_oc_transition_capture; int /*<<< orphan*/ * rootResultRelInfo; int /*<<< orphan*/  mt_root_tuple_slot; TYPE_9__* resultRelInfo; TYPE_3__ ps; int /*<<< orphan*/ * mt_partition_tuple_routing; } ;
struct TYPE_87__ {TYPE_5__* rd_att; } ;
typedef  int /*<<< orphan*/  TM_Result ;
typedef  TYPE_8__ TM_FailureData ;
typedef  TYPE_9__ ResultRelInfo ;
typedef  TYPE_10__* Relation ;
typedef  int /*<<< orphan*/  PartitionTupleRouting ;
typedef  TYPE_11__ ModifyTableState ;
typedef  TYPE_12__ ModifyTable ;
typedef  int /*<<< orphan*/  LockTupleMode ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_13__ EState ;
typedef  int /*<<< orphan*/  EPQState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CMD_INSERT ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_TRIGGERED_DATA_CHANGE_VIOLATION ; 
 int /*<<< orphan*/  ERRCODE_T_R_SERIALIZATION_FAILURE ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_6__* EvalPlanQual (int /*<<< orphan*/ *,TYPE_10__*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 TYPE_6__* EvalPlanQualSlot (int /*<<< orphan*/ *,TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecARUpdateTriggers (TYPE_13__*,TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *,TYPE_81__*) ; 
 int /*<<< orphan*/  ExecBRUpdateTriggers (TYPE_13__*,int /*<<< orphan*/ *,TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  ExecComputeStoredGenerated (TYPE_13__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ExecConstraints (TYPE_9__*,TYPE_6__*,TYPE_13__*) ; 
 int /*<<< orphan*/  ExecDelete (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *,TYPE_13__*,int,int,int,int*,TYPE_6__**) ; 
 TYPE_6__* ExecFilterJunk (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  ExecIRUpdateTriggers (TYPE_13__*,TYPE_9__*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 TYPE_6__* ExecInsert (TYPE_11__*,TYPE_6__*,TYPE_6__*,TYPE_13__*,int) ; 
 int /*<<< orphan*/ * ExecInsertIndexTuples (TYPE_6__*,TYPE_13__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecMaterializeSlot (TYPE_6__*) ; 
 int /*<<< orphan*/  ExecPartitionCheck (TYPE_9__*,TYPE_6__*,TYPE_13__*,int) ; 
 int /*<<< orphan*/  ExecPartitionCheckEmitError (TYPE_9__*,TYPE_6__*,TYPE_13__*) ; 
 TYPE_6__* ExecPrepareTupleRouting (TYPE_11__*,TYPE_13__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_6__*) ; 
 TYPE_6__* ExecProcessReturning (TYPE_9__*,TYPE_6__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ExecWithCheckOptions (int /*<<< orphan*/ ,TYPE_9__*,TYPE_6__*,TYPE_13__*) ; 
 scalar_t__ IsBootstrapProcessingMode () ; 
 int /*<<< orphan*/  IsolationUsesXactSnapshot () ; 
 int /*<<< orphan*/  LockWaitBlock ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ ONCONFLICT_UPDATE ; 
 void* RelationGetRelid (TYPE_10__*) ; 
#define  TM_Deleted 131 
#define  TM_Ok 130 
#define  TM_SelfModified 129 
#define  TM_Updated 128 
 int /*<<< orphan*/  TUPLE_LOCK_FLAG_FIND_LAST_VERSION ; 
 scalar_t__ TupIsNull (TYPE_6__*) ; 
 int /*<<< orphan*/  WCO_RLS_UPDATE_CHECK ; 
 int /*<<< orphan*/  WCO_VIEW_CHECK ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 TYPE_6__* execute_attr_map_slot (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ *) ; 
 TYPE_6__* stub1 (TYPE_13__*,TYPE_9__*,TYPE_6__*,TYPE_6__*) ; 
 int /*<<< orphan*/  table_tuple_lock (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/  table_tuple_update (TYPE_10__*,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_8__*,int /*<<< orphan*/ *,int*) ; 
 TYPE_7__* tupconv_map_for_subplan (TYPE_11__*,int) ; 

__attribute__((used)) static TupleTableSlot *
ExecUpdate(ModifyTableState *mtstate,
		   ItemPointer tupleid,
		   HeapTuple oldtuple,
		   TupleTableSlot *slot,
		   TupleTableSlot *planSlot,
		   EPQState *epqstate,
		   EState *estate,
		   bool canSetTag)
{
	ResultRelInfo *resultRelInfo;
	Relation	resultRelationDesc;
	TM_Result	result;
	TM_FailureData tmfd;
	List	   *recheckIndexes = NIL;
	TupleConversionMap *saved_tcs_map = NULL;

	/*
	 * abort the operation if not running transactions
	 */
	if (IsBootstrapProcessingMode())
		elog(ERROR, "cannot UPDATE during bootstrap");

	ExecMaterializeSlot(slot);

	/*
	 * get information on the (current) result relation
	 */
	resultRelInfo = estate->es_result_relation_info;
	resultRelationDesc = resultRelInfo->ri_RelationDesc;

	/* BEFORE ROW UPDATE Triggers */
	if (resultRelInfo->ri_TrigDesc &&
		resultRelInfo->ri_TrigDesc->trig_update_before_row)
	{
		if (!ExecBRUpdateTriggers(estate, epqstate, resultRelInfo,
								  tupleid, oldtuple, slot))
			return NULL;		/* "do nothing" */
	}

	/* INSTEAD OF ROW UPDATE Triggers */
	if (resultRelInfo->ri_TrigDesc &&
		resultRelInfo->ri_TrigDesc->trig_update_instead_row)
	{
		if (!ExecIRUpdateTriggers(estate, resultRelInfo,
								  oldtuple, slot))
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
		 * update in foreign table: let the FDW do it
		 */
		slot = resultRelInfo->ri_FdwRoutine->ExecForeignUpdate(estate,
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
		slot->tts_tableOid = RelationGetRelid(resultRelationDesc);
	}
	else
	{
		LockTupleMode lockmode;
		bool		partition_constraint_failed;
		bool		update_indexes;

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
		 * Check any RLS UPDATE WITH CHECK policies
		 *
		 * If we generate a new candidate tuple after EvalPlanQual testing, we
		 * must loop back here and recheck any RLS policies and constraints.
		 * (We don't need to redo triggers, however.  If there are any BEFORE
		 * triggers then trigger.c will have done table_tuple_lock to lock the
		 * correct tuple, so there's no need to do them again.)
		 */
lreplace:;

		/* ensure slot is independent, consider e.g. EPQ */
		ExecMaterializeSlot(slot);

		/*
		 * If partition constraint fails, this row might get moved to another
		 * partition, in which case we should check the RLS CHECK policy just
		 * before inserting into the new partition, rather than doing it here.
		 * This is because a trigger on that partition might again change the
		 * row.  So skip the WCO checks if the partition constraint fails.
		 */
		partition_constraint_failed =
			resultRelInfo->ri_PartitionCheck &&
			!ExecPartitionCheck(resultRelInfo, slot, estate, false);

		if (!partition_constraint_failed &&
			resultRelInfo->ri_WithCheckOptions != NIL)
		{
			/*
			 * ExecWithCheckOptions() will skip any WCOs which are not of the
			 * kind we are looking for at this point.
			 */
			ExecWithCheckOptions(WCO_RLS_UPDATE_CHECK,
								 resultRelInfo, slot, estate);
		}

		/*
		 * If a partition check failed, try to move the row into the right
		 * partition.
		 */
		if (partition_constraint_failed)
		{
			bool		tuple_deleted;
			TupleTableSlot *ret_slot;
			TupleTableSlot *epqslot = NULL;
			PartitionTupleRouting *proute = mtstate->mt_partition_tuple_routing;
			int			map_index;
			TupleConversionMap *tupconv_map;

			/*
			 * Disallow an INSERT ON CONFLICT DO UPDATE that causes the
			 * original row to migrate to a different partition.  Maybe this
			 * can be implemented some day, but it seems a fringe feature with
			 * little redeeming value.
			 */
			if (((ModifyTable *) mtstate->ps.plan)->onConflictAction == ONCONFLICT_UPDATE)
				ereport(ERROR,
						(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						 errmsg("invalid ON UPDATE specification"),
						 errdetail("The result tuple would appear in a different partition than the original tuple.")));

			/*
			 * When an UPDATE is run on a leaf partition, we will not have
			 * partition tuple routing set up. In that case, fail with
			 * partition constraint violation error.
			 */
			if (proute == NULL)
				ExecPartitionCheckEmitError(resultRelInfo, slot, estate);

			/*
			 * Row movement, part 1.  Delete the tuple, but skip RETURNING
			 * processing. We want to return rows from INSERT.
			 */
			ExecDelete(mtstate, tupleid, oldtuple, planSlot, epqstate,
					   estate, false, false /* canSetTag */ ,
					   true /* changingPart */ , &tuple_deleted, &epqslot);

			/*
			 * For some reason if DELETE didn't happen (e.g. trigger prevented
			 * it, or it was already deleted by self, or it was concurrently
			 * deleted by another transaction), then we should skip the insert
			 * as well; otherwise, an UPDATE could cause an increase in the
			 * total number of rows across all partitions, which is clearly
			 * wrong.
			 *
			 * For a normal UPDATE, the case where the tuple has been the
			 * subject of a concurrent UPDATE or DELETE would be handled by
			 * the EvalPlanQual machinery, but for an UPDATE that we've
			 * translated into a DELETE from this partition and an INSERT into
			 * some other partition, that's not available, because CTID chains
			 * can't span relation boundaries.  We mimic the semantics to a
			 * limited extent by skipping the INSERT if the DELETE fails to
			 * find a tuple. This ensures that two concurrent attempts to
			 * UPDATE the same tuple at the same time can't turn one tuple
			 * into two, and that an UPDATE of a just-deleted tuple can't
			 * resurrect it.
			 */
			if (!tuple_deleted)
			{
				/*
				 * epqslot will be typically NULL.  But when ExecDelete()
				 * finds that another transaction has concurrently updated the
				 * same row, it re-fetches the row, skips the delete, and
				 * epqslot is set to the re-fetched tuple slot. In that case,
				 * we need to do all the checks again.
				 */
				if (TupIsNull(epqslot))
					return NULL;
				else
				{
					slot = ExecFilterJunk(resultRelInfo->ri_junkFilter, epqslot);
					goto lreplace;
				}
			}

			/*
			 * Updates set the transition capture map only when a new subplan
			 * is chosen.  But for inserts, it is set for each row. So after
			 * INSERT, we need to revert back to the map created for UPDATE;
			 * otherwise the next UPDATE will incorrectly use the one created
			 * for INSERT.  So first save the one created for UPDATE.
			 */
			if (mtstate->mt_transition_capture)
				saved_tcs_map = mtstate->mt_transition_capture->tcs_map;

			/*
			 * resultRelInfo is one of the per-subplan resultRelInfos.  So we
			 * should convert the tuple into root's tuple descriptor, since
			 * ExecInsert() starts the search from root.  The tuple conversion
			 * map list is in the order of mtstate->resultRelInfo[], so to
			 * retrieve the one for this resultRel, we need to know the
			 * position of the resultRel in mtstate->resultRelInfo[].
			 */
			map_index = resultRelInfo - mtstate->resultRelInfo;
			Assert(map_index >= 0 && map_index < mtstate->mt_nplans);
			tupconv_map = tupconv_map_for_subplan(mtstate, map_index);
			if (tupconv_map != NULL)
				slot = execute_attr_map_slot(tupconv_map->attrMap,
											 slot,
											 mtstate->mt_root_tuple_slot);

			/*
			 * Prepare for tuple routing, making it look like we're inserting
			 * into the root.
			 */
			Assert(mtstate->rootResultRelInfo != NULL);
			slot = ExecPrepareTupleRouting(mtstate, estate, proute,
										   mtstate->rootResultRelInfo, slot);

			ret_slot = ExecInsert(mtstate, slot, planSlot,
								  estate, canSetTag);

			/* Revert ExecPrepareTupleRouting's node change. */
			estate->es_result_relation_info = resultRelInfo;
			if (mtstate->mt_transition_capture)
			{
				mtstate->mt_transition_capture->tcs_original_insert_tuple = NULL;
				mtstate->mt_transition_capture->tcs_map = saved_tcs_map;
			}

			return ret_slot;
		}

		/*
		 * Check the constraints of the tuple.  We've already checked the
		 * partition constraint above; however, we must still ensure the tuple
		 * passes all other constraints, so we will call ExecConstraints() and
		 * have it validate all remaining checks.
		 */
		if (resultRelationDesc->rd_att->constr)
			ExecConstraints(resultRelInfo, slot, estate);

		/*
		 * replace the heap tuple
		 *
		 * Note: if es_crosscheck_snapshot isn't InvalidSnapshot, we check
		 * that the row to be updated is visible to that snapshot, and throw a
		 * can't-serialize error if not. This is a special-case behavior
		 * needed for referential integrity updates in transaction-snapshot
		 * mode transactions.
		 */
		result = table_tuple_update(resultRelationDesc, tupleid, slot,
									estate->es_output_cid,
									estate->es_snapshot,
									estate->es_crosscheck_snapshot,
									true /* wait for commit */ ,
									&tmfd, &lockmode, &update_indexes);

		switch (result)
		{
			case TM_SelfModified:

				/*
				 * The target tuple was already updated or deleted by the
				 * current command, or by a later command in the current
				 * transaction.  The former case is possible in a join UPDATE
				 * where multiple tuples join to the same target tuple. This
				 * is pretty questionable, but Postgres has always allowed it:
				 * we just execute the first update action and ignore
				 * additional update attempts.
				 *
				 * The latter case arises if the tuple is modified by a
				 * command in a BEFORE trigger, or perhaps by a command in a
				 * volatile function used in the query.  In such situations we
				 * should not ignore the update, but it is equally unsafe to
				 * proceed.  We don't want to discard the original UPDATE
				 * while keeping the triggered actions based on it; and we
				 * have no principled way to merge this update with the
				 * previous ones.  So throwing an error is the only safe
				 * course.
				 *
				 * If a trigger actually intends this type of interaction, it
				 * can re-execute the UPDATE (assuming it can figure out how)
				 * and then return NULL to cancel the outer update.
				 */
				if (tmfd.cmax != estate->es_output_cid)
					ereport(ERROR,
							(errcode(ERRCODE_TRIGGERED_DATA_CHANGE_VIOLATION),
							 errmsg("tuple to be updated was already modified by an operation triggered by the current command"),
							 errhint("Consider using an AFTER trigger instead of a BEFORE trigger to propagate changes to other rows.")));

				/* Else, already updated by self; nothing to do */
				return NULL;

			case TM_Ok:
				break;

			case TM_Updated:
				{
					TupleTableSlot *inputslot;
					TupleTableSlot *epqslot;

					if (IsolationUsesXactSnapshot())
						ereport(ERROR,
								(errcode(ERRCODE_T_R_SERIALIZATION_FAILURE),
								 errmsg("could not serialize access due to concurrent update")));

					/*
					 * Already know that we're going to need to do EPQ, so
					 * fetch tuple directly into the right slot.
					 */
					inputslot = EvalPlanQualSlot(epqstate, resultRelationDesc,
												 resultRelInfo->ri_RangeTableIndex);

					result = table_tuple_lock(resultRelationDesc, tupleid,
											  estate->es_snapshot,
											  inputslot, estate->es_output_cid,
											  lockmode, LockWaitBlock,
											  TUPLE_LOCK_FLAG_FIND_LAST_VERSION,
											  &tmfd);

					switch (result)
					{
						case TM_Ok:
							Assert(tmfd.traversed);

							epqslot = EvalPlanQual(epqstate,
												   resultRelationDesc,
												   resultRelInfo->ri_RangeTableIndex,
												   inputslot);
							if (TupIsNull(epqslot))
								/* Tuple not passing quals anymore, exiting... */
								return NULL;

							slot = ExecFilterJunk(resultRelInfo->ri_junkFilter, epqslot);
							goto lreplace;

						case TM_Deleted:
							/* tuple already deleted; nothing to do */
							return NULL;

						case TM_SelfModified:

							/*
							 * This can be reached when following an update
							 * chain from a tuple updated by another session,
							 * reaching a tuple that was already updated in
							 * this transaction. If previously modified by
							 * this command, ignore the redundant update,
							 * otherwise error out.
							 *
							 * See also TM_SelfModified response to
							 * table_tuple_update() above.
							 */
							if (tmfd.cmax != estate->es_output_cid)
								ereport(ERROR,
										(errcode(ERRCODE_TRIGGERED_DATA_CHANGE_VIOLATION),
										 errmsg("tuple to be updated was already modified by an operation triggered by the current command"),
										 errhint("Consider using an AFTER trigger instead of a BEFORE trigger to propagate changes to other rows.")));
							return NULL;

						default:
							/* see table_tuple_lock call in ExecDelete() */
							elog(ERROR, "unexpected table_tuple_lock status: %u",
								 result);
							return NULL;
					}
				}

				break;

			case TM_Deleted:
				if (IsolationUsesXactSnapshot())
					ereport(ERROR,
							(errcode(ERRCODE_T_R_SERIALIZATION_FAILURE),
							 errmsg("could not serialize access due to concurrent delete")));
				/* tuple already deleted; nothing to do */
				return NULL;

			default:
				elog(ERROR, "unrecognized table_tuple_update status: %u",
					 result);
				return NULL;
		}

		/* insert index entries for tuple if necessary */
		if (resultRelInfo->ri_NumIndices > 0 && update_indexes)
			recheckIndexes = ExecInsertIndexTuples(slot, estate, false, NULL, NIL);
	}

	if (canSetTag)
		(estate->es_processed)++;

	/* AFTER ROW UPDATE Triggers */
	ExecARUpdateTriggers(estate, resultRelInfo, tupleid, oldtuple, slot,
						 recheckIndexes,
						 mtstate->operation == CMD_INSERT ?
						 mtstate->mt_oc_transition_capture :
						 mtstate->mt_transition_capture);

	list_free(recheckIndexes);

	/*
	 * Check any WITH CHECK OPTION constraints from parent views.  We are
	 * required to do this after testing all constraints and uniqueness
	 * violations per the SQL spec, so we do it after actually updating the
	 * record in the heap and all indexes.
	 *
	 * ExecWithCheckOptions() will skip any WCOs which are not of the kind we
	 * are looking for at this point.
	 */
	if (resultRelInfo->ri_WithCheckOptions != NIL)
		ExecWithCheckOptions(WCO_VIEW_CHECK, resultRelInfo, slot, estate);

	/* Process RETURNING if present */
	if (resultRelInfo->ri_projectReturning)
		return ExecProcessReturning(resultRelInfo, slot, planSlot);

	return NULL;
}