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
struct TYPE_3__ {int bs_pagesPerRange; int bs_currRangeStart; int /*<<< orphan*/  bs_dtuple; int /*<<< orphan*/  bs_bdesc; int /*<<< orphan*/  bs_rmAccess; int /*<<< orphan*/  bs_irel; } ;
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  IndexInfo ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BrinTuple ;
typedef  TYPE_1__ BrinBuildState ;
typedef  int BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BUFFER_LOCK_SHARE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int Min (int,int) ; 
 int RelationGetNumberOfBlocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * brinGetTupleForHeapBlock (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int brin_can_do_samepage_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * brin_copy_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brin_doinsert (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int brin_doupdate (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * brin_form_placeholder_tuple (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * brin_form_tuple (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brin_free_tuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brinbuildCallback ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  table_index_build_range_scan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  union_tuples (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
summarize_range(IndexInfo *indexInfo, BrinBuildState *state, Relation heapRel,
				BlockNumber heapBlk, BlockNumber heapNumBlks)
{
	Buffer		phbuf;
	BrinTuple  *phtup;
	Size		phsz;
	OffsetNumber offset;
	BlockNumber scanNumBlks;

	/*
	 * Insert the placeholder tuple
	 */
	phbuf = InvalidBuffer;
	phtup = brin_form_placeholder_tuple(state->bs_bdesc, heapBlk, &phsz);
	offset = brin_doinsert(state->bs_irel, state->bs_pagesPerRange,
						   state->bs_rmAccess, &phbuf,
						   heapBlk, phtup, phsz);

	/*
	 * Compute range end.  We hold ShareUpdateExclusive lock on table, so it
	 * cannot shrink concurrently (but it can grow).
	 */
	Assert(heapBlk % state->bs_pagesPerRange == 0);
	if (heapBlk + state->bs_pagesPerRange > heapNumBlks)
	{
		/*
		 * If we're asked to scan what we believe to be the final range on the
		 * table (i.e. a range that might be partial) we need to recompute our
		 * idea of what the latest page is after inserting the placeholder
		 * tuple.  Anyone that grows the table later will update the
		 * placeholder tuple, so it doesn't matter that we won't scan these
		 * pages ourselves.  Careful: the table might have been extended
		 * beyond the current range, so clamp our result.
		 *
		 * Fortunately, this should occur infrequently.
		 */
		scanNumBlks = Min(RelationGetNumberOfBlocks(heapRel) - heapBlk,
						  state->bs_pagesPerRange);
	}
	else
	{
		/* Easy case: range is known to be complete */
		scanNumBlks = state->bs_pagesPerRange;
	}

	/*
	 * Execute the partial heap scan covering the heap blocks in the specified
	 * page range, summarizing the heap tuples in it.  This scan stops just
	 * short of brinbuildCallback creating the new index entry.
	 *
	 * Note that it is critical we use the "any visible" mode of
	 * table_index_build_range_scan here: otherwise, we would miss tuples
	 * inserted by transactions that are still in progress, among other corner
	 * cases.
	 */
	state->bs_currRangeStart = heapBlk;
	table_index_build_range_scan(heapRel, state->bs_irel, indexInfo, false, true, false,
								 heapBlk, scanNumBlks,
								 brinbuildCallback, (void *) state, NULL);

	/*
	 * Now we update the values obtained by the scan with the placeholder
	 * tuple.  We do this in a loop which only terminates if we're able to
	 * update the placeholder tuple successfully; if we are not, this means
	 * somebody else modified the placeholder tuple after we read it.
	 */
	for (;;)
	{
		BrinTuple  *newtup;
		Size		newsize;
		bool		didupdate;
		bool		samepage;

		CHECK_FOR_INTERRUPTS();

		/*
		 * Update the summary tuple and try to update.
		 */
		newtup = brin_form_tuple(state->bs_bdesc,
								 heapBlk, state->bs_dtuple, &newsize);
		samepage = brin_can_do_samepage_update(phbuf, phsz, newsize);
		didupdate =
			brin_doupdate(state->bs_irel, state->bs_pagesPerRange,
						  state->bs_rmAccess, heapBlk, phbuf, offset,
						  phtup, phsz, newtup, newsize, samepage);
		brin_free_tuple(phtup);
		brin_free_tuple(newtup);

		/* If the update succeeded, we're done. */
		if (didupdate)
			break;

		/*
		 * If the update didn't work, it might be because somebody updated the
		 * placeholder tuple concurrently.  Extract the new version, union it
		 * with the values we have from the scan, and start over.  (There are
		 * other reasons for the update to fail, but it's simple to treat them
		 * the same.)
		 */
		phtup = brinGetTupleForHeapBlock(state->bs_rmAccess, heapBlk, &phbuf,
										 &offset, &phsz, BUFFER_LOCK_SHARE,
										 NULL);
		/* the placeholder tuple must exist */
		if (phtup == NULL)
			elog(ERROR, "missing placeholder tuple");
		phtup = brin_copy_tuple(phtup, phsz, NULL, NULL);
		LockBuffer(phbuf, BUFFER_LOCK_UNLOCK);

		/* merge it into the tuple from the heap scan */
		union_tuples(state->bs_bdesc, state->bs_dtuple, phtup);
	}

	ReleaseBuffer(phbuf);
}