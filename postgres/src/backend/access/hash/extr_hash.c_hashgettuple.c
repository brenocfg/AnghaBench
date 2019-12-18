#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int itemIndex; } ;
struct TYPE_8__ {int* killedItems; int numKilled; TYPE_6__ currPos; } ;
struct TYPE_7__ {int xs_recheck; scalar_t__ kill_prior_tuple; int /*<<< orphan*/  opaque; } ;
typedef  int /*<<< orphan*/  ScanDirection ;
typedef  TYPE_1__* IndexScanDesc ;
typedef  TYPE_2__* HashScanOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  HashScanPosIsValid (TYPE_6__) ; 
 int MaxIndexTuplesPerPage ; 
 int _hash_first (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int _hash_next (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 

bool
hashgettuple(IndexScanDesc scan, ScanDirection dir)
{
	HashScanOpaque so = (HashScanOpaque) scan->opaque;
	bool		res;

	/* Hash indexes are always lossy since we store only the hash code */
	scan->xs_recheck = true;

	/*
	 * If we've already initialized this scan, we can just advance it in the
	 * appropriate direction.  If we haven't done so yet, we call a routine to
	 * get the first item in the scan.
	 */
	if (!HashScanPosIsValid(so->currPos))
		res = _hash_first(scan, dir);
	else
	{
		/*
		 * Check to see if we should kill the previously-fetched tuple.
		 */
		if (scan->kill_prior_tuple)
		{
			/*
			 * Yes, so remember it for later. (We'll deal with all such tuples
			 * at once right after leaving the index page or at end of scan.)
			 * In case if caller reverses the indexscan direction it is quite
			 * possible that the same item might get entered multiple times.
			 * But, we don't detect that; instead, we just forget any excess
			 * entries.
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
		res = _hash_next(scan, dir);
	}

	return res;
}