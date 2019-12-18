#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ rightlink; } ;
struct TYPE_7__ {scalar_t__ downlinkoffnum; scalar_t__ lsn; scalar_t__ blkno; void* buffer; struct TYPE_7__* parent; void* page; } ;
struct TYPE_6__ {int /*<<< orphan*/  t_tid; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  void* Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  TYPE_1__* IndexTuple ;
typedef  TYPE_2__ GISTInsertStack ;

/* Variables and functions */
 scalar_t__ BufferGetPage (void*) ; 
 scalar_t__ FirstOffsetNumber ; 
 int /*<<< orphan*/  GIST_EXCLUSIVE ; 
 TYPE_5__* GistPageGetOpaque (void*) ; 
 scalar_t__ InvalidBlockNumber ; 
 scalar_t__ InvalidOffsetNumber ; 
 scalar_t__ ItemPointerGetBlockNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockBuffer (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ OffsetNumberNext (scalar_t__) ; 
 scalar_t__ PageGetItem (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (void*,scalar_t__) ; 
 scalar_t__ PageGetLSN (void*) ; 
 scalar_t__ PageGetMaxOffsetNumber (void*) ; 
 void* ReadBuffer (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ReleaseBuffer (void*) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (void*) ; 
 TYPE_2__* gistFindPath (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  gistcheckpage (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void
gistFindCorrectParent(Relation r, GISTInsertStack *child)
{
	GISTInsertStack *parent = child->parent;

	gistcheckpage(r, parent->buffer);
	parent->page = (Page) BufferGetPage(parent->buffer);

	/* here we don't need to distinguish between split and page update */
	if (child->downlinkoffnum == InvalidOffsetNumber ||
		parent->lsn != PageGetLSN(parent->page))
	{
		/* parent is changed, look child in right links until found */
		OffsetNumber i,
					maxoff;
		ItemId		iid;
		IndexTuple	idxtuple;
		GISTInsertStack *ptr;

		while (true)
		{
			maxoff = PageGetMaxOffsetNumber(parent->page);
			for (i = FirstOffsetNumber; i <= maxoff; i = OffsetNumberNext(i))
			{
				iid = PageGetItemId(parent->page, i);
				idxtuple = (IndexTuple) PageGetItem(parent->page, iid);
				if (ItemPointerGetBlockNumber(&(idxtuple->t_tid)) == child->blkno)
				{
					/* yes!!, found */
					child->downlinkoffnum = i;
					return;
				}
			}

			parent->blkno = GistPageGetOpaque(parent->page)->rightlink;
			UnlockReleaseBuffer(parent->buffer);
			if (parent->blkno == InvalidBlockNumber)
			{
				/*
				 * End of chain and still didn't find parent. It's a very-very
				 * rare situation when root splitted.
				 */
				break;
			}
			parent->buffer = ReadBuffer(r, parent->blkno);
			LockBuffer(parent->buffer, GIST_EXCLUSIVE);
			gistcheckpage(r, parent->buffer);
			parent->page = (Page) BufferGetPage(parent->buffer);
		}

		/*
		 * awful!!, we need search tree to find parent ... , but before we
		 * should release all old parent
		 */

		ptr = child->parent->parent;	/* child->parent already released
										 * above */
		while (ptr)
		{
			ReleaseBuffer(ptr->buffer);
			ptr = ptr->parent;
		}

		/* ok, find new path */
		ptr = parent = gistFindPath(r, child->blkno, &child->downlinkoffnum);

		/* read all buffers as expected by caller */
		/* note we don't lock them or gistcheckpage them here! */
		while (ptr)
		{
			ptr->buffer = ReadBuffer(r, ptr->blkno);
			ptr->page = (Page) BufferGetPage(ptr->buffer);
			ptr = ptr->parent;
		}

		/* install new chain of parents to stack */
		child->parent = parent;

		/* make recursive call to normal processing */
		LockBuffer(child->parent->buffer, GIST_EXCLUSIVE);
		gistFindCorrectParent(r, child);
	}

	return;
}