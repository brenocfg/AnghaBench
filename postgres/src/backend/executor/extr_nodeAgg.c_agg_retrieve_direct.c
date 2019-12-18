#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_29__ {scalar_t__ aggstrategy; int numCols; } ;
struct TYPE_23__ {TYPE_5__* ps_ExprContext; } ;
struct TYPE_24__ {int /*<<< orphan*/ * ss_ScanTupleSlot; TYPE_1__ ps; } ;
struct TYPE_28__ {int agg_done; int projected_set; int input_done; int current_phase; int numphases; scalar_t__ aggstrategy; int table_filled; int /*<<< orphan*/ * grp_firstTuple; TYPE_4__* phase; TYPE_3__* perhash; TYPE_5__** aggcontexts; TYPE_2__ ss; int /*<<< orphan*/ * pergroups; int /*<<< orphan*/  peragg; TYPE_5__* tmpcontext; } ;
struct TYPE_27__ {int /*<<< orphan*/ * ecxt_outertuple; int /*<<< orphan*/ * ecxt_innertuple; } ;
struct TYPE_26__ {scalar_t__ numsets; int* gset_lengths; int /*<<< orphan*/ * eqfunctions; TYPE_7__* aggnode; } ;
struct TYPE_25__ {int /*<<< orphan*/  hashiter; int /*<<< orphan*/  hashtable; } ;
typedef  TYPE_5__ ExprContext ;
typedef  int /*<<< orphan*/  AggStatePerGroup ;
typedef  int /*<<< orphan*/  AggStatePerAgg ;
typedef  TYPE_6__ AggState ;
typedef  TYPE_7__ Agg ;

/* Variables and functions */
 scalar_t__ AGG_MIXED ; 
 scalar_t__ AGG_PLAIN ; 
 int /*<<< orphan*/  Assert (int) ; 
 void* ExecCopySlotHeapTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecForceStoreHeapTuple (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ExecQual (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  ExecQualAndReset (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int Max (scalar_t__,int) ; 
 int /*<<< orphan*/  ReScanExprContext (TYPE_5__*) ; 
 int /*<<< orphan*/  ResetExprContext (TYPE_5__*) ; 
 int /*<<< orphan*/  ResetTupleHashIterator (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ TupIsNull (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  advance_aggregates (TYPE_6__*) ; 
 int /*<<< orphan*/ * agg_retrieve_hash_table (TYPE_6__*) ; 
 int /*<<< orphan*/ * fetch_input_tuple (TYPE_6__*) ; 
 int /*<<< orphan*/  finalize_aggregates (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initialize_aggregates (TYPE_6__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  initialize_phase (TYPE_6__*,int) ; 
 int /*<<< orphan*/  lookup_hash_entries (TYPE_6__*) ; 
 int /*<<< orphan*/  prepare_projection_slot (TYPE_6__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * project_aggregates (TYPE_6__*) ; 
 int /*<<< orphan*/  select_current_set (TYPE_6__*,int,int) ; 

__attribute__((used)) static TupleTableSlot *
agg_retrieve_direct(AggState *aggstate)
{
	Agg		   *node = aggstate->phase->aggnode;
	ExprContext *econtext;
	ExprContext *tmpcontext;
	AggStatePerAgg peragg;
	AggStatePerGroup *pergroups;
	TupleTableSlot *outerslot;
	TupleTableSlot *firstSlot;
	TupleTableSlot *result;
	bool		hasGroupingSets = aggstate->phase->numsets > 0;
	int			numGroupingSets = Max(aggstate->phase->numsets, 1);
	int			currentSet;
	int			nextSetSize;
	int			numReset;
	int			i;

	/*
	 * get state info from node
	 *
	 * econtext is the per-output-tuple expression context
	 *
	 * tmpcontext is the per-input-tuple expression context
	 */
	econtext = aggstate->ss.ps.ps_ExprContext;
	tmpcontext = aggstate->tmpcontext;

	peragg = aggstate->peragg;
	pergroups = aggstate->pergroups;
	firstSlot = aggstate->ss.ss_ScanTupleSlot;

	/*
	 * We loop retrieving groups until we find one matching
	 * aggstate->ss.ps.qual
	 *
	 * For grouping sets, we have the invariant that aggstate->projected_set
	 * is either -1 (initial call) or the index (starting from 0) in
	 * gset_lengths for the group we just completed (either by projecting a
	 * row or by discarding it in the qual).
	 */
	while (!aggstate->agg_done)
	{
		/*
		 * Clear the per-output-tuple context for each group, as well as
		 * aggcontext (which contains any pass-by-ref transvalues of the old
		 * group).  Some aggregate functions store working state in child
		 * contexts; those now get reset automatically without us needing to
		 * do anything special.
		 *
		 * We use ReScanExprContext not just ResetExprContext because we want
		 * any registered shutdown callbacks to be called.  That allows
		 * aggregate functions to ensure they've cleaned up any non-memory
		 * resources.
		 */
		ReScanExprContext(econtext);

		/*
		 * Determine how many grouping sets need to be reset at this boundary.
		 */
		if (aggstate->projected_set >= 0 &&
			aggstate->projected_set < numGroupingSets)
			numReset = aggstate->projected_set + 1;
		else
			numReset = numGroupingSets;

		/*
		 * numReset can change on a phase boundary, but that's OK; we want to
		 * reset the contexts used in _this_ phase, and later, after possibly
		 * changing phase, initialize the right number of aggregates for the
		 * _new_ phase.
		 */

		for (i = 0; i < numReset; i++)
		{
			ReScanExprContext(aggstate->aggcontexts[i]);
		}

		/*
		 * Check if input is complete and there are no more groups to project
		 * in this phase; move to next phase or mark as done.
		 */
		if (aggstate->input_done == true &&
			aggstate->projected_set >= (numGroupingSets - 1))
		{
			if (aggstate->current_phase < aggstate->numphases - 1)
			{
				initialize_phase(aggstate, aggstate->current_phase + 1);
				aggstate->input_done = false;
				aggstate->projected_set = -1;
				numGroupingSets = Max(aggstate->phase->numsets, 1);
				node = aggstate->phase->aggnode;
				numReset = numGroupingSets;
			}
			else if (aggstate->aggstrategy == AGG_MIXED)
			{
				/*
				 * Mixed mode; we've output all the grouped stuff and have
				 * full hashtables, so switch to outputting those.
				 */
				initialize_phase(aggstate, 0);
				aggstate->table_filled = true;
				ResetTupleHashIterator(aggstate->perhash[0].hashtable,
									   &aggstate->perhash[0].hashiter);
				select_current_set(aggstate, 0, true);
				return agg_retrieve_hash_table(aggstate);
			}
			else
			{
				aggstate->agg_done = true;
				break;
			}
		}

		/*
		 * Get the number of columns in the next grouping set after the last
		 * projected one (if any). This is the number of columns to compare to
		 * see if we reached the boundary of that set too.
		 */
		if (aggstate->projected_set >= 0 &&
			aggstate->projected_set < (numGroupingSets - 1))
			nextSetSize = aggstate->phase->gset_lengths[aggstate->projected_set + 1];
		else
			nextSetSize = 0;

		/*----------
		 * If a subgroup for the current grouping set is present, project it.
		 *
		 * We have a new group if:
		 *	- we're out of input but haven't projected all grouping sets
		 *	  (checked above)
		 * OR
		 *	  - we already projected a row that wasn't from the last grouping
		 *		set
		 *	  AND
		 *	  - the next grouping set has at least one grouping column (since
		 *		empty grouping sets project only once input is exhausted)
		 *	  AND
		 *	  - the previous and pending rows differ on the grouping columns
		 *		of the next grouping set
		 *----------
		 */
		tmpcontext->ecxt_innertuple = econtext->ecxt_outertuple;
		if (aggstate->input_done ||
			(node->aggstrategy != AGG_PLAIN &&
			 aggstate->projected_set != -1 &&
			 aggstate->projected_set < (numGroupingSets - 1) &&
			 nextSetSize > 0 &&
			 !ExecQualAndReset(aggstate->phase->eqfunctions[nextSetSize - 1],
							   tmpcontext)))
		{
			aggstate->projected_set += 1;

			Assert(aggstate->projected_set < numGroupingSets);
			Assert(nextSetSize > 0 || aggstate->input_done);
		}
		else
		{
			/*
			 * We no longer care what group we just projected, the next
			 * projection will always be the first (or only) grouping set
			 * (unless the input proves to be empty).
			 */
			aggstate->projected_set = 0;

			/*
			 * If we don't already have the first tuple of the new group,
			 * fetch it from the outer plan.
			 */
			if (aggstate->grp_firstTuple == NULL)
			{
				outerslot = fetch_input_tuple(aggstate);
				if (!TupIsNull(outerslot))
				{
					/*
					 * Make a copy of the first input tuple; we will use this
					 * for comparisons (in group mode) and for projection.
					 */
					aggstate->grp_firstTuple = ExecCopySlotHeapTuple(outerslot);
				}
				else
				{
					/* outer plan produced no tuples at all */
					if (hasGroupingSets)
					{
						/*
						 * If there was no input at all, we need to project
						 * rows only if there are grouping sets of size 0.
						 * Note that this implies that there can't be any
						 * references to ungrouped Vars, which would otherwise
						 * cause issues with the empty output slot.
						 *
						 * XXX: This is no longer true, we currently deal with
						 * this in finalize_aggregates().
						 */
						aggstate->input_done = true;

						while (aggstate->phase->gset_lengths[aggstate->projected_set] > 0)
						{
							aggstate->projected_set += 1;
							if (aggstate->projected_set >= numGroupingSets)
							{
								/*
								 * We can't set agg_done here because we might
								 * have more phases to do, even though the
								 * input is empty. So we need to restart the
								 * whole outer loop.
								 */
								break;
							}
						}

						if (aggstate->projected_set >= numGroupingSets)
							continue;
					}
					else
					{
						aggstate->agg_done = true;
						/* If we are grouping, we should produce no tuples too */
						if (node->aggstrategy != AGG_PLAIN)
							return NULL;
					}
				}
			}

			/*
			 * Initialize working state for a new input tuple group.
			 */
			initialize_aggregates(aggstate, pergroups, numReset);

			if (aggstate->grp_firstTuple != NULL)
			{
				/*
				 * Store the copied first input tuple in the tuple table slot
				 * reserved for it.  The tuple will be deleted when it is
				 * cleared from the slot.
				 */
				ExecForceStoreHeapTuple(aggstate->grp_firstTuple,
										firstSlot, true);
				aggstate->grp_firstTuple = NULL;	/* don't keep two pointers */

				/* set up for first advance_aggregates call */
				tmpcontext->ecxt_outertuple = firstSlot;

				/*
				 * Process each outer-plan tuple, and then fetch the next one,
				 * until we exhaust the outer plan or cross a group boundary.
				 */
				for (;;)
				{
					/*
					 * During phase 1 only of a mixed agg, we need to update
					 * hashtables as well in advance_aggregates.
					 */
					if (aggstate->aggstrategy == AGG_MIXED &&
						aggstate->current_phase == 1)
					{
						lookup_hash_entries(aggstate);
					}

					/* Advance the aggregates (or combine functions) */
					advance_aggregates(aggstate);

					/* Reset per-input-tuple context after each tuple */
					ResetExprContext(tmpcontext);

					outerslot = fetch_input_tuple(aggstate);
					if (TupIsNull(outerslot))
					{
						/* no more outer-plan tuples available */
						if (hasGroupingSets)
						{
							aggstate->input_done = true;
							break;
						}
						else
						{
							aggstate->agg_done = true;
							break;
						}
					}
					/* set up for next advance_aggregates call */
					tmpcontext->ecxt_outertuple = outerslot;

					/*
					 * If we are grouping, check whether we've crossed a group
					 * boundary.
					 */
					if (node->aggstrategy != AGG_PLAIN)
					{
						tmpcontext->ecxt_innertuple = firstSlot;
						if (!ExecQual(aggstate->phase->eqfunctions[node->numCols - 1],
									  tmpcontext))
						{
							aggstate->grp_firstTuple = ExecCopySlotHeapTuple(outerslot);
							break;
						}
					}
				}
			}

			/*
			 * Use the representative input tuple for any references to
			 * non-aggregated input columns in aggregate direct args, the node
			 * qual, and the tlist.  (If we are not grouping, and there are no
			 * input rows at all, we will come here with an empty firstSlot
			 * ... but if not grouping, there can't be any references to
			 * non-aggregated input columns, so no problem.)
			 */
			econtext->ecxt_outertuple = firstSlot;
		}

		Assert(aggstate->projected_set >= 0);

		currentSet = aggstate->projected_set;

		prepare_projection_slot(aggstate, econtext->ecxt_outertuple, currentSet);

		select_current_set(aggstate, currentSet, false);

		finalize_aggregates(aggstate,
							peragg,
							pergroups[currentSet]);

		/*
		 * If there's no row to project right now, we must continue rather
		 * than returning a null since there might be more groups.
		 */
		result = project_aggregates(aggstate);
		if (result)
			return result;
	}

	/* No more groups */
	return NULL;
}