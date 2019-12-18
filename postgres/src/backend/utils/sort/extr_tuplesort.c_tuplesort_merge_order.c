#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int int64 ;

/* Variables and functions */
 int /*<<< orphan*/  MAXORDER ; 
 int MERGE_BUFFER_SIZE ; 
 int /*<<< orphan*/  MINORDER ; 
 int Max (int,int /*<<< orphan*/ ) ; 
 int Min (int,int /*<<< orphan*/ ) ; 
 int TAPE_BUFFER_OVERHEAD ; 

int
tuplesort_merge_order(int64 allowedMem)
{
	int			mOrder;

	/*
	 * We need one tape for each merge input, plus another one for the output,
	 * and each of these tapes needs buffer space.  In addition we want
	 * MERGE_BUFFER_SIZE workspace per input tape (but the output tape doesn't
	 * count).
	 *
	 * Note: you might be thinking we need to account for the memtuples[]
	 * array in this calculation, but we effectively treat that as part of the
	 * MERGE_BUFFER_SIZE workspace.
	 */
	mOrder = (allowedMem - TAPE_BUFFER_OVERHEAD) /
		(MERGE_BUFFER_SIZE + TAPE_BUFFER_OVERHEAD);

	/*
	 * Even in minimum memory, use at least a MINORDER merge.  On the other
	 * hand, even when we have lots of memory, do not use more than a MAXORDER
	 * merge.  Tapes are pretty cheap, but they're not entirely free.  Each
	 * additional tape reduces the amount of memory available to build runs,
	 * which in turn can cause the same sort to need more runs, which makes
	 * merging slower even if it can still be done in a single pass.  Also,
	 * high order merges are quite slow due to CPU cache effects; it can be
	 * faster to pay the I/O cost of a polyphase merge than to perform a
	 * single merge pass across many hundreds of tapes.
	 */
	mOrder = Max(mOrder, MINORDER);
	mOrder = Min(mOrder, MAXORDER);

	return mOrder;
}