#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  rightlink; } ;
struct TYPE_5__ {int /*<<< orphan*/  strategy; int /*<<< orphan*/  index; int /*<<< orphan*/  tmpCxt; } ;
typedef  int /*<<< orphan*/  PostingItem ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ GinVacuumState ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ FirstOffsetNumber ; 
 int /*<<< orphan*/  GIN_EXCLUSIVE ; 
 int /*<<< orphan*/  GIN_SHARE ; 
 int /*<<< orphan*/  GIN_UNLOCK ; 
 scalar_t__ GinDataLeafPageIsEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GinDataPageGetPostingItem (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_4__* GinPageGetOpaque (int /*<<< orphan*/ ) ; 
 int GinPageIsData (int /*<<< orphan*/ ) ; 
 scalar_t__ GinPageIsLeaf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidBlockNumber ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PostingItemGetBlockNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RBM_NORMAL ; 
 int /*<<< orphan*/  ReadBufferExtended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ginVacuumPostingTreeLeaf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static bool
ginVacuumPostingTreeLeaves(GinVacuumState *gvs, BlockNumber blkno)
{
	Buffer		buffer;
	Page		page;
	bool		hasVoidPage = false;
	MemoryContext oldCxt;

	/* Find leftmost leaf page of posting tree and lock it in exclusive mode */
	while (true)
	{
		PostingItem *pitem;

		buffer = ReadBufferExtended(gvs->index, MAIN_FORKNUM, blkno,
									RBM_NORMAL, gvs->strategy);
		LockBuffer(buffer, GIN_SHARE);
		page = BufferGetPage(buffer);

		Assert(GinPageIsData(page));

		if (GinPageIsLeaf(page))
		{
			LockBuffer(buffer, GIN_UNLOCK);
			LockBuffer(buffer, GIN_EXCLUSIVE);
			break;
		}

		Assert(PageGetMaxOffsetNumber(page) >= FirstOffsetNumber);

		pitem = GinDataPageGetPostingItem(page, FirstOffsetNumber);
		blkno = PostingItemGetBlockNumber(pitem);
		Assert(blkno != InvalidBlockNumber);

		UnlockReleaseBuffer(buffer);
	}

	/* Iterate all posting tree leaves using rightlinks and vacuum them */
	while (true)
	{
		oldCxt = MemoryContextSwitchTo(gvs->tmpCxt);
		ginVacuumPostingTreeLeaf(gvs->index, buffer, gvs);
		MemoryContextSwitchTo(oldCxt);
		MemoryContextReset(gvs->tmpCxt);

		if (GinDataLeafPageIsEmpty(page))
			hasVoidPage = true;

		blkno = GinPageGetOpaque(page)->rightlink;

		UnlockReleaseBuffer(buffer);

		if (blkno == InvalidBlockNumber)
			break;

		buffer = ReadBufferExtended(gvs->index, MAIN_FORKNUM, blkno,
									RBM_NORMAL, gvs->strategy);
		LockBuffer(buffer, GIN_EXCLUSIVE);
		page = BufferGetPage(buffer);
	}

	return hasVoidPage;
}