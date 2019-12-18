#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* partrelprunedata; } ;
struct TYPE_5__ {scalar_t__* subplan_map; int* subpart_map; int /*<<< orphan*/ * present_parts; scalar_t__ exec_pruning_steps; int /*<<< orphan*/  exec_context; scalar_t__ initial_pruning_steps; int /*<<< orphan*/  initial_context; } ;
typedef  TYPE_1__ PartitionedRelPruningData ;
typedef  TYPE_2__ PartitionPruningData ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 int /*<<< orphan*/ * bms_add_member (int /*<<< orphan*/ *,scalar_t__) ; 
 int bms_next_member (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/ * get_matching_partitions (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
find_matching_subplans_recurse(PartitionPruningData *prunedata,
							   PartitionedRelPruningData *pprune,
							   bool initial_prune,
							   Bitmapset **validsubplans)
{
	Bitmapset  *partset;
	int			i;

	/* Guard against stack overflow due to overly deep partition hierarchy. */
	check_stack_depth();

	/* Only prune if pruning would be useful at this level. */
	if (initial_prune && pprune->initial_pruning_steps)
	{
		partset = get_matching_partitions(&pprune->initial_context,
										  pprune->initial_pruning_steps);
	}
	else if (!initial_prune && pprune->exec_pruning_steps)
	{
		partset = get_matching_partitions(&pprune->exec_context,
										  pprune->exec_pruning_steps);
	}
	else
	{
		/*
		 * If no pruning is to be done, just include all partitions at this
		 * level.
		 */
		partset = pprune->present_parts;
	}

	/* Translate partset into subplan indexes */
	i = -1;
	while ((i = bms_next_member(partset, i)) >= 0)
	{
		if (pprune->subplan_map[i] >= 0)
			*validsubplans = bms_add_member(*validsubplans,
											pprune->subplan_map[i]);
		else
		{
			int			partidx = pprune->subpart_map[i];

			if (partidx >= 0)
				find_matching_subplans_recurse(prunedata,
											   &prunedata->partrelprunedata[partidx],
											   initial_prune, validsubplans);
			else
			{
				/*
				 * We get here if the planner already pruned all the sub-
				 * partitions for this partition.  Silently ignore this
				 * partition in this case.  The end result is the same: we
				 * would have pruned all partitions just the same, but we
				 * don't have any pruning steps to execute to verify this.
				 */
			}
		}
	}
}