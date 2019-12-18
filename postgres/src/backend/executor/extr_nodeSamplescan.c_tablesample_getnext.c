#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
typedef  int /*<<< orphan*/  TableScanDesc ;
struct TYPE_6__ {int /*<<< orphan*/ * ss_ScanTupleSlot; int /*<<< orphan*/  ss_currentScanDesc; } ;
struct TYPE_7__ {int done; int haveblock; int /*<<< orphan*/  donetuples; TYPE_1__ ss; } ;
typedef  TYPE_2__ SampleScanState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecClearTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_scan_sample_next_block (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  table_scan_sample_next_tuple (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static TupleTableSlot *
tablesample_getnext(SampleScanState *scanstate)
{
	TableScanDesc scan = scanstate->ss.ss_currentScanDesc;
	TupleTableSlot *slot = scanstate->ss.ss_ScanTupleSlot;

	ExecClearTuple(slot);

	if (scanstate->done)
		return NULL;

	for (;;)
	{
		if (!scanstate->haveblock)
		{
			if (!table_scan_sample_next_block(scan, scanstate))
			{
				scanstate->haveblock = false;
				scanstate->done = true;

				/* exhausted relation */
				return NULL;
			}

			scanstate->haveblock = true;
		}

		if (!table_scan_sample_next_tuple(scan, scanstate, slot))
		{
			/*
			 * If we get here, it means we've exhausted the items on this page
			 * and it's time to move to the next.
			 */
			scanstate->haveblock = false;
			continue;
		}

		/* Found visible tuple, return it. */
		break;
	}

	scanstate->donetuples++;

	return slot;
}