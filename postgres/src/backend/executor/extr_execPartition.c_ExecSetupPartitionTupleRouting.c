#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ operation; } ;
struct TYPE_10__ {scalar_t__ plan; } ;
struct TYPE_12__ {TYPE_1__ ps; } ;
struct TYPE_11__ {int /*<<< orphan*/  memcxt; int /*<<< orphan*/  partition_root; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_2__ PartitionTupleRouting ;
typedef  TYPE_3__ ModifyTableState ;
typedef  TYPE_4__ ModifyTable ;
typedef  int /*<<< orphan*/  EState ;

/* Variables and functions */
 scalar_t__ CMD_UPDATE ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  ExecHashSubPlanResultRelsByOid (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ExecInitPartitionDispatchInfo (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 scalar_t__ palloc0 (int) ; 

PartitionTupleRouting *
ExecSetupPartitionTupleRouting(EState *estate, ModifyTableState *mtstate,
							   Relation rel)
{
	PartitionTupleRouting *proute;
	ModifyTable *node = mtstate ? (ModifyTable *) mtstate->ps.plan : NULL;

	/*
	 * Here we attempt to expend as little effort as possible in setting up
	 * the PartitionTupleRouting.  Each partition's ResultRelInfo is built on
	 * demand, only when we actually need to route a tuple to that partition.
	 * The reason for this is that a common case is for INSERT to insert a
	 * single tuple into a partitioned table and this must be fast.
	 */
	proute = (PartitionTupleRouting *) palloc0(sizeof(PartitionTupleRouting));
	proute->partition_root = rel;
	proute->memcxt = CurrentMemoryContext;
	/* Rest of members initialized by zeroing */

	/*
	 * Initialize this table's PartitionDispatch object.  Here we pass in the
	 * parent as NULL as we don't need to care about any parent of the target
	 * partitioned table.
	 */
	ExecInitPartitionDispatchInfo(estate, proute, RelationGetRelid(rel),
								  NULL, 0);

	/*
	 * If performing an UPDATE with tuple routing, we can reuse partition
	 * sub-plan result rels.  We build a hash table to map the OIDs of
	 * partitions present in mtstate->resultRelInfo to their ResultRelInfos.
	 * Every time a tuple is routed to a partition that we've yet to set the
	 * ResultRelInfo for, before we go to the trouble of making one, we check
	 * for a pre-made one in the hash table.
	 */
	if (node && node->operation == CMD_UPDATE)
		ExecHashSubPlanResultRelsByOid(mtstate, proute);

	return proute;
}