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
struct TYPE_5__ {int rs_ntuples; scalar_t__* rs_vistuples; } ;
struct TYPE_4__ {int rs_flags; int /*<<< orphan*/  rs_snapshot; } ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* HeapScanDesc ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int HeapTupleSatisfiesVisibility (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SO_ALLOW_PAGEMODE ; 

__attribute__((used)) static bool
SampleHeapTupleVisible(TableScanDesc scan, Buffer buffer,
					   HeapTuple tuple,
					   OffsetNumber tupoffset)
{
	HeapScanDesc hscan = (HeapScanDesc) scan;

	if (scan->rs_flags & SO_ALLOW_PAGEMODE)
	{
		/*
		 * In pageatatime mode, heapgetpage() already did visibility checks,
		 * so just look at the info it left in rs_vistuples[].
		 *
		 * We use a binary search over the known-sorted array.  Note: we could
		 * save some effort if we insisted that NextSampleTuple select tuples
		 * in increasing order, but it's not clear that there would be enough
		 * gain to justify the restriction.
		 */
		int			start = 0,
					end = hscan->rs_ntuples - 1;

		while (start <= end)
		{
			int			mid = (start + end) / 2;
			OffsetNumber curoffset = hscan->rs_vistuples[mid];

			if (tupoffset == curoffset)
				return true;
			else if (tupoffset < curoffset)
				end = mid - 1;
			else
				start = mid + 1;
		}

		return false;
	}
	else
	{
		/* Otherwise, we have to check the tuple individually. */
		return HeapTupleSatisfiesVisibility(tuple, scan->rs_snapshot,
											buffer);
	}
}