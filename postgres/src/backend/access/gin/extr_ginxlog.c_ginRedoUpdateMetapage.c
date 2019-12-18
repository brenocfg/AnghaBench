#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_8__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ ntuples; scalar_t__ prevTail; int /*<<< orphan*/  newRightlink; int /*<<< orphan*/  metadata; } ;
typedef  TYPE_1__ ginxlogUpdateMeta ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_10__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_2__ XLogReaderState ;
struct TYPE_11__ {int /*<<< orphan*/  rightlink; int /*<<< orphan*/  maxoff; } ;
typedef  int Size ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  Item ;
typedef  scalar_t__ IndexTuple ;
typedef  int /*<<< orphan*/  GinMetaPageData ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BLK_NEEDS_REDO ; 
 scalar_t__ BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FirstOffsetNumber ; 
 scalar_t__ GIN_METAPAGE_BLKNO ; 
 int /*<<< orphan*/  GinInitMetabuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GinPageGetMeta (int /*<<< orphan*/ ) ; 
 TYPE_8__* GinPageGetOpaque (int /*<<< orphan*/ ) ; 
 int IndexTupleSize (scalar_t__) ; 
 scalar_t__ InvalidBlockNumber ; 
 scalar_t__ InvalidOffsetNumber ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OffsetNumberNext (int /*<<< orphan*/ ) ; 
 scalar_t__ PageAddItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ PageIsEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogInitBufferForRedo (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ XLogReadBufferForRedo (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 char* XLogRecGetBlockData (TYPE_2__*,int,int*) ; 
 scalar_t__ XLogRecGetData (TYPE_2__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
ginRedoUpdateMetapage(XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	ginxlogUpdateMeta *data = (ginxlogUpdateMeta *) XLogRecGetData(record);
	Buffer		metabuffer;
	Page		metapage;
	Buffer		buffer;

	/*
	 * Restore the metapage. This is essentially the same as a full-page
	 * image, so restore the metapage unconditionally without looking at the
	 * LSN, to avoid torn page hazards.
	 */
	metabuffer = XLogInitBufferForRedo(record, 0);
	Assert(BufferGetBlockNumber(metabuffer) == GIN_METAPAGE_BLKNO);
	metapage = BufferGetPage(metabuffer);

	GinInitMetabuffer(metabuffer);
	memcpy(GinPageGetMeta(metapage), &data->metadata, sizeof(GinMetaPageData));
	PageSetLSN(metapage, lsn);
	MarkBufferDirty(metabuffer);

	if (data->ntuples > 0)
	{
		/*
		 * insert into tail page
		 */
		if (XLogReadBufferForRedo(record, 1, &buffer) == BLK_NEEDS_REDO)
		{
			Page		page = BufferGetPage(buffer);
			OffsetNumber off;
			int			i;
			Size		tupsize;
			char	   *payload;
			IndexTuple	tuples;
			Size		totaltupsize;

			payload = XLogRecGetBlockData(record, 1, &totaltupsize);
			tuples = (IndexTuple) payload;

			if (PageIsEmpty(page))
				off = FirstOffsetNumber;
			else
				off = OffsetNumberNext(PageGetMaxOffsetNumber(page));

			for (i = 0; i < data->ntuples; i++)
			{
				tupsize = IndexTupleSize(tuples);

				if (PageAddItem(page, (Item) tuples, tupsize, off,
								false, false) == InvalidOffsetNumber)
					elog(ERROR, "failed to add item to index page");

				tuples = (IndexTuple) (((char *) tuples) + tupsize);

				off++;
			}
			Assert(payload + totaltupsize == (char *) tuples);

			/*
			 * Increase counter of heap tuples
			 */
			GinPageGetOpaque(page)->maxoff++;

			PageSetLSN(page, lsn);
			MarkBufferDirty(buffer);
		}
		if (BufferIsValid(buffer))
			UnlockReleaseBuffer(buffer);
	}
	else if (data->prevTail != InvalidBlockNumber)
	{
		/*
		 * New tail
		 */
		if (XLogReadBufferForRedo(record, 1, &buffer) == BLK_NEEDS_REDO)
		{
			Page		page = BufferGetPage(buffer);

			GinPageGetOpaque(page)->rightlink = data->newRightlink;

			PageSetLSN(page, lsn);
			MarkBufferDirty(buffer);
		}
		if (BufferIsValid(buffer))
			UnlockReleaseBuffer(buffer);
	}

	UnlockReleaseBuffer(metabuffer);
}