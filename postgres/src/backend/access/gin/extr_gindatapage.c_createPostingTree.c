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
typedef  int uint32 ;
struct TYPE_6__ {int size; } ;
typedef  TYPE_1__ ginxlogCreatePostingTree ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_8__ {int /*<<< orphan*/  rightlink; } ;
struct TYPE_7__ {int /*<<< orphan*/  nDataPages; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Pointer ;
typedef  scalar_t__ Page ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  TYPE_2__ GinStatsData ;
typedef  int /*<<< orphan*/  GinPostingList ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BLCKSZ ; 
 int /*<<< orphan*/  BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int GIN_COMPRESSED ; 
 int GIN_DATA ; 
 int GIN_LEAF ; 
 scalar_t__ GinDataLeafPageGetPostingList (scalar_t__) ; 
 int GinDataPageMaxDataSize ; 
 int /*<<< orphan*/  GinDataPageSetDataSize (scalar_t__,int) ; 
 int /*<<< orphan*/  GinInitPage (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GinNewBuffer (int /*<<< orphan*/ ) ; 
 TYPE_5__* GinPageGetOpaque (scalar_t__) ; 
 int /*<<< orphan*/  GinPostingListSegmentMaxSize ; 
 int /*<<< orphan*/  InvalidBlockNumber ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageRestoreTempPage (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PageSetLSN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PredicateLockPageSplit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGBUF_WILL_INIT ; 
 int /*<<< orphan*/  RM_GIN_ID ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int SizeOfGinPostingList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLOG_GIN_CREATE_PTREE ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * ginCompressPostingList (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ginInsertItemPointers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ palloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

BlockNumber
createPostingTree(Relation index, ItemPointerData *items, uint32 nitems,
				  GinStatsData *buildStats, Buffer entrybuffer)
{
	BlockNumber blkno;
	Buffer		buffer;
	Page		tmppage;
	Page		page;
	Pointer		ptr;
	int			nrootitems;
	int			rootsize;
	bool		is_build = (buildStats != NULL);

	/* Construct the new root page in memory first. */
	tmppage = (Page) palloc(BLCKSZ);
	GinInitPage(tmppage, GIN_DATA | GIN_LEAF | GIN_COMPRESSED, BLCKSZ);
	GinPageGetOpaque(tmppage)->rightlink = InvalidBlockNumber;

	/*
	 * Write as many of the items to the root page as fit. In segments of max
	 * GinPostingListSegmentMaxSize bytes each.
	 */
	nrootitems = 0;
	rootsize = 0;
	ptr = (Pointer) GinDataLeafPageGetPostingList(tmppage);
	while (nrootitems < nitems)
	{
		GinPostingList *segment;
		int			npacked;
		int			segsize;

		segment = ginCompressPostingList(&items[nrootitems],
										 nitems - nrootitems,
										 GinPostingListSegmentMaxSize,
										 &npacked);
		segsize = SizeOfGinPostingList(segment);
		if (rootsize + segsize > GinDataPageMaxDataSize)
			break;

		memcpy(ptr, segment, segsize);
		ptr += segsize;
		rootsize += segsize;
		nrootitems += npacked;
		pfree(segment);
	}
	GinDataPageSetDataSize(tmppage, rootsize);

	/*
	 * All set. Get a new physical page, and copy the in-memory page to it.
	 */
	buffer = GinNewBuffer(index);
	page = BufferGetPage(buffer);
	blkno = BufferGetBlockNumber(buffer);

	/*
	 * Copy any predicate locks from the entry tree leaf (containing posting
	 * list) to the posting tree.
	 */
	PredicateLockPageSplit(index, BufferGetBlockNumber(entrybuffer), blkno);

	START_CRIT_SECTION();

	PageRestoreTempPage(tmppage, page);
	MarkBufferDirty(buffer);

	if (RelationNeedsWAL(index) && !is_build)
	{
		XLogRecPtr	recptr;
		ginxlogCreatePostingTree data;

		data.size = rootsize;

		XLogBeginInsert();
		XLogRegisterData((char *) &data, sizeof(ginxlogCreatePostingTree));

		XLogRegisterData((char *) GinDataLeafPageGetPostingList(page),
						 rootsize);
		XLogRegisterBuffer(0, buffer, REGBUF_WILL_INIT);

		recptr = XLogInsert(RM_GIN_ID, XLOG_GIN_CREATE_PTREE);
		PageSetLSN(page, recptr);
	}

	UnlockReleaseBuffer(buffer);

	END_CRIT_SECTION();

	/* During index build, count the newly-added data page */
	if (buildStats)
		buildStats->nDataPages++;

	elog(DEBUG2, "created GIN posting tree with %d items", nrootitems);

	/*
	 * Add any remaining TIDs to the newly-created posting tree.
	 */
	if (nitems > nrootitems)
	{
		ginInsertItemPointers(index, blkno,
							  items + nrootitems,
							  nitems - nrootitems,
							  buildStats);
	}

	return blkno;
}