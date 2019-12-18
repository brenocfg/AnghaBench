#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int do_initial_prune; int num_partprunedata; int /*<<< orphan*/ * other_subplans; TYPE_4__** partprunedata; scalar_t__ do_exec_prune; int /*<<< orphan*/  prune_context; } ;
struct TYPE_12__ {int num_partrelprunedata; TYPE_3__* partrelprunedata; } ;
struct TYPE_10__ {TYPE_1__* planstate; } ;
struct TYPE_11__ {int nparts; int* subplan_map; int* subpart_map; int /*<<< orphan*/ * present_parts; TYPE_2__ initial_context; scalar_t__ initial_pruning_steps; } ;
struct TYPE_9__ {int /*<<< orphan*/  ps_ExprContext; } ;
typedef  TYPE_3__ PartitionedRelPruningData ;
typedef  TYPE_4__ PartitionPruningData ;
typedef  TYPE_5__ PartitionPruneState ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResetExprContext (int /*<<< orphan*/ ) ; 
 void* bms_add_member (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * bms_add_members (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bms_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bms_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bms_is_empty (int /*<<< orphan*/ *) ; 
 int bms_next_member (int /*<<< orphan*/ *,int) ; 
 int bms_num_members (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_matching_subplans_recurse (TYPE_4__*,TYPE_3__*,int,int /*<<< orphan*/ **) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  pfree (int*) ; 

Bitmapset *
ExecFindInitialMatchingSubPlans(PartitionPruneState *prunestate, int nsubplans)
{
	Bitmapset  *result = NULL;
	MemoryContext oldcontext;
	int			i;

	/* Caller error if we get here without do_initial_prune */
	Assert(prunestate->do_initial_prune);

	/*
	 * Switch to a temp context to avoid leaking memory in the executor's
	 * query-lifespan memory context.
	 */
	oldcontext = MemoryContextSwitchTo(prunestate->prune_context);

	/*
	 * For each hierarchy, do the pruning tests, and add nondeletable
	 * subplans' indexes to "result".
	 */
	for (i = 0; i < prunestate->num_partprunedata; i++)
	{
		PartitionPruningData *prunedata;
		PartitionedRelPruningData *pprune;

		prunedata = prunestate->partprunedata[i];
		pprune = &prunedata->partrelprunedata[0];

		/* Perform pruning without using PARAM_EXEC Params */
		find_matching_subplans_recurse(prunedata, pprune, true, &result);

		/* Expression eval may have used space in node's ps_ExprContext too */
		if (pprune->initial_pruning_steps)
			ResetExprContext(pprune->initial_context.planstate->ps_ExprContext);
	}

	/* Add in any subplans that partition pruning didn't account for */
	result = bms_add_members(result, prunestate->other_subplans);

	MemoryContextSwitchTo(oldcontext);

	/* Copy result out of the temp context before we reset it */
	result = bms_copy(result);

	MemoryContextReset(prunestate->prune_context);

	/*
	 * If exec-time pruning is required and we pruned subplans above, then we
	 * must re-sequence the subplan indexes so that ExecFindMatchingSubPlans
	 * properly returns the indexes from the subplans which will remain after
	 * execution of this function.
	 *
	 * We can safely skip this when !do_exec_prune, even though that leaves
	 * invalid data in prunestate, because that data won't be consulted again
	 * (cf initial Assert in ExecFindMatchingSubPlans).
	 */
	if (prunestate->do_exec_prune && bms_num_members(result) < nsubplans)
	{
		int		   *new_subplan_indexes;
		Bitmapset  *new_other_subplans;
		int			i;
		int			newidx;

		/*
		 * First we must build a temporary array which maps old subplan
		 * indexes to new ones.  For convenience of initialization, we use
		 * 1-based indexes in this array and leave pruned items as 0.
		 */
		new_subplan_indexes = (int *) palloc0(sizeof(int) * nsubplans);
		newidx = 1;
		i = -1;
		while ((i = bms_next_member(result, i)) >= 0)
		{
			Assert(i < nsubplans);
			new_subplan_indexes[i] = newidx++;
		}

		/*
		 * Now we can update each PartitionedRelPruneInfo's subplan_map with
		 * new subplan indexes.  We must also recompute its present_parts
		 * bitmap.
		 */
		for (i = 0; i < prunestate->num_partprunedata; i++)
		{
			PartitionPruningData *prunedata = prunestate->partprunedata[i];
			int			j;

			/*
			 * Within each hierarchy, we perform this loop in back-to-front
			 * order so that we determine present_parts for the lowest-level
			 * partitioned tables first.  This way we can tell whether a
			 * sub-partitioned table's partitions were entirely pruned so we
			 * can exclude it from the current level's present_parts.
			 */
			for (j = prunedata->num_partrelprunedata - 1; j >= 0; j--)
			{
				PartitionedRelPruningData *pprune = &prunedata->partrelprunedata[j];
				int			nparts = pprune->nparts;
				int			k;

				/* We just rebuild present_parts from scratch */
				bms_free(pprune->present_parts);
				pprune->present_parts = NULL;

				for (k = 0; k < nparts; k++)
				{
					int			oldidx = pprune->subplan_map[k];
					int			subidx;

					/*
					 * If this partition existed as a subplan then change the
					 * old subplan index to the new subplan index.  The new
					 * index may become -1 if the partition was pruned above,
					 * or it may just come earlier in the subplan list due to
					 * some subplans being removed earlier in the list.  If
					 * it's a subpartition, add it to present_parts unless
					 * it's entirely pruned.
					 */
					if (oldidx >= 0)
					{
						Assert(oldidx < nsubplans);
						pprune->subplan_map[k] = new_subplan_indexes[oldidx] - 1;

						if (new_subplan_indexes[oldidx] > 0)
							pprune->present_parts =
								bms_add_member(pprune->present_parts, k);
					}
					else if ((subidx = pprune->subpart_map[k]) >= 0)
					{
						PartitionedRelPruningData *subprune;

						subprune = &prunedata->partrelprunedata[subidx];

						if (!bms_is_empty(subprune->present_parts))
							pprune->present_parts =
								bms_add_member(pprune->present_parts, k);
					}
				}
			}
		}

		/*
		 * We must also recompute the other_subplans set, since indexes in it
		 * may change.
		 */
		new_other_subplans = NULL;
		i = -1;
		while ((i = bms_next_member(prunestate->other_subplans, i)) >= 0)
			new_other_subplans = bms_add_member(new_other_subplans,
												new_subplan_indexes[i] - 1);

		bms_free(prunestate->other_subplans);
		prunestate->other_subplans = new_other_subplans;

		pfree(new_subplan_indexes);
	}

	return result;
}