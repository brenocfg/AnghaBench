#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  bs_bdesc; int /*<<< orphan*/  bs_dtuple; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  IndexInfo ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BrinTuple ;
typedef  int /*<<< orphan*/  BrinRevmap ;
typedef  TYPE_1__ BrinBuildState ;
typedef  int BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BRIN_ALL_BLOCKRANGES ; 
 int /*<<< orphan*/  BUFFER_LOCK_SHARE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BuildIndexInfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int Min (int,int) ; 
 int RelationGetNumberOfBlocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * brinGetTupleForHeapBlock (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * brinRevmapInitialize (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brinRevmapTerminate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brin_memtuple_initialize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* initialize_brin_buildstate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  summarize_range (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  terminate_brin_buildstate (TYPE_1__*) ; 

__attribute__((used)) static void
brinsummarize(Relation index, Relation heapRel, BlockNumber pageRange,
			  bool include_partial, double *numSummarized, double *numExisting)
{
	BrinRevmap *revmap;
	BrinBuildState *state = NULL;
	IndexInfo  *indexInfo = NULL;
	BlockNumber heapNumBlocks;
	BlockNumber pagesPerRange;
	Buffer		buf;
	BlockNumber startBlk;

	revmap = brinRevmapInitialize(index, &pagesPerRange, NULL);

	/* determine range of pages to process */
	heapNumBlocks = RelationGetNumberOfBlocks(heapRel);
	if (pageRange == BRIN_ALL_BLOCKRANGES)
		startBlk = 0;
	else
	{
		startBlk = (pageRange / pagesPerRange) * pagesPerRange;
		heapNumBlocks = Min(heapNumBlocks, startBlk + pagesPerRange);
	}
	if (startBlk > heapNumBlocks)
	{
		/* Nothing to do if start point is beyond end of table */
		brinRevmapTerminate(revmap);
		return;
	}

	/*
	 * Scan the revmap to find unsummarized items.
	 */
	buf = InvalidBuffer;
	for (; startBlk < heapNumBlocks; startBlk += pagesPerRange)
	{
		BrinTuple  *tup;
		OffsetNumber off;

		/*
		 * Unless requested to summarize even a partial range, go away now if
		 * we think the next range is partial.  Caller would pass true when it
		 * is typically run once bulk data loading is done
		 * (brin_summarize_new_values), and false when it is typically the
		 * result of arbitrarily-scheduled maintenance command (vacuuming).
		 */
		if (!include_partial &&
			(startBlk + pagesPerRange > heapNumBlocks))
			break;

		CHECK_FOR_INTERRUPTS();

		tup = brinGetTupleForHeapBlock(revmap, startBlk, &buf, &off, NULL,
									   BUFFER_LOCK_SHARE, NULL);
		if (tup == NULL)
		{
			/* no revmap entry for this heap range. Summarize it. */
			if (state == NULL)
			{
				/* first time through */
				Assert(!indexInfo);
				state = initialize_brin_buildstate(index, revmap,
												   pagesPerRange);
				indexInfo = BuildIndexInfo(index);
			}
			summarize_range(indexInfo, state, heapRel, startBlk, heapNumBlocks);

			/* and re-initialize state for the next range */
			brin_memtuple_initialize(state->bs_dtuple, state->bs_bdesc);

			if (numSummarized)
				*numSummarized += 1.0;
		}
		else
		{
			if (numExisting)
				*numExisting += 1.0;
			LockBuffer(buf, BUFFER_LOCK_UNLOCK);
		}
	}

	if (BufferIsValid(buf))
		ReleaseBuffer(buf);

	/* free resources */
	brinRevmapTerminate(revmap);
	if (state)
	{
		terminate_brin_buildstate(state);
		pfree(indexInfo);
	}
}