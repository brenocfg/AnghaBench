#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  es_tupleTable; } ;
struct TYPE_22__ {scalar_t__ mt_oc_transition_capture; scalar_t__ mt_transition_capture; } ;
struct TYPE_21__ {int* indexes; } ;
struct TYPE_20__ {int /*<<< orphan*/ * pi_PartitionToRootMap; int /*<<< orphan*/ * pi_PartitionTupleSlot; int /*<<< orphan*/ * pi_RootToPartitionMap; } ;
struct TYPE_19__ {int num_partitions; int max_partitions; TYPE_2__** partitions; int /*<<< orphan*/  memcxt; } ;
struct TYPE_18__ {int /*<<< orphan*/ * ri_CopyMultiInsertBuffer; TYPE_4__* ri_PartitionInfo; TYPE_1__* ri_FdwRoutine; int /*<<< orphan*/  ri_PartitionRoot; int /*<<< orphan*/  ri_RelationDesc; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* BeginForeignInsert ) (TYPE_6__*,TYPE_2__*) ;} ;
typedef  TYPE_2__ ResultRelInfo ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_3__ PartitionTupleRouting ;
typedef  TYPE_4__ PartitionRoutingInfo ;
typedef  TYPE_5__* PartitionDispatch ;
typedef  TYPE_6__ ModifyTableState ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_7__ EState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 void* convert_tuples_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* palloc (int) ; 
 scalar_t__ repalloc (TYPE_2__**,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,TYPE_2__*) ; 
 int /*<<< orphan*/ * table_slot_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ExecInitRoutingInfo(ModifyTableState *mtstate,
					EState *estate,
					PartitionTupleRouting *proute,
					PartitionDispatch dispatch,
					ResultRelInfo *partRelInfo,
					int partidx)
{
	MemoryContext oldcxt;
	PartitionRoutingInfo *partrouteinfo;
	int			rri_index;

	oldcxt = MemoryContextSwitchTo(proute->memcxt);

	partrouteinfo = palloc(sizeof(PartitionRoutingInfo));

	/*
	 * Set up a tuple conversion map to convert a tuple routed to the
	 * partition from the parent's type to the partition's.
	 */
	partrouteinfo->pi_RootToPartitionMap =
		convert_tuples_by_name(RelationGetDescr(partRelInfo->ri_PartitionRoot),
							   RelationGetDescr(partRelInfo->ri_RelationDesc));

	/*
	 * If a partition has a different rowtype than the root parent, initialize
	 * a slot dedicated to storing this partition's tuples.  The slot is used
	 * for various operations that are applied to tuples after routing, such
	 * as checking constraints.
	 */
	if (partrouteinfo->pi_RootToPartitionMap != NULL)
	{
		Relation	partrel = partRelInfo->ri_RelationDesc;

		/*
		 * Initialize the slot itself setting its descriptor to this
		 * partition's TupleDesc; TupleDesc reference will be released at the
		 * end of the command.
		 */
		partrouteinfo->pi_PartitionTupleSlot =
			table_slot_create(partrel, &estate->es_tupleTable);
	}
	else
		partrouteinfo->pi_PartitionTupleSlot = NULL;

	/*
	 * Also, if transition capture is required, store a map to convert tuples
	 * from partition's rowtype to the root partition table's.
	 */
	if (mtstate &&
		(mtstate->mt_transition_capture || mtstate->mt_oc_transition_capture))
	{
		partrouteinfo->pi_PartitionToRootMap =
			convert_tuples_by_name(RelationGetDescr(partRelInfo->ri_RelationDesc),
								   RelationGetDescr(partRelInfo->ri_PartitionRoot));
	}
	else
		partrouteinfo->pi_PartitionToRootMap = NULL;

	/*
	 * If the partition is a foreign table, let the FDW init itself for
	 * routing tuples to the partition.
	 */
	if (partRelInfo->ri_FdwRoutine != NULL &&
		partRelInfo->ri_FdwRoutine->BeginForeignInsert != NULL)
		partRelInfo->ri_FdwRoutine->BeginForeignInsert(mtstate, partRelInfo);

	partRelInfo->ri_PartitionInfo = partrouteinfo;
	partRelInfo->ri_CopyMultiInsertBuffer = NULL;

	/*
	 * Keep track of it in the PartitionTupleRouting->partitions array.
	 */
	Assert(dispatch->indexes[partidx] == -1);

	rri_index = proute->num_partitions++;

	/* Allocate or enlarge the array, as needed */
	if (proute->num_partitions >= proute->max_partitions)
	{
		if (proute->max_partitions == 0)
		{
			proute->max_partitions = 8;
			proute->partitions = (ResultRelInfo **)
				palloc(sizeof(ResultRelInfo *) * proute->max_partitions);
		}
		else
		{
			proute->max_partitions *= 2;
			proute->partitions = (ResultRelInfo **)
				repalloc(proute->partitions, sizeof(ResultRelInfo *) *
						 proute->max_partitions);
		}
	}

	proute->partitions[rri_index] = partRelInfo;
	dispatch->indexes[partidx] = rri_index;

	MemoryContextSwitchTo(oldcxt);
}