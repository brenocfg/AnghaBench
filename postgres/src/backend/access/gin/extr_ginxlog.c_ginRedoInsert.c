#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flags; } ;
typedef  TYPE_1__ ginxlogInsert ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_9__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_2__ XLogReaderState ;
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;
typedef  int /*<<< orphan*/  BlockIdData ;
typedef  int /*<<< orphan*/  BlockId ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BLK_NEEDS_REDO ; 
 int /*<<< orphan*/  BlockIdGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int GIN_INSERT_ISDATA ; 
 int GIN_INSERT_ISLEAF ; 
 int GinPageIsData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidBlockNumber ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ XLogReadBufferForRedo (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* XLogRecGetBlockData (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* XLogRecGetData (TYPE_2__*) ; 
 int /*<<< orphan*/  ginRedoClearIncompleteSplit (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ginRedoInsertData (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ginRedoInsertEntry (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ginRedoInsert(XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	ginxlogInsert *data = (ginxlogInsert *) XLogRecGetData(record);
	Buffer		buffer;
#ifdef NOT_USED
	BlockNumber leftChildBlkno = InvalidBlockNumber;
#endif
	BlockNumber rightChildBlkno = InvalidBlockNumber;
	bool		isLeaf = (data->flags & GIN_INSERT_ISLEAF) != 0;

	/*
	 * First clear incomplete-split flag on child page if this finishes a
	 * split.
	 */
	if (!isLeaf)
	{
		char	   *payload = XLogRecGetData(record) + sizeof(ginxlogInsert);

#ifdef NOT_USED
		leftChildBlkno = BlockIdGetBlockNumber((BlockId) payload);
#endif
		payload += sizeof(BlockIdData);
		rightChildBlkno = BlockIdGetBlockNumber((BlockId) payload);
		payload += sizeof(BlockIdData);

		ginRedoClearIncompleteSplit(record, 1);
	}

	if (XLogReadBufferForRedo(record, 0, &buffer) == BLK_NEEDS_REDO)
	{
		Page		page = BufferGetPage(buffer);
		Size		len;
		char	   *payload = XLogRecGetBlockData(record, 0, &len);

		/* How to insert the payload is tree-type specific */
		if (data->flags & GIN_INSERT_ISDATA)
		{
			Assert(GinPageIsData(page));
			ginRedoInsertData(buffer, isLeaf, rightChildBlkno, payload);
		}
		else
		{
			Assert(!GinPageIsData(page));
			ginRedoInsertEntry(buffer, isLeaf, rightChildBlkno, payload);
		}

		PageSetLSN(page, lsn);
		MarkBufferDirty(buffer);
	}
	if (BufferIsValid(buffer))
		UnlockReleaseBuffer(buffer);
}