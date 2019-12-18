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
struct TYPE_3__ {void* callback_state; int /*<<< orphan*/  callback; int /*<<< orphan*/ * stats; int /*<<< orphan*/ * info; } ;
typedef  TYPE_1__ spgBulkDeleteState ;
typedef  int /*<<< orphan*/  IndexVacuumInfo ;
typedef  int /*<<< orphan*/  IndexBulkDeleteResult ;
typedef  int /*<<< orphan*/  IndexBulkDeleteCallback ;

/* Variables and functions */
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  spgvacuumscan (TYPE_1__*) ; 

IndexBulkDeleteResult *
spgbulkdelete(IndexVacuumInfo *info, IndexBulkDeleteResult *stats,
			  IndexBulkDeleteCallback callback, void *callback_state)
{
	spgBulkDeleteState bds;

	/* allocate stats if first time through, else re-use existing struct */
	if (stats == NULL)
		stats = (IndexBulkDeleteResult *) palloc0(sizeof(IndexBulkDeleteResult));
	bds.info = info;
	bds.stats = stats;
	bds.callback = callback;
	bds.callback_state = callback_state;

	spgvacuumscan(&bds);

	return stats;
}