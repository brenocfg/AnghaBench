#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_27__ {TYPE_5__* es_result_relation_info; } ;
struct TYPE_26__ {TYPE_4__* rd_att; TYPE_1__* rd_rel; } ;
struct TYPE_25__ {scalar_t__ ri_NumIndices; TYPE_6__* ri_RelationDesc; scalar_t__ ri_PartitionCheck; TYPE_2__* ri_TrigDesc; } ;
struct TYPE_24__ {TYPE_3__* constr; } ;
struct TYPE_23__ {scalar_t__ has_generated_stored; } ;
struct TYPE_22__ {scalar_t__ trig_insert_before_row; } ;
struct TYPE_21__ {scalar_t__ relkind; } ;
typedef  TYPE_5__ ResultRelInfo ;
typedef  TYPE_6__* Relation ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_7__ EState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CMD_INSERT ; 
 int /*<<< orphan*/  CheckCmdReplicaIdentity (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecARInsertTriggers (TYPE_7__*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecBRInsertTriggers (TYPE_7__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecComputeStoredGenerated (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecConstraints (TYPE_5__*,int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/ * ExecInsertIndexTuples (int /*<<< orphan*/ *,TYPE_7__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecPartitionCheck (TYPE_5__*,int /*<<< orphan*/ *,TYPE_7__*,int) ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ RELKIND_RELATION ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_table_tuple_insert (TYPE_6__*,int /*<<< orphan*/ *) ; 

void
ExecSimpleRelationInsert(EState *estate, TupleTableSlot *slot)
{
	bool		skip_tuple = false;
	ResultRelInfo *resultRelInfo = estate->es_result_relation_info;
	Relation	rel = resultRelInfo->ri_RelationDesc;

	/* For now we support only tables. */
	Assert(rel->rd_rel->relkind == RELKIND_RELATION);

	CheckCmdReplicaIdentity(rel, CMD_INSERT);

	/* BEFORE ROW INSERT Triggers */
	if (resultRelInfo->ri_TrigDesc &&
		resultRelInfo->ri_TrigDesc->trig_insert_before_row)
	{
		if (!ExecBRInsertTriggers(estate, resultRelInfo, slot))
			skip_tuple = true;	/* "do nothing" */
	}

	if (!skip_tuple)
	{
		List	   *recheckIndexes = NIL;

		/* Compute stored generated columns */
		if (rel->rd_att->constr &&
			rel->rd_att->constr->has_generated_stored)
			ExecComputeStoredGenerated(estate, slot);

		/* Check the constraints of the tuple */
		if (rel->rd_att->constr)
			ExecConstraints(resultRelInfo, slot, estate);
		if (resultRelInfo->ri_PartitionCheck)
			ExecPartitionCheck(resultRelInfo, slot, estate, true);

		/* OK, store the tuple and create index entries for it */
		simple_table_tuple_insert(resultRelInfo->ri_RelationDesc, slot);

		if (resultRelInfo->ri_NumIndices > 0)
			recheckIndexes = ExecInsertIndexTuples(slot, estate, false, NULL,
												   NIL);

		/* AFTER ROW INSERT Triggers */
		ExecARInsertTriggers(estate, resultRelInfo, slot,
							 recheckIndexes, NULL);

		/*
		 * XXX we should in theory pass a TransitionCaptureState object to the
		 * above to capture transition tuples, but after statement triggers
		 * don't actually get fired by replication yet anyway
		 */

		list_free(recheckIndexes);
	}
}