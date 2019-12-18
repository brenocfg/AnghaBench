#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nFreeBlocks; int freeBlocksLen; long* freeBlocks; int blocksSorted; scalar_t__ forgetFreeSpace; } ;
typedef  TYPE_1__ LogicalTapeSet ;

/* Variables and functions */
 scalar_t__ repalloc (long*,int) ; 

__attribute__((used)) static void
ltsReleaseBlock(LogicalTapeSet *lts, long blocknum)
{
	int			ndx;

	/*
	 * Do nothing if we're no longer interested in remembering free space.
	 */
	if (lts->forgetFreeSpace)
		return;

	/*
	 * Enlarge freeBlocks array if full.
	 */
	if (lts->nFreeBlocks >= lts->freeBlocksLen)
	{
		lts->freeBlocksLen *= 2;
		lts->freeBlocks = (long *) repalloc(lts->freeBlocks,
											lts->freeBlocksLen * sizeof(long));
	}

	/*
	 * Add blocknum to array, and mark the array unsorted if it's no longer in
	 * decreasing order.
	 */
	ndx = lts->nFreeBlocks++;
	lts->freeBlocks[ndx] = blocknum;
	if (ndx > 0 && lts->freeBlocks[ndx - 1] < blocknum)
		lts->blocksSorted = false;
}