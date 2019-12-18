#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int rs_flags; int rs_nkeys; int /*<<< orphan*/  rs_rd; int /*<<< orphan*/  rs_key; TYPE_1__* rs_parallel; } ;
struct TYPE_8__ {int /*<<< orphan*/  t_self; int /*<<< orphan*/ * t_data; } ;
struct TYPE_11__ {int rs_nblocks; int rs_inited; TYPE_3__ rs_base; void* rs_cblock; int /*<<< orphan*/  rs_cbuf; TYPE_2__ rs_ctup; void* rs_numblocks; scalar_t__ rs_startblock; int /*<<< orphan*/ * rs_strategy; } ;
struct TYPE_10__ {int phs_nblocks; } ;
struct TYPE_7__ {scalar_t__ phs_syncscan; } ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/ * ScanKey ;
typedef  TYPE_4__* ParallelBlockTableScanDesc ;
typedef  TYPE_5__* HeapScanDesc ;

/* Variables and functions */
 int /*<<< orphan*/  BAS_BULKREAD ; 
 int /*<<< orphan*/  FreeAccessStrategy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetAccessStrategy (int /*<<< orphan*/ ) ; 
 void* InvalidBlockNumber ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 int /*<<< orphan*/  ItemPointerSetInvalid (int /*<<< orphan*/ *) ; 
 int NBuffers ; 
 int RelationGetNumberOfBlocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationUsesLocalBuffers (int /*<<< orphan*/ ) ; 
 int SO_ALLOW_STRAT ; 
 int SO_ALLOW_SYNC ; 
 int SO_TYPE_SEQSCAN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pgstat_count_heap_scan (int /*<<< orphan*/ ) ; 
 scalar_t__ ss_get_location (int /*<<< orphan*/ ,int) ; 
 scalar_t__ synchronize_seqscans ; 

__attribute__((used)) static void
initscan(HeapScanDesc scan, ScanKey key, bool keep_startblock)
{
	ParallelBlockTableScanDesc bpscan = NULL;
	bool		allow_strat;
	bool		allow_sync;

	/*
	 * Determine the number of blocks we have to scan.
	 *
	 * It is sufficient to do this once at scan start, since any tuples added
	 * while the scan is in progress will be invisible to my snapshot anyway.
	 * (That is not true when using a non-MVCC snapshot.  However, we couldn't
	 * guarantee to return tuples added after scan start anyway, since they
	 * might go into pages we already scanned.  To guarantee consistent
	 * results for a non-MVCC snapshot, the caller must hold some higher-level
	 * lock that ensures the interesting tuple(s) won't change.)
	 */
	if (scan->rs_base.rs_parallel != NULL)
	{
		bpscan = (ParallelBlockTableScanDesc) scan->rs_base.rs_parallel;
		scan->rs_nblocks = bpscan->phs_nblocks;
	}
	else
		scan->rs_nblocks = RelationGetNumberOfBlocks(scan->rs_base.rs_rd);

	/*
	 * If the table is large relative to NBuffers, use a bulk-read access
	 * strategy and enable synchronized scanning (see syncscan.c).  Although
	 * the thresholds for these features could be different, we make them the
	 * same so that there are only two behaviors to tune rather than four.
	 * (However, some callers need to be able to disable one or both of these
	 * behaviors, independently of the size of the table; also there is a GUC
	 * variable that can disable synchronized scanning.)
	 *
	 * Note that table_block_parallelscan_initialize has a very similar test;
	 * if you change this, consider changing that one, too.
	 */
	if (!RelationUsesLocalBuffers(scan->rs_base.rs_rd) &&
		scan->rs_nblocks > NBuffers / 4)
	{
		allow_strat = (scan->rs_base.rs_flags & SO_ALLOW_STRAT) != 0;
		allow_sync = (scan->rs_base.rs_flags & SO_ALLOW_SYNC) != 0;
	}
	else
		allow_strat = allow_sync = false;

	if (allow_strat)
	{
		/* During a rescan, keep the previous strategy object. */
		if (scan->rs_strategy == NULL)
			scan->rs_strategy = GetAccessStrategy(BAS_BULKREAD);
	}
	else
	{
		if (scan->rs_strategy != NULL)
			FreeAccessStrategy(scan->rs_strategy);
		scan->rs_strategy = NULL;
	}

	if (scan->rs_base.rs_parallel != NULL)
	{
		/* For parallel scan, believe whatever ParallelTableScanDesc says. */
		if (scan->rs_base.rs_parallel->phs_syncscan)
			scan->rs_base.rs_flags |= SO_ALLOW_SYNC;
		else
			scan->rs_base.rs_flags &= ~SO_ALLOW_SYNC;
	}
	else if (keep_startblock)
	{
		/*
		 * When rescanning, we want to keep the previous startblock setting,
		 * so that rewinding a cursor doesn't generate surprising results.
		 * Reset the active syncscan setting, though.
		 */
		if (allow_sync && synchronize_seqscans)
			scan->rs_base.rs_flags |= SO_ALLOW_SYNC;
		else
			scan->rs_base.rs_flags &= ~SO_ALLOW_SYNC;
	}
	else if (allow_sync && synchronize_seqscans)
	{
		scan->rs_base.rs_flags |= SO_ALLOW_SYNC;
		scan->rs_startblock = ss_get_location(scan->rs_base.rs_rd, scan->rs_nblocks);
	}
	else
	{
		scan->rs_base.rs_flags &= ~SO_ALLOW_SYNC;
		scan->rs_startblock = 0;
	}

	scan->rs_numblocks = InvalidBlockNumber;
	scan->rs_inited = false;
	scan->rs_ctup.t_data = NULL;
	ItemPointerSetInvalid(&scan->rs_ctup.t_self);
	scan->rs_cbuf = InvalidBuffer;
	scan->rs_cblock = InvalidBlockNumber;

	/* page-at-a-time fields are always invalid when not rs_inited */

	/*
	 * copy the scan key, if appropriate
	 */
	if (key != NULL)
		memcpy(scan->rs_base.rs_key, key, scan->rs_base.rs_nkeys * sizeof(ScanKeyData));

	/*
	 * Currently, we only have a stats counter for sequential heap scans (but
	 * e.g for bitmap scans the underlying bitmap index scans will be counted,
	 * and for sample scans we update stats for tuple fetches).
	 */
	if (scan->rs_base.rs_flags & SO_TYPE_SEQSCAN)
		pgstat_count_heap_scan(scan->rs_base.rs_rd);
}