#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_12__ {int table_filled; TYPE_1__* perhash; TYPE_2__* tmpcontext; } ;
struct TYPE_11__ {int /*<<< orphan*/ * ecxt_outertuple; } ;
struct TYPE_10__ {int /*<<< orphan*/  hashiter; int /*<<< orphan*/  hashtable; } ;
typedef  TYPE_2__ ExprContext ;
typedef  TYPE_3__ AggState ;

/* Variables and functions */
 int /*<<< orphan*/  ResetExprContext (TYPE_2__*) ; 
 int /*<<< orphan*/  ResetTupleHashIterator (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ TupIsNull (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  advance_aggregates (TYPE_3__*) ; 
 int /*<<< orphan*/ * fetch_input_tuple (TYPE_3__*) ; 
 int /*<<< orphan*/  lookup_hash_entries (TYPE_3__*) ; 
 int /*<<< orphan*/  select_current_set (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
agg_fill_hash_table(AggState *aggstate)
{
	TupleTableSlot *outerslot;
	ExprContext *tmpcontext = aggstate->tmpcontext;

	/*
	 * Process each outer-plan tuple, and then fetch the next one, until we
	 * exhaust the outer plan.
	 */
	for (;;)
	{
		outerslot = fetch_input_tuple(aggstate);
		if (TupIsNull(outerslot))
			break;

		/* set up for lookup_hash_entries and advance_aggregates */
		tmpcontext->ecxt_outertuple = outerslot;

		/* Find or build hashtable entries */
		lookup_hash_entries(aggstate);

		/* Advance the aggregates (or combine functions) */
		advance_aggregates(aggstate);

		/*
		 * Reset per-input-tuple context after each tuple, but note that the
		 * hash lookups do this too
		 */
		ResetExprContext(aggstate->tmpcontext);
	}

	aggstate->table_filled = true;
	/* Initialize to walk the first hash table */
	select_current_set(aggstate, 0, true);
	ResetTupleHashIterator(aggstate->perhash[0].hashtable,
						   &aggstate->perhash[0].hashiter);
}