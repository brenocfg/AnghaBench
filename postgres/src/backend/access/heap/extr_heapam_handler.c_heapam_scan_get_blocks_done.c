#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * rs_parallel; } ;
struct TYPE_7__ {scalar_t__ rs_startblock; scalar_t__ rs_cblock; scalar_t__ rs_nblocks; TYPE_1__ rs_base; } ;
struct TYPE_6__ {scalar_t__ phs_startblock; scalar_t__ phs_nblocks; } ;
typedef  TYPE_2__* ParallelBlockTableScanDesc ;
typedef  TYPE_3__* HeapScanDesc ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */

__attribute__((used)) static BlockNumber
heapam_scan_get_blocks_done(HeapScanDesc hscan)
{
	ParallelBlockTableScanDesc bpscan = NULL;
	BlockNumber startblock;
	BlockNumber blocks_done;

	if (hscan->rs_base.rs_parallel != NULL)
	{
		bpscan = (ParallelBlockTableScanDesc) hscan->rs_base.rs_parallel;
		startblock = bpscan->phs_startblock;
	}
	else
		startblock = hscan->rs_startblock;

	/*
	 * Might have wrapped around the end of the relation, if startblock was
	 * not zero.
	 */
	if (hscan->rs_cblock > startblock)
		blocks_done = hscan->rs_cblock - startblock;
	else
	{
		BlockNumber nblocks;

		nblocks = bpscan != NULL ? bpscan->phs_nblocks : hscan->rs_nblocks;
		blocks_done = nblocks - startblock +
			hscan->rs_cblock;
	}

	return blocks_done;
}