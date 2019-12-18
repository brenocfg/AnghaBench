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
struct TYPE_12__ {int npage; scalar_t__ markfollowright; int /*<<< orphan*/  orignsn; scalar_t__ origrlink; scalar_t__ origleaf; } ;
typedef  TYPE_1__ gistxlogPageSplit ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_13__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_2__ XLogReaderState ;
struct TYPE_11__ {scalar_t__ rightlink; } ;
typedef  int /*<<< orphan*/  Size ;
typedef  scalar_t__ Page ;
typedef  int /*<<< orphan*/  IndexTuple ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 int F_LEAF ; 
 int /*<<< orphan*/  FirstOffsetNumber ; 
 int /*<<< orphan*/  GISTInitBuffer (int /*<<< orphan*/ ,int) ; 
 scalar_t__ GIST_ROOT_BLKNO ; 
 int /*<<< orphan*/  GistClearFollowRight (scalar_t__) ; 
 int /*<<< orphan*/  GistMarkFollowRight (scalar_t__) ; 
 TYPE_10__* GistPageGetOpaque (scalar_t__) ; 
 int /*<<< orphan*/  GistPageSetNSN (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidBlockNumber ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogInitBufferForRedo (TYPE_2__*,int) ; 
 char* XLogRecGetBlockData (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLogRecGetBlockTag (TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ XLogRecGetData (TYPE_2__*) ; 
 scalar_t__ XLogRecHasBlockRef (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * decodePageSplitRecord (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  gistRedoClearFollowRight (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gistfillbuffer (scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gistRedoPageSplitRecord(XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	gistxlogPageSplit *xldata = (gistxlogPageSplit *) XLogRecGetData(record);
	Buffer		firstbuffer = InvalidBuffer;
	Buffer		buffer;
	Page		page;
	int			i;
	bool		isrootsplit = false;

	/*
	 * We must hold lock on the first-listed page throughout the action,
	 * including while updating the left child page (if any).  We can unlock
	 * remaining pages in the list as soon as they've been written, because
	 * there is no path for concurrent queries to reach those pages without
	 * first visiting the first-listed page.
	 */

	/* loop around all pages */
	for (i = 0; i < xldata->npage; i++)
	{
		int			flags;
		char	   *data;
		Size		datalen;
		int			num;
		BlockNumber blkno;
		IndexTuple *tuples;

		XLogRecGetBlockTag(record, i + 1, NULL, NULL, &blkno);
		if (blkno == GIST_ROOT_BLKNO)
		{
			Assert(i == 0);
			isrootsplit = true;
		}

		buffer = XLogInitBufferForRedo(record, i + 1);
		page = (Page) BufferGetPage(buffer);
		data = XLogRecGetBlockData(record, i + 1, &datalen);

		tuples = decodePageSplitRecord(data, datalen, &num);

		/* ok, clear buffer */
		if (xldata->origleaf && blkno != GIST_ROOT_BLKNO)
			flags = F_LEAF;
		else
			flags = 0;
		GISTInitBuffer(buffer, flags);

		/* and fill it */
		gistfillbuffer(page, tuples, num, FirstOffsetNumber);

		if (blkno == GIST_ROOT_BLKNO)
		{
			GistPageGetOpaque(page)->rightlink = InvalidBlockNumber;
			GistPageSetNSN(page, xldata->orignsn);
			GistClearFollowRight(page);
		}
		else
		{
			if (i < xldata->npage - 1)
			{
				BlockNumber nextblkno;

				XLogRecGetBlockTag(record, i + 2, NULL, NULL, &nextblkno);
				GistPageGetOpaque(page)->rightlink = nextblkno;
			}
			else
				GistPageGetOpaque(page)->rightlink = xldata->origrlink;
			GistPageSetNSN(page, xldata->orignsn);
			if (i < xldata->npage - 1 && !isrootsplit &&
				xldata->markfollowright)
				GistMarkFollowRight(page);
			else
				GistClearFollowRight(page);
		}

		PageSetLSN(page, lsn);
		MarkBufferDirty(buffer);

		if (i == 0)
			firstbuffer = buffer;
		else
			UnlockReleaseBuffer(buffer);
	}

	/* Fix follow-right data on left child page, if any */
	if (XLogRecHasBlockRef(record, 0))
		gistRedoClearFollowRight(record, 0);

	/* Finally, release lock on the first page */
	UnlockReleaseBuffer(firstbuffer);
}