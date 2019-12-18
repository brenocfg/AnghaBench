#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64 ;
struct TYPE_11__ {scalar_t__ itemIndex; scalar_t__ lastItem; TYPE_1__* items; } ;
struct TYPE_13__ {scalar_t__ numArrayKeys; TYPE_2__ currPos; } ;
struct TYPE_12__ {int /*<<< orphan*/  xs_heaptid; int /*<<< orphan*/  opaque; } ;
struct TYPE_10__ {int /*<<< orphan*/  heapTid; } ;
typedef  int /*<<< orphan*/  TIDBitmap ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  TYPE_3__* IndexScanDesc ;
typedef  TYPE_4__* BTScanOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  ForwardScanDirection ; 
 scalar_t__ _bt_advance_array_keys (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ _bt_first (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_next (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_start_array_keys (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tbm_add_tuples (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

int64
btgetbitmap(IndexScanDesc scan, TIDBitmap *tbm)
{
	BTScanOpaque so = (BTScanOpaque) scan->opaque;
	int64		ntids = 0;
	ItemPointer heapTid;

	/*
	 * If we have any array keys, initialize them.
	 */
	if (so->numArrayKeys)
	{
		/* punt if we have any unsatisfiable array keys */
		if (so->numArrayKeys < 0)
			return ntids;

		_bt_start_array_keys(scan, ForwardScanDirection);
	}

	/* This loop handles advancing to the next array elements, if any */
	do
	{
		/* Fetch the first page & tuple */
		if (_bt_first(scan, ForwardScanDirection))
		{
			/* Save tuple ID, and continue scanning */
			heapTid = &scan->xs_heaptid;
			tbm_add_tuples(tbm, heapTid, 1, false);
			ntids++;

			for (;;)
			{
				/*
				 * Advance to next tuple within page.  This is the same as the
				 * easy case in _bt_next().
				 */
				if (++so->currPos.itemIndex > so->currPos.lastItem)
				{
					/* let _bt_next do the heavy lifting */
					if (!_bt_next(scan, ForwardScanDirection))
						break;
				}

				/* Save tuple ID, and continue scanning */
				heapTid = &so->currPos.items[so->currPos.itemIndex].heapTid;
				tbm_add_tuples(tbm, heapTid, 1, false);
				ntids++;
			}
		}
		/* Now see if we have more array keys to deal with */
	} while (so->numArrayKeys && _bt_advance_array_keys(scan, ForwardScanDirection));

	return ntids;
}