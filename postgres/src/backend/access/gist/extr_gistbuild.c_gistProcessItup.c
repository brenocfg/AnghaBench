#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  indexrel; int /*<<< orphan*/ * gfbb; int /*<<< orphan*/ * giststate; } ;
struct TYPE_13__ {int /*<<< orphan*/  t_tid; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  TYPE_1__* IndexTuple ;
typedef  int /*<<< orphan*/  GISTSTATE ;
typedef  int /*<<< orphan*/  GISTNodeBuffer ;
typedef  TYPE_2__ GISTBuildState ;
typedef  int /*<<< orphan*/  GISTBuildBuffers ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BUFFER_OVERFLOWED (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  GIST_EXCLUSIVE ; 
 int /*<<< orphan*/  InvalidBlockNumber ; 
 int /*<<< orphan*/  InvalidOffsetNumber ; 
 int /*<<< orphan*/  ItemPointerGetBlockNumber (int /*<<< orphan*/ *) ; 
 scalar_t__ LEVEL_HAS_BUFFERS (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetItem (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gistGetNodeBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gistMemorizeParent (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gistPushItupToNodeBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  gistbufferinginserttuples (TYPE_2__*,int /*<<< orphan*/ ,int,TYPE_1__**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gistchoose (int /*<<< orphan*/ ,scalar_t__,TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* gistgetadjusted (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
gistProcessItup(GISTBuildState *buildstate, IndexTuple itup,
				BlockNumber startblkno, int startlevel)
{
	GISTSTATE  *giststate = buildstate->giststate;
	GISTBuildBuffers *gfbb = buildstate->gfbb;
	Relation	indexrel = buildstate->indexrel;
	BlockNumber childblkno;
	Buffer		buffer;
	bool		result = false;
	BlockNumber blkno;
	int			level;
	OffsetNumber downlinkoffnum = InvalidOffsetNumber;
	BlockNumber parentblkno = InvalidBlockNumber;

	CHECK_FOR_INTERRUPTS();

	/*
	 * Loop until we reach a leaf page (level == 0) or a level with buffers
	 * (not including the level we start at, because we would otherwise make
	 * no progress).
	 */
	blkno = startblkno;
	level = startlevel;
	for (;;)
	{
		ItemId		iid;
		IndexTuple	idxtuple,
					newtup;
		Page		page;
		OffsetNumber childoffnum;

		/* Have we reached a level with buffers? */
		if (LEVEL_HAS_BUFFERS(level, gfbb) && level != startlevel)
			break;

		/* Have we reached a leaf page? */
		if (level == 0)
			break;

		/*
		 * Nope. Descend down to the next level then. Choose a child to
		 * descend down to.
		 */

		buffer = ReadBuffer(indexrel, blkno);
		LockBuffer(buffer, GIST_EXCLUSIVE);

		page = (Page) BufferGetPage(buffer);
		childoffnum = gistchoose(indexrel, page, itup, giststate);
		iid = PageGetItemId(page, childoffnum);
		idxtuple = (IndexTuple) PageGetItem(page, iid);
		childblkno = ItemPointerGetBlockNumber(&(idxtuple->t_tid));

		if (level > 1)
			gistMemorizeParent(buildstate, childblkno, blkno);

		/*
		 * Check that the key representing the target child node is consistent
		 * with the key we're inserting. Update it if it's not.
		 */
		newtup = gistgetadjusted(indexrel, idxtuple, itup, giststate);
		if (newtup)
		{
			blkno = gistbufferinginserttuples(buildstate,
											  buffer,
											  level,
											  &newtup,
											  1,
											  childoffnum,
											  InvalidBlockNumber,
											  InvalidOffsetNumber);
			/* gistbufferinginserttuples() released the buffer */
		}
		else
			UnlockReleaseBuffer(buffer);

		/* Descend to the child */
		parentblkno = blkno;
		blkno = childblkno;
		downlinkoffnum = childoffnum;
		Assert(level > 0);
		level--;
	}

	if (LEVEL_HAS_BUFFERS(level, gfbb))
	{
		/*
		 * We've reached level with buffers. Place the index tuple to the
		 * buffer, and add the buffer to the emptying queue if it overflows.
		 */
		GISTNodeBuffer *childNodeBuffer;

		/* Find the buffer or create a new one */
		childNodeBuffer = gistGetNodeBuffer(gfbb, giststate, blkno, level);

		/* Add index tuple to it */
		gistPushItupToNodeBuffer(gfbb, childNodeBuffer, itup);

		if (BUFFER_OVERFLOWED(childNodeBuffer, gfbb))
			result = true;
	}
	else
	{
		/*
		 * We've reached a leaf page. Place the tuple here.
		 */
		Assert(level == 0);
		buffer = ReadBuffer(indexrel, blkno);
		LockBuffer(buffer, GIST_EXCLUSIVE);
		gistbufferinginserttuples(buildstate, buffer, level,
								  &itup, 1, InvalidOffsetNumber,
								  parentblkno, downlinkoffnum);
		/* gistbufferinginserttuples() released the buffer */
	}

	return result;
}