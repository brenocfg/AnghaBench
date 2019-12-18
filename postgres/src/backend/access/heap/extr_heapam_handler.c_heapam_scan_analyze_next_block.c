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
typedef  TYPE_1__* TableScanDesc ;
struct TYPE_5__ {int /*<<< orphan*/  rs_cbuf; int /*<<< orphan*/  rs_cindex; int /*<<< orphan*/  rs_cblock; } ;
struct TYPE_4__ {int /*<<< orphan*/  rs_rd; } ;
typedef  TYPE_2__* HeapScanDesc ;
typedef  int /*<<< orphan*/  BufferAccessStrategy ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_LOCK_SHARE ; 
 int /*<<< orphan*/  FirstOffsetNumber ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 int /*<<< orphan*/  RBM_NORMAL ; 
 int /*<<< orphan*/  ReadBufferExtended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
heapam_scan_analyze_next_block(TableScanDesc scan, BlockNumber blockno,
							   BufferAccessStrategy bstrategy)
{
	HeapScanDesc hscan = (HeapScanDesc) scan;

	/*
	 * We must maintain a pin on the target page's buffer to ensure that
	 * concurrent activity - e.g. HOT pruning - doesn't delete tuples out from
	 * under us.  Hence, pin the page until we are done looking at it.  We
	 * also choose to hold sharelock on the buffer throughout --- we could
	 * release and re-acquire sharelock for each tuple, but since we aren't
	 * doing much work per tuple, the extra lock traffic is probably better
	 * avoided.
	 */
	hscan->rs_cblock = blockno;
	hscan->rs_cindex = FirstOffsetNumber;
	hscan->rs_cbuf = ReadBufferExtended(scan->rs_rd, MAIN_FORKNUM,
										blockno, RBM_NORMAL, bstrategy);
	LockBuffer(hscan->rs_cbuf, BUFFER_LOCK_SHARE);

	/* in heap all blocks can contain tuples, so always return true */
	return true;
}