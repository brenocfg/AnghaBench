#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_57__   TYPE_8__ ;
typedef  struct TYPE_56__   TYPE_7__ ;
typedef  struct TYPE_55__   TYPE_6__ ;
typedef  struct TYPE_54__   TYPE_5__ ;
typedef  struct TYPE_53__   TYPE_4__ ;
typedef  struct TYPE_52__   TYPE_3__ ;
typedef  struct TYPE_51__   TYPE_2__ ;
typedef  struct TYPE_50__   TYPE_1__ ;

/* Type definitions */
struct TYPE_52__ {int /*<<< orphan*/  tts_tableOid; } ;
typedef  TYPE_3__ TupleTableSlot ;
struct TYPE_53__ {scalar_t__ tcs_update_old_table; } ;
typedef  TYPE_4__ TransitionCaptureState ;
struct TYPE_57__ {int /*<<< orphan*/  es_processed; int /*<<< orphan*/  es_output_cid; int /*<<< orphan*/  es_snapshot; int /*<<< orphan*/  es_crosscheck_snapshot; TYPE_6__* es_result_relation_info; } ;
struct TYPE_56__ {scalar_t__ operation; TYPE_4__* mt_transition_capture; } ;
struct TYPE_55__ {TYPE_2__* ri_FdwRoutine; scalar_t__ ri_projectReturning; int /*<<< orphan*/  ri_RangeTableIndex; TYPE_1__* ri_TrigDesc; int /*<<< orphan*/  ri_RelationDesc; } ;
struct TYPE_54__ {int traversed; int /*<<< orphan*/  cmax; } ;
struct TYPE_51__ {TYPE_3__* (* ExecForeignDelete ) (TYPE_8__*,TYPE_6__*,TYPE_3__*,TYPE_3__*) ;} ;
struct TYPE_50__ {scalar_t__ trig_delete_instead_row; scalar_t__ trig_delete_before_row; } ;
typedef  int TM_Result ;
typedef  TYPE_5__ TM_FailureData ;
typedef  TYPE_6__ ResultRelInfo ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_7__ ModifyTableState ;
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_8__ EState ;
typedef  int /*<<< orphan*/  EPQState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CMD_UPDATE ; 
 int /*<<< orphan*/  ERRCODE_TRIGGERED_DATA_CHANGE_VIOLATION ; 
 int /*<<< orphan*/  ERRCODE_T_R_SERIALIZATION_FAILURE ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_3__* EvalPlanQual (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  EvalPlanQualBegin (int /*<<< orphan*/ *) ; 
 TYPE_3__* EvalPlanQualSlot (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecARDeleteTriggers (TYPE_8__*,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  ExecARUpdateTriggers (TYPE_8__*,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int ExecBRDeleteTriggers (TYPE_8__*,int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__**) ; 
 int /*<<< orphan*/  ExecClearTuple (TYPE_3__*) ; 
 int /*<<< orphan*/  ExecForceStoreHeapTuple (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 TYPE_3__* ExecGetReturningSlot (TYPE_8__*,TYPE_6__*) ; 
 int ExecIRDeleteTriggers (TYPE_8__*,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecMaterializeSlot (TYPE_3__*) ; 
 TYPE_3__* ExecProcessReturning (TYPE_6__*,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ExecStoreAllNullTuple (TYPE_3__*) ; 
 int /*<<< orphan*/  IsolationUsesXactSnapshot () ; 
 int /*<<< orphan*/  LockTupleExclusive ; 
 int /*<<< orphan*/  LockWaitBlock ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SnapshotAny ; 
#define  TM_Deleted 131 
#define  TM_Ok 130 
#define  TM_SelfModified 129 
#define  TM_Updated 128 
 scalar_t__ TTS_EMPTY (TYPE_3__*) ; 
 int /*<<< orphan*/  TUPLE_LOCK_FLAG_FIND_LAST_VERSION ; 
 int /*<<< orphan*/  TupIsNull (TYPE_3__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 TYPE_3__* stub1 (TYPE_8__*,TYPE_6__*,TYPE_3__*,TYPE_3__*) ; 
 int table_tuple_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_5__*,int) ; 
 int /*<<< orphan*/  table_tuple_fetch_row_version (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int table_tuple_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static TupleTableSlot *
ExecDelete(ModifyTableState *mtstate,
		   ItemPointer tupleid,
		   HeapTuple oldtuple,
		   TupleTableSlot *planSlot,
		   EPQState *epqstate,
		   EState *estate,
		   bool processReturning,
		   bool canSetTag,
		   bool changingPart,
		   bool *tupleDeleted,
		   TupleTableSlot **epqreturnslot)
{
	ResultRelInfo *resultRelInfo;
	Relation	resultRelationDesc;
	TM_Result	result;
	TM_FailureData tmfd;
	TupleTableSlot *slot = NULL;
	TransitionCaptureState *ar_delete_trig_tcs;

	if (tupleDeleted)
		*tupleDeleted = false;

	/*
	 * get information on the (current) result relation
	 */
	resultRelInfo = estate->es_result_relation_info;
	resultRelationDesc = resultRelInfo->ri_RelationDesc;

	/* BEFORE ROW DELETE Triggers */
	if (resultRelInfo->ri_TrigDesc &&
		resultRelInfo->ri_TrigDesc->trig_delete_before_row)
	{
		bool		dodelete;

		dodelete = ExecBRDeleteTriggers(estate, epqstate, resultRelInfo,
										tupleid, oldtuple, epqreturnslot);

		if (!dodelete)			/* "do nothing" */
			return NULL;
	}

	/* INSTEAD OF ROW DELETE Triggers */
	if (resultRelInfo->ri_TrigDesc &&
		resultRelInfo->ri_TrigDesc->trig_delete_instead_row)
	{
		bool		dodelete;

		Assert(oldtuple != NULL);
		dodelete = ExecIRDeleteTriggers(estate, resultRelInfo, oldtuple);

		if (!dodelete)			/* "do nothing" */
			return NULL;
	}
	else if (resultRelInfo->ri_FdwRoutine)
	{
		/*
		 * delete from foreign table: let the FDW do it
		 *
		 * We offer the returning slot as a place to store RETURNING data,
		 * although the FDW can return some other slot if it wants.
		 */
		slot = ExecGetReturningSlot(estate, resultRelInfo);
		slot = resultRelInfo->ri_FdwRoutine->ExecForeignDelete(estate,
															   resultRelInfo,
															   slot,
															   planSlot);

		if (slot == NULL)		/* "do nothing" */
			return NULL;

		/*
		 * RETURNING expressions might reference the tableoid column, so
		 * (re)initialize tts_tableOid before evaluating them.
		 */
		if (TTS_EMPTY(slot))
			ExecStoreAllNullTuple(slot);

		slot->tts_tableOid = RelationGetRelid(resultRelationDesc);
	}
	else
	{
		/*
		 * delete the tuple
		 *
		 * Note: if es_crosscheck_snapshot isn't InvalidSnapshot, we check
		 * that the row to be deleted is visible to that snapshot, and throw a
		 * can't-serialize error if not. This is a special-case behavior
		 * needed for referential integrity updates in transaction-snapshot
		 * mode transactions.
		 */
ldelete:;
		result = table_tuple_delete(resultRelationDesc, tupleid,
									estate->es_output_cid,
									estate->es_snapshot,
									estate->es_crosscheck_snapshot,
									true /* wait for commit */ ,
									&tmfd,
									changingPart);

		switch (result)
		{
			case TM_SelfModified:

				/*
				 * The target tuple was already updated or deleted by the
				 * current command, or by a later command in the current
				 * transaction.  The former case is possible in a join DELETE
				 * where multiple tuples join to the same target tuple. This
				 * is somewhat questionable, but Postgres has always allowed
				 * it: we just ignore additional deletion attempts.
				 *
				 * The latter case arises if the tuple is modified by a
				 * command in a BEFORE trigger, or perhaps by a command in a
				 * volatile function used in the query.  In such situations we
				 * should not ignore the deletion, but it is equally unsafe to
				 * proceed.  We don't want to discard the original DELETE
				 * while keeping the triggered actions based on its deletion;
				 * and it would be no better to allow the original DELETE
				 * while discarding updates that it triggered.  The row update
				 * carries some information that might be important according
				 * to business rules; so throwing an error is the only safe
				 * course.
				 *
				 * If a trigger actually intends this type of interaction, it
				 * can re-execute the DELETE and then return NULL to cancel
				 * the outer delete.
				 */
				if (tmfd.cmax != estate->es_output_cid)
					ereport(ERROR,
							(errcode(ERRCODE_TRIGGERED_DATA_CHANGE_VIOLATION),
							 errmsg("tuple to be deleted was already modified by an operation triggered by the current command"),
							 errhint("Consider using an AFTER trigger instead of a BEFORE trigger to propagate changes to other rows.")));

				/* Else, already deleted by self; nothing to do */
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
					EvalPlanQualBegin(epqstate);
					inputslot = EvalPlanQualSlot(epqstate, resultRelationDesc,
												 resultRelInfo->ri_RangeTableIndex);

					result = table_tuple_lock(resultRelationDesc, tupleid,
											  estate->es_snapshot,
											  inputslot, estate->es_output_cid,
											  LockTupleExclusive, LockWaitBlock,
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

							/*
							 * If requested, skip delete and pass back the
							 * updated row.
							 */
							if (epqreturnslot)
							{
								*epqreturnslot = epqslot;
								return NULL;
							}
							else
								goto ldelete;

						case TM_SelfModified:

							/*
							 * This can be reached when following an update
							 * chain from a tuple updated by another session,
							 * reaching a tuple that was already updated in
							 * this transaction. If previously updated by this
							 * command, ignore the delete, otherwise error
							 * out.
							 *
							 * See also TM_SelfModified response to
							 * table_tuple_delete() above.
							 */
							if (tmfd.cmax != estate->es_output_cid)
								ereport(ERROR,
										(errcode(ERRCODE_TRIGGERED_DATA_CHANGE_VIOLATION),
										 errmsg("tuple to be deleted was already modified by an operation triggered by the current command"),
										 errhint("Consider using an AFTER trigger instead of a BEFORE trigger to propagate changes to other rows.")));
							return NULL;

						case TM_Deleted:
							/* tuple already deleted; nothing to do */
							return NULL;

						default:

							/*
							 * TM_Invisible should be impossible because we're
							 * waiting for updated row versions, and would
							 * already have errored out if the first version
							 * is invisible.
							 *
							 * TM_Updated should be impossible, because we're
							 * locking the latest version via
							 * TUPLE_LOCK_FLAG_FIND_LAST_VERSION.
							 */
							elog(ERROR, "unexpected table_tuple_lock status: %u",
								 result);
							return NULL;
					}

					Assert(false);
					break;
				}

			case TM_Deleted:
				if (IsolationUsesXactSnapshot())
					ereport(ERROR,
							(errcode(ERRCODE_T_R_SERIALIZATION_FAILURE),
							 errmsg("could not serialize access due to concurrent delete")));
				/* tuple already deleted; nothing to do */
				return NULL;

			default:
				elog(ERROR, "unrecognized table_tuple_delete status: %u",
					 result);
				return NULL;
		}

		/*
		 * Note: Normally one would think that we have to delete index tuples
		 * associated with the heap tuple now...
		 *
		 * ... but in POSTGRES, we have no need to do this because VACUUM will
		 * take care of it later.  We can't delete index tuples immediately
		 * anyway, since the tuple is still visible to other transactions.
		 */
	}

	if (canSetTag)
		(estate->es_processed)++;

	/* Tell caller that the delete actually happened. */
	if (tupleDeleted)
		*tupleDeleted = true;

	/*
	 * If this delete is the result of a partition key update that moved the
	 * tuple to a new partition, put this row into the transition OLD TABLE,
	 * if there is one. We need to do this separately for DELETE and INSERT
	 * because they happen on different tables.
	 */
	ar_delete_trig_tcs = mtstate->mt_transition_capture;
	if (mtstate->operation == CMD_UPDATE && mtstate->mt_transition_capture
		&& mtstate->mt_transition_capture->tcs_update_old_table)
	{
		ExecARUpdateTriggers(estate, resultRelInfo,
							 tupleid,
							 oldtuple,
							 NULL,
							 NULL,
							 mtstate->mt_transition_capture);

		/*
		 * We've already captured the NEW TABLE row, so make sure any AR
		 * DELETE trigger fired below doesn't capture it again.
		 */
		ar_delete_trig_tcs = NULL;
	}

	/* AFTER ROW DELETE Triggers */
	ExecARDeleteTriggers(estate, resultRelInfo, tupleid, oldtuple,
						 ar_delete_trig_tcs);

	/* Process RETURNING if present and if requested */
	if (processReturning && resultRelInfo->ri_projectReturning)
	{
		/*
		 * We have to put the target tuple into a slot, which means first we
		 * gotta fetch it.  We can use the trigger tuple slot.
		 */
		TupleTableSlot *rslot;

		if (resultRelInfo->ri_FdwRoutine)
		{
			/* FDW must have provided a slot containing the deleted row */
			Assert(!TupIsNull(slot));
		}
		else
		{
			slot = ExecGetReturningSlot(estate, resultRelInfo);
			if (oldtuple != NULL)
			{
				ExecForceStoreHeapTuple(oldtuple, slot, false);
			}
			else
			{
				if (!table_tuple_fetch_row_version(resultRelationDesc, tupleid,
												   SnapshotAny, slot))
					elog(ERROR, "failed to fetch deleted tuple for DELETE RETURNING");
			}
		}

		rslot = ExecProcessReturning(resultRelInfo, slot, planSlot);

		/*
		 * Before releasing the target tuple again, make sure rslot has a
		 * local copy of any pass-by-reference values.
		 */
		ExecMaterializeSlot(rslot);

		ExecClearTuple(slot);

		return rslot;
	}

	return NULL;
}