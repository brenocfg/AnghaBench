#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_8__ ;
typedef  struct TYPE_37__   TYPE_7__ ;
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
struct TYPE_35__ {int /*<<< orphan*/  tts_tid; } ;
typedef  TYPE_5__ TupleTableSlot ;
struct TYPE_38__ {int /*<<< orphan*/  es_snapshot; TYPE_6__* es_result_relation_info; } ;
struct TYPE_37__ {TYPE_4__* rd_att; TYPE_1__* rd_rel; } ;
struct TYPE_36__ {scalar_t__ ri_NumIndices; scalar_t__ ri_PartitionCheck; TYPE_2__* ri_TrigDesc; TYPE_7__* ri_RelationDesc; } ;
struct TYPE_34__ {TYPE_3__* constr; } ;
struct TYPE_33__ {scalar_t__ has_generated_stored; } ;
struct TYPE_32__ {scalar_t__ trig_update_before_row; } ;
struct TYPE_31__ {scalar_t__ relkind; } ;
typedef  TYPE_6__ ResultRelInfo ;
typedef  TYPE_7__* Relation ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  TYPE_8__ EState ;
typedef  int /*<<< orphan*/  EPQState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CMD_UPDATE ; 
 int /*<<< orphan*/  CheckCmdReplicaIdentity (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecARUpdateTriggers (TYPE_8__*,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecBRUpdateTriggers (TYPE_8__*,int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  ExecComputeStoredGenerated (TYPE_8__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ExecConstraints (TYPE_6__*,TYPE_5__*,TYPE_8__*) ; 
 int /*<<< orphan*/ * ExecInsertIndexTuples (TYPE_5__*,TYPE_8__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecPartitionCheck (TYPE_6__*,TYPE_5__*,TYPE_8__*,int) ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ RELKIND_RELATION ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_table_tuple_update (TYPE_7__*,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ,int*) ; 

void
ExecSimpleRelationUpdate(EState *estate, EPQState *epqstate,
						 TupleTableSlot *searchslot, TupleTableSlot *slot)
{
	bool		skip_tuple = false;
	ResultRelInfo *resultRelInfo = estate->es_result_relation_info;
	Relation	rel = resultRelInfo->ri_RelationDesc;
	ItemPointer tid = &(searchslot->tts_tid);

	/* For now we support only tables. */
	Assert(rel->rd_rel->relkind == RELKIND_RELATION);

	CheckCmdReplicaIdentity(rel, CMD_UPDATE);

	/* BEFORE ROW UPDATE Triggers */
	if (resultRelInfo->ri_TrigDesc &&
		resultRelInfo->ri_TrigDesc->trig_update_before_row)
	{
		if (!ExecBRUpdateTriggers(estate, epqstate, resultRelInfo,
								  tid, NULL, slot))
			skip_tuple = true;	/* "do nothing" */
	}

	if (!skip_tuple)
	{
		List	   *recheckIndexes = NIL;
		bool		update_indexes;

		/* Compute stored generated columns */
		if (rel->rd_att->constr &&
			rel->rd_att->constr->has_generated_stored)
			ExecComputeStoredGenerated(estate, slot);

		/* Check the constraints of the tuple */
		if (rel->rd_att->constr)
			ExecConstraints(resultRelInfo, slot, estate);
		if (resultRelInfo->ri_PartitionCheck)
			ExecPartitionCheck(resultRelInfo, slot, estate, true);

		simple_table_tuple_update(rel, tid, slot, estate->es_snapshot,
								  &update_indexes);

		if (resultRelInfo->ri_NumIndices > 0 && update_indexes)
			recheckIndexes = ExecInsertIndexTuples(slot, estate, false, NULL,
												   NIL);

		/* AFTER ROW UPDATE Triggers */
		ExecARUpdateTriggers(estate, resultRelInfo,
							 tid, NULL, slot,
							 recheckIndexes, NULL);

		list_free(recheckIndexes);
	}
}