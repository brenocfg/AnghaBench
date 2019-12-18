#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ rightlink; int ntuples; } ;
typedef  TYPE_1__ ginxlogInsertListPage ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_9__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_2__ XLogReaderState ;
struct TYPE_10__ {scalar_t__ rightlink; int maxoff; } ;
typedef  int Size ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  Item ;
typedef  scalar_t__ IndexTuple ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FirstOffsetNumber ; 
 int /*<<< orphan*/  GIN_LIST ; 
 int /*<<< orphan*/  GinInitBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* GinPageGetOpaque (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GinPageSetFullRow (int /*<<< orphan*/ ) ; 
 int IndexTupleSize (scalar_t__) ; 
 scalar_t__ InvalidBlockNumber ; 
 scalar_t__ InvalidOffsetNumber ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ PageAddItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int,int) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogInitBufferForRedo (TYPE_2__*,int /*<<< orphan*/ ) ; 
 char* XLogRecGetBlockData (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ XLogRecGetData (TYPE_2__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ginRedoInsertListPage(XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	ginxlogInsertListPage *data = (ginxlogInsertListPage *) XLogRecGetData(record);
	Buffer		buffer;
	Page		page;
	OffsetNumber l,
				off = FirstOffsetNumber;
	int			i,
				tupsize;
	char	   *payload;
	IndexTuple	tuples;
	Size		totaltupsize;

	/* We always re-initialize the page. */
	buffer = XLogInitBufferForRedo(record, 0);
	page = BufferGetPage(buffer);

	GinInitBuffer(buffer, GIN_LIST);
	GinPageGetOpaque(page)->rightlink = data->rightlink;
	if (data->rightlink == InvalidBlockNumber)
	{
		/* tail of sublist */
		GinPageSetFullRow(page);
		GinPageGetOpaque(page)->maxoff = 1;
	}
	else
	{
		GinPageGetOpaque(page)->maxoff = 0;
	}

	payload = XLogRecGetBlockData(record, 0, &totaltupsize);

	tuples = (IndexTuple) payload;
	for (i = 0; i < data->ntuples; i++)
	{
		tupsize = IndexTupleSize(tuples);

		l = PageAddItem(page, (Item) tuples, tupsize, off, false, false);

		if (l == InvalidOffsetNumber)
			elog(ERROR, "failed to add item to index page");

		tuples = (IndexTuple) (((char *) tuples) + tupsize);
		off++;
	}
	Assert((char *) tuples == payload + totaltupsize);

	PageSetLSN(page, lsn);
	MarkBufferDirty(buffer);

	UnlockReleaseBuffer(buffer);
}