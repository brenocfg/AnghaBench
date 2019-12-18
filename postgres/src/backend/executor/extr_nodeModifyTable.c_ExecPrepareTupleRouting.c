#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_19__ {int /*<<< orphan*/  attrMap; } ;
typedef  TYPE_4__ TupleConversionMap ;
struct TYPE_23__ {TYPE_5__* es_result_relation_info; } ;
struct TYPE_22__ {TYPE_3__* mt_oc_transition_capture; TYPE_2__* mt_transition_capture; } ;
struct TYPE_21__ {int /*<<< orphan*/ * pi_PartitionTupleSlot; TYPE_4__* pi_RootToPartitionMap; int /*<<< orphan*/ * pi_PartitionToRootMap; } ;
struct TYPE_20__ {TYPE_1__* ri_TrigDesc; TYPE_6__* ri_PartitionInfo; } ;
struct TYPE_18__ {int /*<<< orphan*/ * tcs_map; } ;
struct TYPE_17__ {int /*<<< orphan*/ * tcs_map; int /*<<< orphan*/ * tcs_original_insert_tuple; } ;
struct TYPE_16__ {scalar_t__ trig_insert_before_row; } ;
typedef  TYPE_5__ ResultRelInfo ;
typedef  int /*<<< orphan*/  PartitionTupleRouting ;
typedef  TYPE_6__ PartitionRoutingInfo ;
typedef  TYPE_7__ ModifyTableState ;
typedef  TYPE_8__ EState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 TYPE_5__* ExecFindPartition (TYPE_7__*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_8__*) ; 
 int /*<<< orphan*/ * execute_attr_map_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static TupleTableSlot *
ExecPrepareTupleRouting(ModifyTableState *mtstate,
						EState *estate,
						PartitionTupleRouting *proute,
						ResultRelInfo *targetRelInfo,
						TupleTableSlot *slot)
{
	ResultRelInfo *partrel;
	PartitionRoutingInfo *partrouteinfo;
	TupleConversionMap *map;

	/*
	 * Lookup the target partition's ResultRelInfo.  If ExecFindPartition does
	 * not find a valid partition for the tuple in 'slot' then an error is
	 * raised.  An error may also be raised if the found partition is not a
	 * valid target for INSERTs.  This is required since a partitioned table
	 * UPDATE to another partition becomes a DELETE+INSERT.
	 */
	partrel = ExecFindPartition(mtstate, targetRelInfo, proute, slot, estate);
	partrouteinfo = partrel->ri_PartitionInfo;
	Assert(partrouteinfo != NULL);

	/*
	 * Make it look like we are inserting into the partition.
	 */
	estate->es_result_relation_info = partrel;

	/*
	 * If we're capturing transition tuples, we might need to convert from the
	 * partition rowtype to root partitioned table's rowtype.
	 */
	if (mtstate->mt_transition_capture != NULL)
	{
		if (partrel->ri_TrigDesc &&
			partrel->ri_TrigDesc->trig_insert_before_row)
		{
			/*
			 * If there are any BEFORE triggers on the partition, we'll have
			 * to be ready to convert their result back to tuplestore format.
			 */
			mtstate->mt_transition_capture->tcs_original_insert_tuple = NULL;
			mtstate->mt_transition_capture->tcs_map =
				partrouteinfo->pi_PartitionToRootMap;
		}
		else
		{
			/*
			 * Otherwise, just remember the original unconverted tuple, to
			 * avoid a needless round trip conversion.
			 */
			mtstate->mt_transition_capture->tcs_original_insert_tuple = slot;
			mtstate->mt_transition_capture->tcs_map = NULL;
		}
	}
	if (mtstate->mt_oc_transition_capture != NULL)
	{
		mtstate->mt_oc_transition_capture->tcs_map =
			partrouteinfo->pi_PartitionToRootMap;
	}

	/*
	 * Convert the tuple, if necessary.
	 */
	map = partrouteinfo->pi_RootToPartitionMap;
	if (map != NULL)
	{
		TupleTableSlot *new_slot = partrouteinfo->pi_PartitionTupleSlot;

		slot = execute_attr_map_slot(map->attrMap, slot, new_slot);
	}

	return slot;
}