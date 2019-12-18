#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ rootBlkno; int fullScan; scalar_t__ (* findChildPage ) (TYPE_2__*,TYPE_1__*) ;int /*<<< orphan*/  index; scalar_t__ (* isMoveRight ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_12__ {scalar_t__ blkno; int predictNumber; void* buffer; struct TYPE_12__* parent; int /*<<< orphan*/  off; } ;
struct TYPE_11__ {scalar_t__ rightlink; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_1__ GinBtreeStack ;
typedef  TYPE_2__* GinBtree ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BufferGetPage (void*) ; 
 int /*<<< orphan*/  CheckForSerializableConflictIn (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  GIN_UNLOCK ; 
 TYPE_10__* GinPageGetOpaque (int /*<<< orphan*/ ) ; 
 scalar_t__ GinPageIsIncompleteSplit (int /*<<< orphan*/ ) ; 
 scalar_t__ GinPageIsLeaf (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidBlockNumber ; 
 int /*<<< orphan*/  InvalidOffsetNumber ; 
 int /*<<< orphan*/  LockBuffer (void*,int /*<<< orphan*/ ) ; 
 void* ReadBuffer (int /*<<< orphan*/ ,scalar_t__) ; 
 void* ReleaseAndReadBuffer (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TestForOldSnapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ginFinishSplit (TYPE_2__*,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 void* ginStepRight (void*,int /*<<< orphan*/ ,int) ; 
 int ginTraverseLock (void*,int) ; 
 scalar_t__ palloc (int) ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_2__*,TYPE_1__*) ; 

GinBtreeStack *
ginFindLeafPage(GinBtree btree, bool searchMode,
				bool rootConflictCheck, Snapshot snapshot)
{
	GinBtreeStack *stack;

	stack = (GinBtreeStack *) palloc(sizeof(GinBtreeStack));
	stack->blkno = btree->rootBlkno;
	stack->buffer = ReadBuffer(btree->index, btree->rootBlkno);
	stack->parent = NULL;
	stack->predictNumber = 1;

	if (rootConflictCheck)
		CheckForSerializableConflictIn(btree->index, NULL, stack->buffer);

	for (;;)
	{
		Page		page;
		BlockNumber child;
		int			access;

		stack->off = InvalidOffsetNumber;

		page = BufferGetPage(stack->buffer);
		TestForOldSnapshot(snapshot, btree->index, page);

		access = ginTraverseLock(stack->buffer, searchMode);

		/*
		 * If we're going to modify the tree, finish any incomplete splits we
		 * encounter on the way.
		 */
		if (!searchMode && GinPageIsIncompleteSplit(page))
			ginFinishSplit(btree, stack, false, NULL);

		/*
		 * ok, page is correctly locked, we should check to move right ..,
		 * root never has a right link, so small optimization
		 */
		while (btree->fullScan == false && stack->blkno != btree->rootBlkno &&
			   btree->isMoveRight(btree, page))
		{
			BlockNumber rightlink = GinPageGetOpaque(page)->rightlink;

			if (rightlink == InvalidBlockNumber)
				/* rightmost page */
				break;

			stack->buffer = ginStepRight(stack->buffer, btree->index, access);
			stack->blkno = rightlink;
			page = BufferGetPage(stack->buffer);
			TestForOldSnapshot(snapshot, btree->index, page);

			if (!searchMode && GinPageIsIncompleteSplit(page))
				ginFinishSplit(btree, stack, false, NULL);
		}

		if (GinPageIsLeaf(page))	/* we found, return locked page */
			return stack;

		/* now we have correct buffer, try to find child */
		child = btree->findChildPage(btree, stack);

		LockBuffer(stack->buffer, GIN_UNLOCK);
		Assert(child != InvalidBlockNumber);
		Assert(stack->blkno != child);

		if (searchMode)
		{
			/* in search mode we may forget path to leaf */
			stack->blkno = child;
			stack->buffer = ReleaseAndReadBuffer(stack->buffer, btree->index, stack->blkno);
		}
		else
		{
			GinBtreeStack *ptr = (GinBtreeStack *) palloc(sizeof(GinBtreeStack));

			ptr->parent = stack;
			stack = ptr;
			stack->blkno = child;
			stack->buffer = ReadBuffer(btree->index, stack->blkno);
			stack->predictNumber = 1;
		}
	}
}