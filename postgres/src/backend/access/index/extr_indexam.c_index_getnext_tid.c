#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* rd_indam; } ;
struct TYPE_7__ {int kill_prior_tuple; int xs_heap_continue; int /*<<< orphan*/  xs_heaptid; TYPE_4__* indexRelation; scalar_t__ xs_heapfetch; } ;
struct TYPE_6__ {int (* amgettuple ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  ScanDirection ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  TYPE_2__* IndexScanDesc ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_SCAN_PROCEDURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemPointerIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RecentGlobalXmin ; 
 int /*<<< orphan*/  SCAN_CHECKS ; 
 int /*<<< orphan*/  TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amgettuple ; 
 int /*<<< orphan*/  pgstat_count_index_tuples (TYPE_4__*,int) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_index_fetch_reset (scalar_t__) ; 

ItemPointer
index_getnext_tid(IndexScanDesc scan, ScanDirection direction)
{
	bool		found;

	SCAN_CHECKS;
	CHECK_SCAN_PROCEDURE(amgettuple);

	Assert(TransactionIdIsValid(RecentGlobalXmin));

	/*
	 * The AM's amgettuple proc finds the next index entry matching the scan
	 * keys, and puts the TID into scan->xs_heaptid.  It should also set
	 * scan->xs_recheck and possibly scan->xs_itup/scan->xs_hitup, though we
	 * pay no attention to those fields here.
	 */
	found = scan->indexRelation->rd_indam->amgettuple(scan, direction);

	/* Reset kill flag immediately for safety */
	scan->kill_prior_tuple = false;
	scan->xs_heap_continue = false;

	/* If we're out of index entries, we're done */
	if (!found)
	{
		/* release resources (like buffer pins) from table accesses */
		if (scan->xs_heapfetch)
			table_index_fetch_reset(scan->xs_heapfetch);

		return NULL;
	}
	Assert(ItemPointerIsValid(&scan->xs_heaptid));

	pgstat_count_index_tuples(scan->indexRelation, 1);

	/* Return the TID of the tuple we found. */
	return &scan->xs_heaptid;
}