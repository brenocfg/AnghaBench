#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* TableScanDesc ;
struct TYPE_13__ {int /*<<< orphan*/ * t_data; } ;
struct TYPE_10__ {int rs_flags; int /*<<< orphan*/  rs_rd; int /*<<< orphan*/  rs_key; int /*<<< orphan*/  rs_nkeys; } ;
struct TYPE_14__ {TYPE_4__ rs_ctup; TYPE_1__ rs_base; } ;
struct TYPE_12__ {TYPE_2__* rs_rd; } ;
struct TYPE_11__ {scalar_t__ rd_tableam; } ;
typedef  int /*<<< orphan*/  ScanDirection ;
typedef  TYPE_4__* HeapTuple ;
typedef  TYPE_5__* HeapScanDesc ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GetHeapamTableAmRoutine () ; 
 int /*<<< orphan*/  HEAPDEBUG_1 ; 
 int /*<<< orphan*/  HEAPDEBUG_2 ; 
 int /*<<< orphan*/  HEAPDEBUG_3 ; 
 int SO_ALLOW_PAGEMODE ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg_internal (char*) ; 
 int /*<<< orphan*/  heapgettup (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heapgettup_pagemode (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgstat_count_heap_getnext (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

HeapTuple
heap_getnext(TableScanDesc sscan, ScanDirection direction)
{
	HeapScanDesc scan = (HeapScanDesc) sscan;

	/*
	 * This is still widely used directly, without going through table AM, so
	 * add a safety check.  It's possible we should, at a later point,
	 * downgrade this to an assert. The reason for checking the AM routine,
	 * rather than the AM oid, is that this allows to write regression tests
	 * that create another AM reusing the heap handler.
	 */
	if (unlikely(sscan->rs_rd->rd_tableam != GetHeapamTableAmRoutine()))
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg_internal("only heap AM is supported")));

	/* Note: no locking manipulations needed */

	HEAPDEBUG_1;				/* heap_getnext( info ) */

	if (scan->rs_base.rs_flags & SO_ALLOW_PAGEMODE)
		heapgettup_pagemode(scan, direction,
							scan->rs_base.rs_nkeys, scan->rs_base.rs_key);
	else
		heapgettup(scan, direction,
				   scan->rs_base.rs_nkeys, scan->rs_base.rs_key);

	if (scan->rs_ctup.t_data == NULL)
	{
		HEAPDEBUG_2;			/* heap_getnext returning EOS */
		return NULL;
	}

	/*
	 * if we get here it means we have a new current scan tuple, so point to
	 * the proper return buffer and return the tuple.
	 */
	HEAPDEBUG_3;				/* heap_getnext returning tuple */

	pgstat_count_heap_getnext(scan->rs_base.rs_rd);

	return &scan->rs_ctup;
}