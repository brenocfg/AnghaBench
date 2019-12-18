#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_8__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int itemIndex; } ;
struct TYPE_10__ {scalar_t__ numArrayKeys; int* killedItems; int numKilled; TYPE_8__ currPos; } ;
struct TYPE_9__ {int xs_recheck; scalar_t__ kill_prior_tuple; int /*<<< orphan*/  opaque; } ;
typedef  int /*<<< orphan*/  ScanDirection ;
typedef  TYPE_1__* IndexScanDesc ;
typedef  TYPE_2__* BTScanOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  BTScanPosIsValid (TYPE_8__) ; 
 int MaxIndexTuplesPerPage ; 
 scalar_t__ _bt_advance_array_keys (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int _bt_first (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int _bt_next (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_start_array_keys (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 

bool
btgettuple(IndexScanDesc scan, ScanDirection dir)
{
	BTScanOpaque so = (BTScanOpaque) scan->opaque;
	bool		res;

	/* btree indexes are never lossy */
	scan->xs_recheck = false;

	/*
	 * If we have any array keys, initialize them during first call for a
	 * scan.  We can't do this in btrescan because we don't know the scan
	 * direction at that time.
	 */
	if (so->numArrayKeys && !BTScanPosIsValid(so->currPos))
	{
		/* punt if we have any unsatisfiable array keys */
		if (so->numArrayKeys < 0)
			return false;

		_bt_start_array_keys(scan, dir);
	}

	/* This loop handles advancing to the next array elements, if any */
	do
	{
		/*
		 * If we've already initialized this scan, we can just advance it in
		 * the appropriate direction.  If we haven't done so yet, we call
		 * _bt_first() to get the first item in the scan.
		 */
		if (!BTScanPosIsValid(so->currPos))
			res = _bt_first(scan, dir);
		else
		{
			/*
			 * Check to see if we should kill the previously-fetched tuple.
			 */
			if (scan->kill_prior_tuple)
			{
				/*
				 * Yes, remember it for later. (We'll deal with all such
				 * tuples at once right before leaving the index page.)  The
				 * test for numKilled overrun is not just paranoia: if the
				 * caller reverses direction in the indexscan then the same
				 * item might get entered multiple times. It's not worth
				 * trying to optimize that, so we don't detect it, but instead
				 * just forget any excess entries.
				 */
				if (so->killedItems == NULL)
					so->killedItems = (int *)
						palloc(MaxIndexTuplesPerPage * sizeof(int));
				if (so->numKilled < MaxIndexTuplesPerPage)
					so->killedItems[so->numKilled++] = so->currPos.itemIndex;
			}

			/*
			 * Now continue the scan.
			 */
			res = _bt_next(scan, dir);
		}

		/* If we have a tuple, return it ... */
		if (res)
			break;
		/* ... otherwise see if we have more array keys to deal with */
	} while (so->numArrayKeys && _bt_advance_array_keys(scan, dir));

	return res;
}