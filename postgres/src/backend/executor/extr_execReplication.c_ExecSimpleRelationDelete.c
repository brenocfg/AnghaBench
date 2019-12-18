#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  tts_tid; } ;
typedef  TYPE_2__ TupleTableSlot ;
struct TYPE_14__ {int /*<<< orphan*/  es_snapshot; TYPE_3__* es_result_relation_info; } ;
struct TYPE_13__ {TYPE_1__* ri_TrigDesc; int /*<<< orphan*/  ri_RelationDesc; } ;
struct TYPE_11__ {scalar_t__ trig_delete_before_row; } ;
typedef  TYPE_3__ ResultRelInfo ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  TYPE_4__ EState ;
typedef  int /*<<< orphan*/  EPQState ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_DELETE ; 
 int /*<<< orphan*/  CheckCmdReplicaIdentity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecARDeleteTriggers (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecBRDeleteTriggers (TYPE_4__*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_table_tuple_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ExecSimpleRelationDelete(EState *estate, EPQState *epqstate,
						 TupleTableSlot *searchslot)
{
	bool		skip_tuple = false;
	ResultRelInfo *resultRelInfo = estate->es_result_relation_info;
	Relation	rel = resultRelInfo->ri_RelationDesc;
	ItemPointer tid = &searchslot->tts_tid;

	CheckCmdReplicaIdentity(rel, CMD_DELETE);

	/* BEFORE ROW DELETE Triggers */
	if (resultRelInfo->ri_TrigDesc &&
		resultRelInfo->ri_TrigDesc->trig_delete_before_row)
	{
		skip_tuple = !ExecBRDeleteTriggers(estate, epqstate, resultRelInfo,
										   tid, NULL, NULL);

	}

	if (!skip_tuple)
	{
		/* OK, delete the tuple */
		simple_table_tuple_delete(rel, tid, estate->es_snapshot);

		/* AFTER ROW DELETE Triggers */
		ExecARDeleteTriggers(estate, resultRelInfo,
							 tid, NULL, NULL);
	}
}