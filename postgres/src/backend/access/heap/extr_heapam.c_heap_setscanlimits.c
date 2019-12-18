#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TableScanDesc ;
struct TYPE_3__ {int rs_flags; } ;
struct TYPE_4__ {scalar_t__ rs_nblocks; scalar_t__ rs_numblocks; scalar_t__ rs_startblock; TYPE_1__ rs_base; int /*<<< orphan*/  rs_inited; } ;
typedef  TYPE_2__* HeapScanDesc ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int SO_ALLOW_SYNC ; 

void
heap_setscanlimits(TableScanDesc sscan, BlockNumber startBlk, BlockNumber numBlks)
{
	HeapScanDesc scan = (HeapScanDesc) sscan;

	Assert(!scan->rs_inited);	/* else too late to change */
	/* else rs_startblock is significant */
	Assert(!(scan->rs_base.rs_flags & SO_ALLOW_SYNC));

	/* Check startBlk is valid (but allow case of zero blocks...) */
	Assert(startBlk == 0 || startBlk < scan->rs_nblocks);

	scan->rs_startblock = startBlk;
	scan->rs_numblocks = numBlks;
}