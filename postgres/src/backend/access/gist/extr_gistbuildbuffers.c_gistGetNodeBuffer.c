#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int buffersOnLevelsLen; int /*<<< orphan*/ ** buffersOnLevels; int /*<<< orphan*/  context; int /*<<< orphan*/  nodeBuffersTab; } ;
struct TYPE_6__ {int queuedForEmptying; int isTemp; int level; int /*<<< orphan*/ * pageBuffer; int /*<<< orphan*/  pageBlocknum; scalar_t__ blocksCount; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  GISTSTATE ;
typedef  TYPE_1__ GISTNodeBuffer ;
typedef  TYPE_2__ GISTBuildBuffers ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  InvalidBlockNumber ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ hash_search (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * lcons (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ repalloc (int /*<<< orphan*/ **,int) ; 

GISTNodeBuffer *
gistGetNodeBuffer(GISTBuildBuffers *gfbb, GISTSTATE *giststate,
				  BlockNumber nodeBlocknum, int level)
{
	GISTNodeBuffer *nodeBuffer;
	bool		found;

	/* Find node buffer in hash table */
	nodeBuffer = (GISTNodeBuffer *) hash_search(gfbb->nodeBuffersTab,
												(const void *) &nodeBlocknum,
												HASH_ENTER,
												&found);
	if (!found)
	{
		/*
		 * Node buffer wasn't found. Initialize the new buffer as empty.
		 */
		MemoryContext oldcxt = MemoryContextSwitchTo(gfbb->context);

		/* nodeBuffer->nodeBlocknum is the hash key and was filled in already */
		nodeBuffer->blocksCount = 0;
		nodeBuffer->pageBlocknum = InvalidBlockNumber;
		nodeBuffer->pageBuffer = NULL;
		nodeBuffer->queuedForEmptying = false;
		nodeBuffer->isTemp = false;
		nodeBuffer->level = level;

		/*
		 * Add this buffer to the list of buffers on this level. Enlarge
		 * buffersOnLevels array if needed.
		 */
		if (level >= gfbb->buffersOnLevelsLen)
		{
			int			i;

			gfbb->buffersOnLevels =
				(List **) repalloc(gfbb->buffersOnLevels,
								   (level + 1) * sizeof(List *));

			/* initialize the enlarged portion */
			for (i = gfbb->buffersOnLevelsLen; i <= level; i++)
				gfbb->buffersOnLevels[i] = NIL;
			gfbb->buffersOnLevelsLen = level + 1;
		}

		/*
		 * Prepend the new buffer to the list of buffers on this level. It's
		 * not arbitrary that the new buffer is put to the beginning of the
		 * list: in the final emptying phase we loop through all buffers at
		 * each level, and flush them. If a page is split during the emptying,
		 * it's more efficient to flush the new splitted pages first, before
		 * moving on to pre-existing pages on the level. The buffers just
		 * created during the page split are likely still in cache, so
		 * flushing them immediately is more efficient than putting them to
		 * the end of the queue.
		 */
		gfbb->buffersOnLevels[level] = lcons(nodeBuffer,
											 gfbb->buffersOnLevels[level]);

		MemoryContextSwitchTo(oldcxt);
	}

	return nodeBuffer;
}