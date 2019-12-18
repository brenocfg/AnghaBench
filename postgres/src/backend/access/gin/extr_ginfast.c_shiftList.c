#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64 ;
struct TYPE_9__ {int ndeleted; int /*<<< orphan*/  metadata; } ;
typedef  TYPE_1__ ginxlogDeleteListPages ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_13__ {scalar_t__ maxoff; scalar_t__ rightlink; int /*<<< orphan*/  flags; } ;
struct TYPE_12__ {scalar_t__ head; size_t nPendingPages; scalar_t__ nPendingHeapTuples; scalar_t__ tailFreeSize; scalar_t__ tail; } ;
struct TYPE_11__ {size_t pages_deleted; } ;
struct TYPE_10__ {int pd_lower; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_2__* PageHeader ;
typedef  scalar_t__ Page ;
typedef  TYPE_3__ IndexBulkDeleteResult ;
typedef  TYPE_4__ GinMetaPageData ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  GIN_DELETED ; 
 int /*<<< orphan*/  GIN_EXCLUSIVE ; 
 int GIN_NDELETE_AT_ONCE ; 
 TYPE_4__* GinPageGetMeta (scalar_t__) ; 
 TYPE_7__* GinPageGetOpaque (scalar_t__) ; 
 int /*<<< orphan*/  GinPageIsDeleted (scalar_t__) ; 
 scalar_t__ InvalidBlockNumber ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (scalar_t__,int /*<<< orphan*/ ) ; 
 int REGBUF_STANDARD ; 
 int REGBUF_WILL_INIT ; 
 int /*<<< orphan*/  RM_GIN_ID ; 
 int /*<<< orphan*/  ReadBuffer (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  RecordFreeIndexPage (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLOG_GIN_DELETE_LISTPAGE ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogEnsureRecordSpace (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_4__*,int) ; 

__attribute__((used)) static void
shiftList(Relation index, Buffer metabuffer, BlockNumber newHead,
		  bool fill_fsm, IndexBulkDeleteResult *stats)
{
	Page		metapage;
	GinMetaPageData *metadata;
	BlockNumber blknoToDelete;

	metapage = BufferGetPage(metabuffer);
	metadata = GinPageGetMeta(metapage);
	blknoToDelete = metadata->head;

	do
	{
		Page		page;
		int			i;
		int64		nDeletedHeapTuples = 0;
		ginxlogDeleteListPages data;
		Buffer		buffers[GIN_NDELETE_AT_ONCE];
		BlockNumber freespace[GIN_NDELETE_AT_ONCE];

		data.ndeleted = 0;
		while (data.ndeleted < GIN_NDELETE_AT_ONCE && blknoToDelete != newHead)
		{
			freespace[data.ndeleted] = blknoToDelete;
			buffers[data.ndeleted] = ReadBuffer(index, blknoToDelete);
			LockBuffer(buffers[data.ndeleted], GIN_EXCLUSIVE);
			page = BufferGetPage(buffers[data.ndeleted]);

			data.ndeleted++;

			Assert(!GinPageIsDeleted(page));

			nDeletedHeapTuples += GinPageGetOpaque(page)->maxoff;
			blknoToDelete = GinPageGetOpaque(page)->rightlink;
		}

		if (stats)
			stats->pages_deleted += data.ndeleted;

		/*
		 * This operation touches an unusually large number of pages, so
		 * prepare the XLogInsert machinery for that before entering the
		 * critical section.
		 */
		if (RelationNeedsWAL(index))
			XLogEnsureRecordSpace(data.ndeleted, 0);

		START_CRIT_SECTION();

		metadata->head = blknoToDelete;

		Assert(metadata->nPendingPages >= data.ndeleted);
		metadata->nPendingPages -= data.ndeleted;
		Assert(metadata->nPendingHeapTuples >= nDeletedHeapTuples);
		metadata->nPendingHeapTuples -= nDeletedHeapTuples;

		if (blknoToDelete == InvalidBlockNumber)
		{
			metadata->tail = InvalidBlockNumber;
			metadata->tailFreeSize = 0;
			metadata->nPendingPages = 0;
			metadata->nPendingHeapTuples = 0;
		}

		/*
		 * Set pd_lower just past the end of the metadata.  This is essential,
		 * because without doing so, metadata will be lost if xlog.c
		 * compresses the page.  (We must do this here because pre-v11
		 * versions of PG did not set the metapage's pd_lower correctly, so a
		 * pg_upgraded index might contain the wrong value.)
		 */
		((PageHeader) metapage)->pd_lower =
			((char *) metadata + sizeof(GinMetaPageData)) - (char *) metapage;

		MarkBufferDirty(metabuffer);

		for (i = 0; i < data.ndeleted; i++)
		{
			page = BufferGetPage(buffers[i]);
			GinPageGetOpaque(page)->flags = GIN_DELETED;
			MarkBufferDirty(buffers[i]);
		}

		if (RelationNeedsWAL(index))
		{
			XLogRecPtr	recptr;

			XLogBeginInsert();
			XLogRegisterBuffer(0, metabuffer,
							   REGBUF_WILL_INIT | REGBUF_STANDARD);
			for (i = 0; i < data.ndeleted; i++)
				XLogRegisterBuffer(i + 1, buffers[i], REGBUF_WILL_INIT);

			memcpy(&data.metadata, metadata, sizeof(GinMetaPageData));

			XLogRegisterData((char *) &data,
							 sizeof(ginxlogDeleteListPages));

			recptr = XLogInsert(RM_GIN_ID, XLOG_GIN_DELETE_LISTPAGE);
			PageSetLSN(metapage, recptr);

			for (i = 0; i < data.ndeleted; i++)
			{
				page = BufferGetPage(buffers[i]);
				PageSetLSN(page, recptr);
			}
		}

		for (i = 0; i < data.ndeleted; i++)
			UnlockReleaseBuffer(buffers[i]);

		END_CRIT_SECTION();

		for (i = 0; fill_fsm && i < data.ndeleted; i++)
			RecordFreeIndexPage(index, freespace[i]);

	} while (blknoToDelete != newHead);
}