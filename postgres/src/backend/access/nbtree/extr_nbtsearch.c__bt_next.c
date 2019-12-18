#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ itemIndex; scalar_t__ lastItem; scalar_t__ firstItem; TYPE_3__* items; } ;
struct TYPE_10__ {scalar_t__ currTuples; TYPE_1__ currPos; } ;
struct TYPE_9__ {scalar_t__ tupleOffset; int /*<<< orphan*/  heapTid; } ;
struct TYPE_8__ {scalar_t__ xs_itup; scalar_t__ xs_want_itup; int /*<<< orphan*/  xs_heaptid; int /*<<< orphan*/  opaque; } ;
typedef  int /*<<< orphan*/  ScanDirection ;
typedef  scalar_t__ IndexTuple ;
typedef  TYPE_2__* IndexScanDesc ;
typedef  TYPE_3__ BTScanPosItem ;
typedef  TYPE_4__* BTScanOpaque ;

/* Variables and functions */
 scalar_t__ ScanDirectionIsForward (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_steppage (TYPE_2__*,int /*<<< orphan*/ ) ; 

bool
_bt_next(IndexScanDesc scan, ScanDirection dir)
{
	BTScanOpaque so = (BTScanOpaque) scan->opaque;
	BTScanPosItem *currItem;

	/*
	 * Advance to next tuple on current page; or if there's no more, try to
	 * step to the next page with data.
	 */
	if (ScanDirectionIsForward(dir))
	{
		if (++so->currPos.itemIndex > so->currPos.lastItem)
		{
			if (!_bt_steppage(scan, dir))
				return false;
		}
	}
	else
	{
		if (--so->currPos.itemIndex < so->currPos.firstItem)
		{
			if (!_bt_steppage(scan, dir))
				return false;
		}
	}

	/* OK, itemIndex says what to return */
	currItem = &so->currPos.items[so->currPos.itemIndex];
	scan->xs_heaptid = currItem->heapTid;
	if (scan->xs_want_itup)
		scan->xs_itup = (IndexTuple) (so->currTuples + currItem->tupleOffset);

	return true;
}