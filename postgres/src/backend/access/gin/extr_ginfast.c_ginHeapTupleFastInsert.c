#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_19__ ;

/* Type definitions */
struct TYPE_24__ {int ntuples; scalar_t__ newRightlink; scalar_t__ prevTail; char metadata; int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ ginxlogUpdateMeta ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_29__ {scalar_t__ head; scalar_t__ tailFreeSize; scalar_t__ tail; int nPendingPages; scalar_t__ nPendingHeapTuples; } ;
struct TYPE_28__ {TYPE_2__* index; } ;
struct TYPE_27__ {int ntuples; scalar_t__ sumsize; TYPE_6__** tuples; } ;
struct TYPE_26__ {int pd_lower; } ;
struct TYPE_25__ {int /*<<< orphan*/  rd_node; } ;
struct TYPE_23__ {scalar_t__ rightlink; scalar_t__ maxoff; } ;
typedef  TYPE_2__* Relation ;
typedef  TYPE_3__* PageHeader ;
typedef  int /*<<< orphan*/ * Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemIdData ;
typedef  int /*<<< orphan*/  Item ;
typedef  TYPE_4__ GinTupleCollector ;
typedef  TYPE_5__ GinState ;
typedef  TYPE_6__ GinMetaPageData ;
typedef  scalar_t__ Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * BufferGetPage (scalar_t__) ; 
 int /*<<< orphan*/  CheckForSerializableConflictIn (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FirstOffsetNumber ; 
 int /*<<< orphan*/  GIN_EXCLUSIVE ; 
 scalar_t__ GIN_METAPAGE_BLKNO ; 
 int GIN_PAGE_FREESIZE ; 
 int /*<<< orphan*/  GIN_UNLOCK ; 
 int GinGetPendingListCleanupSize (TYPE_2__*) ; 
 scalar_t__ GinListPageSize ; 
 TYPE_6__* GinPageGetMeta (int /*<<< orphan*/ *) ; 
 TYPE_19__* GinPageGetOpaque (int /*<<< orphan*/ *) ; 
 int IndexTupleSize (TYPE_6__*) ; 
 scalar_t__ InvalidBlockNumber ; 
 scalar_t__ InvalidBuffer ; 
 scalar_t__ InvalidOffsetNumber ; 
 int /*<<< orphan*/  LockBuffer (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (scalar_t__) ; 
 scalar_t__ OffsetNumberNext (int /*<<< orphan*/ ) ; 
 scalar_t__ PageAddItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__,int,int) ; 
 scalar_t__ PageGetExactFreeSpace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PageGetMaxOffsetNumber (int /*<<< orphan*/ *) ; 
 scalar_t__ PageIsEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int REGBUF_STANDARD ; 
 int REGBUF_WILL_INIT ; 
 int /*<<< orphan*/  RM_GIN_ID ; 
 scalar_t__ ReadBuffer (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_2__*) ; 
 int RelationNeedsWAL (TYPE_2__*) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (scalar_t__) ; 
 int /*<<< orphan*/  XLOG_GIN_UPDATE_META_PAGE ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBufData (int,char*,int) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int,scalar_t__,int) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ginInsertCleanup (TYPE_5__*,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  makeSublist (TYPE_2__*,TYPE_6__**,int,TYPE_6__*) ; 
 int /*<<< orphan*/  memcpy (char*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ palloc (scalar_t__) ; 

void
ginHeapTupleFastInsert(GinState *ginstate, GinTupleCollector *collector)
{
	Relation	index = ginstate->index;
	Buffer		metabuffer;
	Page		metapage;
	GinMetaPageData *metadata = NULL;
	Buffer		buffer = InvalidBuffer;
	Page		page = NULL;
	ginxlogUpdateMeta data;
	bool		separateList = false;
	bool		needCleanup = false;
	int			cleanupSize;
	bool		needWal;

	if (collector->ntuples == 0)
		return;

	needWal = RelationNeedsWAL(index);

	data.node = index->rd_node;
	data.ntuples = 0;
	data.newRightlink = data.prevTail = InvalidBlockNumber;

	metabuffer = ReadBuffer(index, GIN_METAPAGE_BLKNO);
	metapage = BufferGetPage(metabuffer);

	/*
	 * An insertion to the pending list could logically belong anywhere in the
	 * tree, so it conflicts with all serializable scans.  All scans acquire a
	 * predicate lock on the metabuffer to represent that.
	 */
	CheckForSerializableConflictIn(index, NULL, metabuffer);

	if (collector->sumsize + collector->ntuples * sizeof(ItemIdData) > GinListPageSize)
	{
		/*
		 * Total size is greater than one page => make sublist
		 */
		separateList = true;
	}
	else
	{
		LockBuffer(metabuffer, GIN_EXCLUSIVE);
		metadata = GinPageGetMeta(metapage);

		if (metadata->head == InvalidBlockNumber ||
			collector->sumsize + collector->ntuples * sizeof(ItemIdData) > metadata->tailFreeSize)
		{
			/*
			 * Pending list is empty or total size is greater than freespace
			 * on tail page => make sublist
			 *
			 * We unlock metabuffer to keep high concurrency
			 */
			separateList = true;
			LockBuffer(metabuffer, GIN_UNLOCK);
		}
	}

	if (separateList)
	{
		/*
		 * We should make sublist separately and append it to the tail
		 */
		GinMetaPageData sublist;

		memset(&sublist, 0, sizeof(GinMetaPageData));
		makeSublist(index, collector->tuples, collector->ntuples, &sublist);

		if (needWal)
			XLogBeginInsert();

		/*
		 * metapage was unlocked, see above
		 */
		LockBuffer(metabuffer, GIN_EXCLUSIVE);
		metadata = GinPageGetMeta(metapage);

		if (metadata->head == InvalidBlockNumber)
		{
			/*
			 * Main list is empty, so just insert sublist as main list
			 */
			START_CRIT_SECTION();

			metadata->head = sublist.head;
			metadata->tail = sublist.tail;
			metadata->tailFreeSize = sublist.tailFreeSize;

			metadata->nPendingPages = sublist.nPendingPages;
			metadata->nPendingHeapTuples = sublist.nPendingHeapTuples;
		}
		else
		{
			/*
			 * Merge lists
			 */
			data.prevTail = metadata->tail;
			data.newRightlink = sublist.head;

			buffer = ReadBuffer(index, metadata->tail);
			LockBuffer(buffer, GIN_EXCLUSIVE);
			page = BufferGetPage(buffer);

			Assert(GinPageGetOpaque(page)->rightlink == InvalidBlockNumber);

			START_CRIT_SECTION();

			GinPageGetOpaque(page)->rightlink = sublist.head;

			MarkBufferDirty(buffer);

			metadata->tail = sublist.tail;
			metadata->tailFreeSize = sublist.tailFreeSize;

			metadata->nPendingPages += sublist.nPendingPages;
			metadata->nPendingHeapTuples += sublist.nPendingHeapTuples;

			if (needWal)
				XLogRegisterBuffer(1, buffer, REGBUF_STANDARD);
		}
	}
	else
	{
		/*
		 * Insert into tail page.  Metapage is already locked
		 */
		OffsetNumber l,
					off;
		int			i,
					tupsize;
		char	   *ptr;
		char	   *collectordata;

		buffer = ReadBuffer(index, metadata->tail);
		LockBuffer(buffer, GIN_EXCLUSIVE);
		page = BufferGetPage(buffer);

		off = (PageIsEmpty(page)) ? FirstOffsetNumber :
			OffsetNumberNext(PageGetMaxOffsetNumber(page));

		collectordata = ptr = (char *) palloc(collector->sumsize);

		data.ntuples = collector->ntuples;

		if (needWal)
			XLogBeginInsert();

		START_CRIT_SECTION();

		/*
		 * Increase counter of heap tuples
		 */
		Assert(GinPageGetOpaque(page)->maxoff <= metadata->nPendingHeapTuples);
		GinPageGetOpaque(page)->maxoff++;
		metadata->nPendingHeapTuples++;

		for (i = 0; i < collector->ntuples; i++)
		{
			tupsize = IndexTupleSize(collector->tuples[i]);
			l = PageAddItem(page, (Item) collector->tuples[i], tupsize, off, false, false);

			if (l == InvalidOffsetNumber)
				elog(ERROR, "failed to add item to index page in \"%s\"",
					 RelationGetRelationName(index));

			memcpy(ptr, collector->tuples[i], tupsize);
			ptr += tupsize;

			off++;
		}

		Assert((ptr - collectordata) <= collector->sumsize);
		if (needWal)
		{
			XLogRegisterBuffer(1, buffer, REGBUF_STANDARD);
			XLogRegisterBufData(1, collectordata, collector->sumsize);
		}

		metadata->tailFreeSize = PageGetExactFreeSpace(page);

		MarkBufferDirty(buffer);
	}

	/*
	 * Set pd_lower just past the end of the metadata.  This is essential,
	 * because without doing so, metadata will be lost if xlog.c compresses
	 * the page.  (We must do this here because pre-v11 versions of PG did not
	 * set the metapage's pd_lower correctly, so a pg_upgraded index might
	 * contain the wrong value.)
	 */
	((PageHeader) metapage)->pd_lower =
		((char *) metadata + sizeof(GinMetaPageData)) - (char *) metapage;

	/*
	 * Write metabuffer, make xlog entry
	 */
	MarkBufferDirty(metabuffer);

	if (needWal)
	{
		XLogRecPtr	recptr;

		memcpy(&data.metadata, metadata, sizeof(GinMetaPageData));

		XLogRegisterBuffer(0, metabuffer, REGBUF_WILL_INIT | REGBUF_STANDARD);
		XLogRegisterData((char *) &data, sizeof(ginxlogUpdateMeta));

		recptr = XLogInsert(RM_GIN_ID, XLOG_GIN_UPDATE_META_PAGE);
		PageSetLSN(metapage, recptr);

		if (buffer != InvalidBuffer)
		{
			PageSetLSN(page, recptr);
		}
	}

	if (buffer != InvalidBuffer)
		UnlockReleaseBuffer(buffer);

	/*
	 * Force pending list cleanup when it becomes too long. And,
	 * ginInsertCleanup could take significant amount of time, so we prefer to
	 * call it when it can do all the work in a single collection cycle. In
	 * non-vacuum mode, it shouldn't require maintenance_work_mem, so fire it
	 * while pending list is still small enough to fit into
	 * gin_pending_list_limit.
	 *
	 * ginInsertCleanup() should not be called inside our CRIT_SECTION.
	 */
	cleanupSize = GinGetPendingListCleanupSize(index);
	if (metadata->nPendingPages * GIN_PAGE_FREESIZE > cleanupSize * 1024L)
		needCleanup = true;

	UnlockReleaseBuffer(metabuffer);

	END_CRIT_SECTION();

	/*
	 * Since it could contend with concurrent cleanup process we cleanup
	 * pending list not forcibly.
	 */
	if (needCleanup)
		ginInsertCleanup(ginstate, false, true, false, NULL);
}