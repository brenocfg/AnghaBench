#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  phs_syncscan; } ;
struct TYPE_5__ {scalar_t__ phs_startblock; int /*<<< orphan*/  phs_mutex; int /*<<< orphan*/  phs_nblocks; TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_2__* ParallelBlockTableScanDesc ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 scalar_t__ InvalidBlockNumber ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 scalar_t__ ss_get_location (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
table_block_parallelscan_startblock_init(Relation rel, ParallelBlockTableScanDesc pbscan)
{
	BlockNumber sync_startpage = InvalidBlockNumber;

retry:
	/* Grab the spinlock. */
	SpinLockAcquire(&pbscan->phs_mutex);

	/*
	 * If the scan's startblock has not yet been initialized, we must do so
	 * now.  If this is not a synchronized scan, we just start at block 0, but
	 * if it is a synchronized scan, we must get the starting position from
	 * the synchronized scan machinery.  We can't hold the spinlock while
	 * doing that, though, so release the spinlock, get the information we
	 * need, and retry.  If nobody else has initialized the scan in the
	 * meantime, we'll fill in the value we fetched on the second time
	 * through.
	 */
	if (pbscan->phs_startblock == InvalidBlockNumber)
	{
		if (!pbscan->base.phs_syncscan)
			pbscan->phs_startblock = 0;
		else if (sync_startpage != InvalidBlockNumber)
			pbscan->phs_startblock = sync_startpage;
		else
		{
			SpinLockRelease(&pbscan->phs_mutex);
			sync_startpage = ss_get_location(rel, pbscan->phs_nblocks);
			goto retry;
		}
	}
	SpinLockRelease(&pbscan->phs_mutex);
}