#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ maxoff; } ;
struct TYPE_8__ {scalar_t__ leftBlkno; int /*<<< orphan*/  isRoot; struct TYPE_8__* parent; void* blkno; struct TYPE_8__* child; } ;
struct TYPE_7__ {int /*<<< orphan*/  strategy; int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  PostingItem ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  TYPE_1__ GinVacuumState ;
typedef  TYPE_2__ DataPageDeleteStack ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  void* BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ FirstOffsetNumber ; 
 int /*<<< orphan*/  GIN_EXCLUSIVE ; 
 int /*<<< orphan*/  GIN_UNLOCK ; 
 int GinDataLeafPageIsEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GinDataPageGetPostingItem (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_6__* GinPageGetOpaque (int /*<<< orphan*/ ) ; 
 int GinPageIsData (int /*<<< orphan*/ ) ; 
 scalar_t__ GinPageIsLeaf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GinPageRightMost (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidBlockNumber ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 void* PostingItemGetBlockNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RBM_NORMAL ; 
 int /*<<< orphan*/  ReadBufferExtended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ginDeletePage (TYPE_1__*,void*,scalar_t__,void*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc0 (int) ; 

__attribute__((used)) static bool
ginScanToDelete(GinVacuumState *gvs, BlockNumber blkno, bool isRoot,
				DataPageDeleteStack *parent, OffsetNumber myoff)
{
	DataPageDeleteStack *me;
	Buffer		buffer;
	Page		page;
	bool		meDelete = false;
	bool		isempty;

	if (isRoot)
	{
		me = parent;
	}
	else
	{
		if (!parent->child)
		{
			me = (DataPageDeleteStack *) palloc0(sizeof(DataPageDeleteStack));
			me->parent = parent;
			parent->child = me;
			me->leftBlkno = InvalidBlockNumber;
		}
		else
			me = parent->child;
	}

	buffer = ReadBufferExtended(gvs->index, MAIN_FORKNUM, blkno,
								RBM_NORMAL, gvs->strategy);

	if (!isRoot)
		LockBuffer(buffer, GIN_EXCLUSIVE);

	page = BufferGetPage(buffer);

	Assert(GinPageIsData(page));

	if (!GinPageIsLeaf(page))
	{
		OffsetNumber i;

		me->blkno = blkno;
		for (i = FirstOffsetNumber; i <= GinPageGetOpaque(page)->maxoff; i++)
		{
			PostingItem *pitem = GinDataPageGetPostingItem(page, i);

			if (ginScanToDelete(gvs, PostingItemGetBlockNumber(pitem), false, me, i))
				i--;
		}
	}

	if (GinPageIsLeaf(page))
		isempty = GinDataLeafPageIsEmpty(page);
	else
		isempty = GinPageGetOpaque(page)->maxoff < FirstOffsetNumber;

	if (isempty)
	{
		/* we never delete the left- or rightmost branch */
		if (me->leftBlkno != InvalidBlockNumber && !GinPageRightMost(page))
		{
			Assert(!isRoot);
			ginDeletePage(gvs, blkno, me->leftBlkno, me->parent->blkno, myoff, me->parent->isRoot);
			meDelete = true;
		}
	}

	if (!isRoot)
		LockBuffer(buffer, GIN_UNLOCK);

	ReleaseBuffer(buffer);

	if (!meDelete)
		me->leftBlkno = blkno;

	return meDelete;
}