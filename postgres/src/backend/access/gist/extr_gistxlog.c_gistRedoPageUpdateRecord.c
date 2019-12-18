#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int ntodelete; int ntoinsert; } ;
typedef  TYPE_1__ gistxlogPageUpdate ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_10__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_2__ XLogReaderState ;
typedef  int Size ;
typedef  scalar_t__ Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  Item ;
typedef  scalar_t__ IndexTuple ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BLK_NEEDS_REDO ; 
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FirstOffsetNumber ; 
 int /*<<< orphan*/  GistMarkTuplesDeleted (scalar_t__) ; 
 scalar_t__ GistPageIsLeaf (scalar_t__) ; 
 int IndexTupleSize (scalar_t__) ; 
 scalar_t__ InvalidOffsetNumber ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ OffsetNumberNext (int /*<<< orphan*/ ) ; 
 scalar_t__ PageAddItem (scalar_t__,int /*<<< orphan*/ ,int,scalar_t__,int,int) ; 
 int /*<<< orphan*/  PageGetMaxOffsetNumber (scalar_t__) ; 
 int /*<<< orphan*/  PageIndexMultiDelete (scalar_t__,scalar_t__*,int) ; 
 int /*<<< orphan*/  PageIndexTupleOverwrite (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ PageIsEmpty (scalar_t__) ; 
 int /*<<< orphan*/  PageSetLSN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ XLogReadBufferForRedo (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* XLogRecGetBlockData (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ XLogRecGetData (TYPE_2__*) ; 
 scalar_t__ XLogRecHasBlockRef (TYPE_2__*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gistRedoClearFollowRight (TYPE_2__*,int) ; 

__attribute__((used)) static void
gistRedoPageUpdateRecord(XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	gistxlogPageUpdate *xldata = (gistxlogPageUpdate *) XLogRecGetData(record);
	Buffer		buffer;
	Page		page;

	if (XLogReadBufferForRedo(record, 0, &buffer) == BLK_NEEDS_REDO)
	{
		char	   *begin;
		char	   *data;
		Size		datalen;
		int			ninserted = 0;

		data = begin = XLogRecGetBlockData(record, 0, &datalen);

		page = (Page) BufferGetPage(buffer);

		if (xldata->ntodelete == 1 && xldata->ntoinsert == 1)
		{
			/*
			 * When replacing one tuple with one other tuple, we must use
			 * PageIndexTupleOverwrite for consistency with gistplacetopage.
			 */
			OffsetNumber offnum = *((OffsetNumber *) data);
			IndexTuple	itup;
			Size		itupsize;

			data += sizeof(OffsetNumber);
			itup = (IndexTuple) data;
			itupsize = IndexTupleSize(itup);
			if (!PageIndexTupleOverwrite(page, offnum, (Item) itup, itupsize))
				elog(ERROR, "failed to add item to GiST index page, size %d bytes",
					 (int) itupsize);
			data += itupsize;
			/* should be nothing left after consuming 1 tuple */
			Assert(data - begin == datalen);
			/* update insertion count for assert check below */
			ninserted++;
		}
		else if (xldata->ntodelete > 0)
		{
			/* Otherwise, delete old tuples if any */
			OffsetNumber *todelete = (OffsetNumber *) data;

			data += sizeof(OffsetNumber) * xldata->ntodelete;

			PageIndexMultiDelete(page, todelete, xldata->ntodelete);
			if (GistPageIsLeaf(page))
				GistMarkTuplesDeleted(page);
		}

		/* Add new tuples if any */
		if (data - begin < datalen)
		{
			OffsetNumber off = (PageIsEmpty(page)) ? FirstOffsetNumber :
			OffsetNumberNext(PageGetMaxOffsetNumber(page));

			while (data - begin < datalen)
			{
				IndexTuple	itup = (IndexTuple) data;
				Size		sz = IndexTupleSize(itup);
				OffsetNumber l;

				data += sz;

				l = PageAddItem(page, (Item) itup, sz, off, false, false);
				if (l == InvalidOffsetNumber)
					elog(ERROR, "failed to add item to GiST index page, size %d bytes",
						 (int) sz);
				off++;
				ninserted++;
			}
		}

		/* Check that XLOG record contained expected number of tuples */
		Assert(ninserted == xldata->ntoinsert);

		PageSetLSN(page, lsn);
		MarkBufferDirty(buffer);
	}

	/*
	 * Fix follow-right data on left child page
	 *
	 * This must be done while still holding the lock on the target page. Note
	 * that even if the target page no longer exists, we still attempt to
	 * replay the change on the child page.
	 */
	if (XLogRecHasBlockRef(record, 1))
		gistRedoClearFollowRight(record, 1);

	if (BufferIsValid(buffer))
		UnlockReleaseBuffer(buffer);
}