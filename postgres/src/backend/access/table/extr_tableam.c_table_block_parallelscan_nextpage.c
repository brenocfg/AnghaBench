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
typedef  int uint64 ;
struct TYPE_4__ {scalar_t__ phs_syncscan; } ;
struct TYPE_5__ {int phs_nblocks; int phs_startblock; TYPE_1__ base; int /*<<< orphan*/  phs_nallocated; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_2__* ParallelBlockTableScanDesc ;
typedef  int BlockNumber ;

/* Variables and functions */
 int InvalidBlockNumber ; 
 int pg_atomic_fetch_add_u64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ss_report_location (int /*<<< orphan*/ ,int) ; 

BlockNumber
table_block_parallelscan_nextpage(Relation rel, ParallelBlockTableScanDesc pbscan)
{
	BlockNumber page;
	uint64		nallocated;

	/*
	 * phs_nallocated tracks how many pages have been allocated to workers
	 * already.  When phs_nallocated >= rs_nblocks, all blocks have been
	 * allocated.
	 *
	 * Because we use an atomic fetch-and-add to fetch the current value, the
	 * phs_nallocated counter will exceed rs_nblocks, because workers will
	 * still increment the value, when they try to allocate the next block but
	 * all blocks have been allocated already. The counter must be 64 bits
	 * wide because of that, to avoid wrapping around when rs_nblocks is close
	 * to 2^32.
	 *
	 * The actual page to return is calculated by adding the counter to the
	 * starting block number, modulo nblocks.
	 */
	nallocated = pg_atomic_fetch_add_u64(&pbscan->phs_nallocated, 1);
	if (nallocated >= pbscan->phs_nblocks)
		page = InvalidBlockNumber;	/* all blocks have been allocated */
	else
		page = (nallocated + pbscan->phs_startblock) % pbscan->phs_nblocks;

	/*
	 * Report scan location.  Normally, we report the current page number.
	 * When we reach the end of the scan, though, we report the starting page,
	 * not the ending page, just so the starting positions for later scans
	 * doesn't slew backwards.  We only report the position at the end of the
	 * scan once, though: subsequent callers will report nothing.
	 */
	if (pbscan->base.phs_syncscan)
	{
		if (page != InvalidBlockNumber)
			ss_report_location(rel, page);
		else if (nallocated == pbscan->phs_nblocks)
			ss_report_location(rel, pbscan->phs_startblock);
	}

	return page;
}