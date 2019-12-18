#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * callback_state; int /*<<< orphan*/  callback; TYPE_3__* stats; TYPE_2__* info; } ;
typedef  TYPE_1__ spgBulkDeleteState ;
struct TYPE_10__ {scalar_t__ num_index_tuples; } ;
struct TYPE_9__ {scalar_t__ num_heap_tuples; int /*<<< orphan*/  estimated_count; scalar_t__ analyze_only; } ;
typedef  TYPE_2__ IndexVacuumInfo ;
typedef  TYPE_3__ IndexBulkDeleteResult ;

/* Variables and functions */
 int /*<<< orphan*/  dummy_callback ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  spgvacuumscan (TYPE_1__*) ; 

IndexBulkDeleteResult *
spgvacuumcleanup(IndexVacuumInfo *info, IndexBulkDeleteResult *stats)
{
	spgBulkDeleteState bds;

	/* No-op in ANALYZE ONLY mode */
	if (info->analyze_only)
		return stats;

	/*
	 * We don't need to scan the index if there was a preceding bulkdelete
	 * pass.  Otherwise, make a pass that won't delete any live tuples, but
	 * might still accomplish useful stuff with redirect/placeholder cleanup
	 * and/or FSM housekeeping, and in any case will provide stats.
	 */
	if (stats == NULL)
	{
		stats = (IndexBulkDeleteResult *) palloc0(sizeof(IndexBulkDeleteResult));
		bds.info = info;
		bds.stats = stats;
		bds.callback = dummy_callback;
		bds.callback_state = NULL;

		spgvacuumscan(&bds);
	}

	/*
	 * It's quite possible for us to be fooled by concurrent tuple moves into
	 * double-counting some index tuples, so disbelieve any total that exceeds
	 * the underlying heap's count ... if we know that accurately.  Otherwise
	 * this might just make matters worse.
	 */
	if (!info->estimated_count)
	{
		if (stats->num_index_tuples > info->num_heap_tuples)
			stats->num_index_tuples = info->num_heap_tuples;
	}

	return stats;
}