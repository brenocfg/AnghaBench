#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ prev; } ;
struct TYPE_13__ {int /*<<< orphan*/  pfile; } ;
struct TYPE_12__ {scalar_t__ blocksCount; TYPE_3__* pageBuffer; } ;
typedef  int /*<<< orphan*/  IndexTuple ;
typedef  TYPE_1__ GISTNodeBuffer ;
typedef  TYPE_2__ GISTBuildBuffers ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ InvalidBlockNumber ; 
 scalar_t__ PAGE_IS_EMPTY (TYPE_3__*) ; 
 int /*<<< orphan*/  ReadTempFileBlock (int /*<<< orphan*/ ,scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  gistBuffersReleaseBlock (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  gistGetItupFromPage (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gistLoadNodeBuffer (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  pfree (TYPE_3__*) ; 

bool
gistPopItupFromNodeBuffer(GISTBuildBuffers *gfbb, GISTNodeBuffer *nodeBuffer,
						  IndexTuple *itup)
{
	/*
	 * If node buffer is empty then return false.
	 */
	if (nodeBuffer->blocksCount <= 0)
		return false;

	/* Load last page of node buffer if needed */
	if (!nodeBuffer->pageBuffer)
		gistLoadNodeBuffer(gfbb, nodeBuffer);

	/*
	 * Get index tuple from last non-empty page.
	 */
	gistGetItupFromPage(nodeBuffer->pageBuffer, itup);

	/*
	 * If we just removed the last tuple from the page, fetch previous page on
	 * this node buffer (if any).
	 */
	if (PAGE_IS_EMPTY(nodeBuffer->pageBuffer))
	{
		BlockNumber prevblkno;

		/*
		 * blocksCount includes the page in pageBuffer, so decrease it now.
		 */
		nodeBuffer->blocksCount--;

		/*
		 * If there's more pages, fetch previous one.
		 */
		prevblkno = nodeBuffer->pageBuffer->prev;
		if (prevblkno != InvalidBlockNumber)
		{
			/* There is a previous page. Fetch it. */
			Assert(nodeBuffer->blocksCount > 0);
			ReadTempFileBlock(gfbb->pfile, prevblkno, nodeBuffer->pageBuffer);

			/*
			 * Now that we've read the block in memory, we can release its
			 * on-disk block for reuse.
			 */
			gistBuffersReleaseBlock(gfbb, prevblkno);
		}
		else
		{
			/* No more pages. Free memory. */
			Assert(nodeBuffer->blocksCount == 0);
			pfree(nodeBuffer->pageBuffer);
			nodeBuffer->pageBuffer = NULL;
		}
	}
	return true;
}