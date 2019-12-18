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
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  size_t uint32 ;
struct TYPE_14__ {TYPE_2__* result; int /*<<< orphan*/  tmpCxt; int /*<<< orphan*/  index; int /*<<< orphan*/  ginstate; int /*<<< orphan*/  strategy; void* callback_state; int /*<<< orphan*/  callback; } ;
struct TYPE_13__ {scalar_t__ num_index_tuples; } ;
struct TYPE_12__ {int /*<<< orphan*/  strategy; int /*<<< orphan*/  index; } ;
struct TYPE_11__ {scalar_t__ rightlink; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Page ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  TYPE_1__ IndexVacuumInfo ;
typedef  int /*<<< orphan*/  IndexTupleData ;
typedef  scalar_t__ IndexTuple ;
typedef  TYPE_2__ IndexBulkDeleteResult ;
typedef  int /*<<< orphan*/  IndexBulkDeleteCallback ;
typedef  TYPE_3__ GinVacuumState ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int BLCKSZ ; 
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 scalar_t__ FirstOffsetNumber ; 
 int /*<<< orphan*/  GIN_EXCLUSIVE ; 
 scalar_t__ GIN_ROOT_BLKNO ; 
 int /*<<< orphan*/  GIN_SHARE ; 
 int /*<<< orphan*/  GIN_UNLOCK ; 
 scalar_t__ GinGetDownlink (scalar_t__) ; 
 TYPE_10__* GinPageGetOpaque (scalar_t__) ; 
 int /*<<< orphan*/  GinPageIsData (scalar_t__) ; 
 scalar_t__ GinPageIsLeaf (scalar_t__) ; 
 scalar_t__ InvalidBlockNumber ; 
 int /*<<< orphan*/  IsAutoVacuumWorkerProcess () ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetItem (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (scalar_t__,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (scalar_t__) ; 
 int /*<<< orphan*/  PageRestoreTempPage (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  RBM_NORMAL ; 
 int /*<<< orphan*/  ReadBufferExtended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ginInsertCleanup (int /*<<< orphan*/ *,int,int,int,TYPE_2__*) ; 
 scalar_t__ ginVacuumEntryPage (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__*,size_t*) ; 
 int /*<<< orphan*/  ginVacuumPostingTree (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  initGinState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  vacuum_delay_point () ; 
 int /*<<< orphan*/  xlogVacuumPage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

IndexBulkDeleteResult *
ginbulkdelete(IndexVacuumInfo *info, IndexBulkDeleteResult *stats,
			  IndexBulkDeleteCallback callback, void *callback_state)
{
	Relation	index = info->index;
	BlockNumber blkno = GIN_ROOT_BLKNO;
	GinVacuumState gvs;
	Buffer		buffer;
	BlockNumber rootOfPostingTree[BLCKSZ / (sizeof(IndexTupleData) + sizeof(ItemId))];
	uint32		nRoot;

	gvs.tmpCxt = AllocSetContextCreate(CurrentMemoryContext,
									   "Gin vacuum temporary context",
									   ALLOCSET_DEFAULT_SIZES);
	gvs.index = index;
	gvs.callback = callback;
	gvs.callback_state = callback_state;
	gvs.strategy = info->strategy;
	initGinState(&gvs.ginstate, index);

	/* first time through? */
	if (stats == NULL)
	{
		/* Yes, so initialize stats to zeroes */
		stats = (IndexBulkDeleteResult *) palloc0(sizeof(IndexBulkDeleteResult));

		/*
		 * and cleanup any pending inserts
		 */
		ginInsertCleanup(&gvs.ginstate, !IsAutoVacuumWorkerProcess(),
						 false, true, stats);
	}

	/* we'll re-count the tuples each time */
	stats->num_index_tuples = 0;
	gvs.result = stats;

	buffer = ReadBufferExtended(index, MAIN_FORKNUM, blkno,
								RBM_NORMAL, info->strategy);

	/* find leaf page */
	for (;;)
	{
		Page		page = BufferGetPage(buffer);
		IndexTuple	itup;

		LockBuffer(buffer, GIN_SHARE);

		Assert(!GinPageIsData(page));

		if (GinPageIsLeaf(page))
		{
			LockBuffer(buffer, GIN_UNLOCK);
			LockBuffer(buffer, GIN_EXCLUSIVE);

			if (blkno == GIN_ROOT_BLKNO && !GinPageIsLeaf(page))
			{
				LockBuffer(buffer, GIN_UNLOCK);
				continue;		/* check it one more */
			}
			break;
		}

		Assert(PageGetMaxOffsetNumber(page) >= FirstOffsetNumber);

		itup = (IndexTuple) PageGetItem(page, PageGetItemId(page, FirstOffsetNumber));
		blkno = GinGetDownlink(itup);
		Assert(blkno != InvalidBlockNumber);

		UnlockReleaseBuffer(buffer);
		buffer = ReadBufferExtended(index, MAIN_FORKNUM, blkno,
									RBM_NORMAL, info->strategy);
	}

	/* right now we found leftmost page in entry's BTree */

	for (;;)
	{
		Page		page = BufferGetPage(buffer);
		Page		resPage;
		uint32		i;

		Assert(!GinPageIsData(page));

		resPage = ginVacuumEntryPage(&gvs, buffer, rootOfPostingTree, &nRoot);

		blkno = GinPageGetOpaque(page)->rightlink;

		if (resPage)
		{
			START_CRIT_SECTION();
			PageRestoreTempPage(resPage, page);
			MarkBufferDirty(buffer);
			xlogVacuumPage(gvs.index, buffer);
			UnlockReleaseBuffer(buffer);
			END_CRIT_SECTION();
		}
		else
		{
			UnlockReleaseBuffer(buffer);
		}

		vacuum_delay_point();

		for (i = 0; i < nRoot; i++)
		{
			ginVacuumPostingTree(&gvs, rootOfPostingTree[i]);
			vacuum_delay_point();
		}

		if (blkno == InvalidBlockNumber)	/* rightmost page */
			break;

		buffer = ReadBufferExtended(index, MAIN_FORKNUM, blkno,
									RBM_NORMAL, info->strategy);
		LockBuffer(buffer, GIN_EXCLUSIVE);
	}

	MemoryContextDelete(gvs.tmpCxt);

	return gvs.result;
}