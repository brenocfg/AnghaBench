#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_10__ {scalar_t__ num_index_tuples; } ;
struct TYPE_9__ {scalar_t__ num_heap_tuples; int /*<<< orphan*/  estimated_count; int /*<<< orphan*/  index; scalar_t__ analyze_only; } ;
typedef  TYPE_1__ IndexVacuumInfo ;
typedef  TYPE_2__ IndexBulkDeleteResult ;

/* Variables and functions */
 int /*<<< orphan*/  _bt_update_meta_cleanup_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  _bt_vacuum_needs_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  btvacuumscan (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ palloc0 (int) ; 

IndexBulkDeleteResult *
btvacuumcleanup(IndexVacuumInfo *info, IndexBulkDeleteResult *stats)
{
	/* No-op in ANALYZE ONLY mode */
	if (info->analyze_only)
		return stats;

	/*
	 * If btbulkdelete was called, we need not do anything, just return the
	 * stats from the latest btbulkdelete call.  If it wasn't called, we might
	 * still need to do a pass over the index, to recycle any newly-recyclable
	 * pages or to obtain index statistics.  _bt_vacuum_needs_cleanup
	 * determines if either are needed.
	 *
	 * Since we aren't going to actually delete any leaf items, there's no
	 * need to go through all the vacuum-cycle-ID pushups.
	 */
	if (stats == NULL)
	{
		TransactionId oldestBtpoXact;

		/* Check if we need a cleanup */
		if (!_bt_vacuum_needs_cleanup(info))
			return NULL;

		stats = (IndexBulkDeleteResult *) palloc0(sizeof(IndexBulkDeleteResult));
		btvacuumscan(info, stats, NULL, NULL, 0, &oldestBtpoXact);

		/* Update cleanup-related information in the metapage */
		_bt_update_meta_cleanup_info(info->index, oldestBtpoXact,
									 info->num_heap_tuples);
	}

	/*
	 * It's quite possible for us to be fooled by concurrent page splits into
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