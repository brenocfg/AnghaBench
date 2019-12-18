#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  nparts; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ PartitionedRelPruneInfo ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_BITMAPSET_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_INT_ARRAY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_OID_ARRAY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_UINT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec_pruning_steps ; 
 int /*<<< orphan*/  execparamids ; 
 int /*<<< orphan*/  initial_pruning_steps ; 
 int /*<<< orphan*/  nparts ; 
 int /*<<< orphan*/  present_parts ; 
 int /*<<< orphan*/  relid_map ; 
 int /*<<< orphan*/  rtindex ; 
 int /*<<< orphan*/  subpart_map ; 
 int /*<<< orphan*/  subplan_map ; 

__attribute__((used)) static void
_outPartitionedRelPruneInfo(StringInfo str, const PartitionedRelPruneInfo *node)
{
	WRITE_NODE_TYPE("PARTITIONEDRELPRUNEINFO");

	WRITE_UINT_FIELD(rtindex);
	WRITE_BITMAPSET_FIELD(present_parts);
	WRITE_INT_FIELD(nparts);
	WRITE_INT_ARRAY(subplan_map, node->nparts);
	WRITE_INT_ARRAY(subpart_map, node->nparts);
	WRITE_OID_ARRAY(relid_map, node->nparts);
	WRITE_NODE_FIELD(initial_pruning_steps);
	WRITE_NODE_FIELD(exec_pruning_steps);
	WRITE_BITMAPSET_FIELD(execparamids);
}