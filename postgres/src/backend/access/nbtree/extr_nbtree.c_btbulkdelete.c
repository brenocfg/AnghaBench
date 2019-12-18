#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_4__ {int /*<<< orphan*/  num_heap_tuples; int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ IndexVacuumInfo ;
typedef  int /*<<< orphan*/  IndexBulkDeleteResult ;
typedef  int /*<<< orphan*/  IndexBulkDeleteCallback ;
typedef  int /*<<< orphan*/  BTCycleId ;

/* Variables and functions */
 int /*<<< orphan*/  PG_END_ENSURE_ERROR_CLEANUP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_ENSURE_ERROR_CLEANUP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_end_vacuum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_end_vacuum_callback ; 
 int /*<<< orphan*/  _bt_start_vacuum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_update_meta_cleanup_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btvacuumscan (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ palloc0 (int) ; 

IndexBulkDeleteResult *
btbulkdelete(IndexVacuumInfo *info, IndexBulkDeleteResult *stats,
			 IndexBulkDeleteCallback callback, void *callback_state)
{
	Relation	rel = info->index;
	BTCycleId	cycleid;

	/* allocate stats if first time through, else re-use existing struct */
	if (stats == NULL)
		stats = (IndexBulkDeleteResult *) palloc0(sizeof(IndexBulkDeleteResult));

	/* Establish the vacuum cycle ID to use for this scan */
	/* The ENSURE stuff ensures we clean up shared memory on failure */
	PG_ENSURE_ERROR_CLEANUP(_bt_end_vacuum_callback, PointerGetDatum(rel));
	{
		TransactionId oldestBtpoXact;

		cycleid = _bt_start_vacuum(rel);

		btvacuumscan(info, stats, callback, callback_state, cycleid,
					 &oldestBtpoXact);

		/*
		 * Update cleanup-related information in metapage. This information is
		 * used only for cleanup but keeping them up to date can avoid
		 * unnecessary cleanup even after bulkdelete.
		 */
		_bt_update_meta_cleanup_info(info->index, oldestBtpoXact,
									 info->num_heap_tuples);
	}
	PG_END_ENSURE_ERROR_CLEANUP(_bt_end_vacuum_callback, PointerGetDatum(rel));
	_bt_end_vacuum(rel);

	return stats;
}