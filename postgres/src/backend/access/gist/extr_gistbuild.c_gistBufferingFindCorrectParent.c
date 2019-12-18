#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  indexrel; } ;
struct TYPE_5__ {int /*<<< orphan*/  t_tid; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  TYPE_1__* IndexTuple ;
typedef  TYPE_2__ GISTBuildState ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FirstOffsetNumber ; 
 int /*<<< orphan*/  GIST_EXCLUSIVE ; 
 scalar_t__ InvalidBlockNumber ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 scalar_t__ InvalidOffsetNumber ; 
 scalar_t__ ItemPointerGetBlockNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OffsetNumberNext (scalar_t__) ; 
 int /*<<< orphan*/  PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadBuffer (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ gistGetParent (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  gistcheckpage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Buffer
gistBufferingFindCorrectParent(GISTBuildState *buildstate,
							   BlockNumber childblkno, int level,
							   BlockNumber *parentblkno,
							   OffsetNumber *downlinkoffnum)
{
	BlockNumber parent;
	Buffer		buffer;
	Page		page;
	OffsetNumber maxoff;
	OffsetNumber off;

	if (level > 0)
		parent = gistGetParent(buildstate, childblkno);
	else
	{
		/*
		 * For a leaf page, the caller must supply a correct parent block
		 * number.
		 */
		if (*parentblkno == InvalidBlockNumber)
			elog(ERROR, "no parent buffer provided of child %d", childblkno);
		parent = *parentblkno;
	}

	buffer = ReadBuffer(buildstate->indexrel, parent);
	page = BufferGetPage(buffer);
	LockBuffer(buffer, GIST_EXCLUSIVE);
	gistcheckpage(buildstate->indexrel, buffer);
	maxoff = PageGetMaxOffsetNumber(page);

	/* Check if it was not moved */
	if (parent == *parentblkno && *parentblkno != InvalidBlockNumber &&
		*downlinkoffnum != InvalidOffsetNumber && *downlinkoffnum <= maxoff)
	{
		ItemId		iid = PageGetItemId(page, *downlinkoffnum);
		IndexTuple	idxtuple = (IndexTuple) PageGetItem(page, iid);

		if (ItemPointerGetBlockNumber(&(idxtuple->t_tid)) == childblkno)
		{
			/* Still there */
			return buffer;
		}
	}

	/*
	 * Downlink was not at the offset where it used to be. Scan the page to
	 * find it. During normal gist insertions, it might've moved to another
	 * page, to the right, but during a buffering build, we keep track of the
	 * parent of each page in the lookup table so we should always know what
	 * page it's on.
	 */
	for (off = FirstOffsetNumber; off <= maxoff; off = OffsetNumberNext(off))
	{
		ItemId		iid = PageGetItemId(page, off);
		IndexTuple	idxtuple = (IndexTuple) PageGetItem(page, iid);

		if (ItemPointerGetBlockNumber(&(idxtuple->t_tid)) == childblkno)
		{
			/* yes!!, found it */
			*downlinkoffnum = off;
			return buffer;
		}
	}

	elog(ERROR, "failed to re-find parent for block %u", childblkno);
	return InvalidBuffer;		/* keep compiler quiet */
}