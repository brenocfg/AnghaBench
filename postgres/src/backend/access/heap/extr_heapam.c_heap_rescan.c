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
typedef  int /*<<< orphan*/  TableScanDesc ;
struct TYPE_4__ {int /*<<< orphan*/  rs_flags; scalar_t__ rs_snapshot; } ;
struct TYPE_5__ {int /*<<< orphan*/  rs_cbuf; TYPE_1__ rs_base; } ;
typedef  int /*<<< orphan*/  ScanKey ;
typedef  TYPE_2__* HeapScanDesc ;

/* Variables and functions */
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ IsMVCCSnapshot (scalar_t__) ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SO_ALLOW_PAGEMODE ; 
 int /*<<< orphan*/  SO_ALLOW_STRAT ; 
 int /*<<< orphan*/  SO_ALLOW_SYNC ; 
 int /*<<< orphan*/  initscan (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void
heap_rescan(TableScanDesc sscan, ScanKey key, bool set_params,
			bool allow_strat, bool allow_sync, bool allow_pagemode)
{
	HeapScanDesc scan = (HeapScanDesc) sscan;

	if (set_params)
	{
		if (allow_strat)
			scan->rs_base.rs_flags |= SO_ALLOW_STRAT;
		else
			scan->rs_base.rs_flags &= ~SO_ALLOW_STRAT;

		if (allow_sync)
			scan->rs_base.rs_flags |= SO_ALLOW_SYNC;
		else
			scan->rs_base.rs_flags &= ~SO_ALLOW_SYNC;

		if (allow_pagemode && scan->rs_base.rs_snapshot &&
			IsMVCCSnapshot(scan->rs_base.rs_snapshot))
			scan->rs_base.rs_flags |= SO_ALLOW_PAGEMODE;
		else
			scan->rs_base.rs_flags &= ~SO_ALLOW_PAGEMODE;
	}

	/*
	 * unpin scan buffers
	 */
	if (BufferIsValid(scan->rs_cbuf))
		ReleaseBuffer(scan->rs_cbuf);

	/*
	 * reinitialize scan descriptor
	 */
	initscan(scan, key, true);
}