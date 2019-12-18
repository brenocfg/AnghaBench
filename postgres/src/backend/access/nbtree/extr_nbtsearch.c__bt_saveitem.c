#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ nextTupleOffset; TYPE_3__* items; } ;
struct TYPE_12__ {TYPE_1__ currPos; scalar_t__ currTuples; } ;
struct TYPE_11__ {scalar_t__ tupleOffset; int /*<<< orphan*/  indexOffset; int /*<<< orphan*/  heapTid; } ;
struct TYPE_10__ {int /*<<< orphan*/  t_tid; } ;
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  TYPE_2__* IndexTuple ;
typedef  TYPE_3__ BTScanPosItem ;
typedef  TYPE_4__* BTScanOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  IndexTupleSize (TYPE_2__*) ; 
 scalar_t__ MAXALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_bt_saveitem(BTScanOpaque so, int itemIndex,
			 OffsetNumber offnum, IndexTuple itup)
{
	BTScanPosItem *currItem = &so->currPos.items[itemIndex];

	currItem->heapTid = itup->t_tid;
	currItem->indexOffset = offnum;
	if (so->currTuples)
	{
		Size		itupsz = IndexTupleSize(itup);

		currItem->tupleOffset = so->currPos.nextTupleOffset;
		memcpy(so->currTuples + so->currPos.nextTupleOffset, itup, itupsz);
		so->currPos.nextTupleOffset += MAXALIGN(itupsz);
	}
}