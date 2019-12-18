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
struct TYPE_8__ {int ntups; scalar_t__ is_prim_bucket_same_wrt; } ;
typedef  TYPE_1__ xl_hash_move_page_contents ;
typedef  size_t uint16 ;
typedef  scalar_t__ XLogRedoAction ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_9__ {int /*<<< orphan*/  EndRecPtr; } ;
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
 int IndexTupleSize (scalar_t__) ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 scalar_t__ InvalidOffsetNumber ; 
 int MAXALIGN (int) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ PageAddItem (scalar_t__,int /*<<< orphan*/ ,int,scalar_t__,int,int) ; 
 int /*<<< orphan*/  PageIndexMultiDelete (scalar_t__,scalar_t__*,int) ; 
 int /*<<< orphan*/  PageSetLSN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RBM_NORMAL ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ XLogReadBufferForRedo (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ XLogReadBufferForRedoExtended (TYPE_2__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 char* XLogRecGetBlockData (TYPE_2__*,int,int*) ; 
 scalar_t__ XLogRecGetData (TYPE_2__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
hash_xlog_move_page_contents(XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	xl_hash_move_page_contents *xldata = (xl_hash_move_page_contents *) XLogRecGetData(record);
	Buffer		bucketbuf = InvalidBuffer;
	Buffer		writebuf = InvalidBuffer;
	Buffer		deletebuf = InvalidBuffer;
	XLogRedoAction action;

	/*
	 * Ensure we have a cleanup lock on primary bucket page before we start
	 * with the actual replay operation.  This is to ensure that neither a
	 * scan can start nor a scan can be already-in-progress during the replay
	 * of this operation.  If we allow scans during this operation, then they
	 * can miss some records or show the same record multiple times.
	 */
	if (xldata->is_prim_bucket_same_wrt)
		action = XLogReadBufferForRedoExtended(record, 1, RBM_NORMAL, true, &writebuf);
	else
	{
		/*
		 * we don't care for return value as the purpose of reading bucketbuf
		 * is to ensure a cleanup lock on primary bucket page.
		 */
		(void) XLogReadBufferForRedoExtended(record, 0, RBM_NORMAL, true, &bucketbuf);

		action = XLogReadBufferForRedo(record, 1, &writebuf);
	}

	/* replay the record for adding entries in overflow buffer */
	if (action == BLK_NEEDS_REDO)
	{
		Page		writepage;
		char	   *begin;
		char	   *data;
		Size		datalen;
		uint16		ninserted = 0;

		data = begin = XLogRecGetBlockData(record, 1, &datalen);

		writepage = (Page) BufferGetPage(writebuf);

		if (xldata->ntups > 0)
		{
			OffsetNumber *towrite = (OffsetNumber *) data;

			data += sizeof(OffsetNumber) * xldata->ntups;

			while (data - begin < datalen)
			{
				IndexTuple	itup = (IndexTuple) data;
				Size		itemsz;
				OffsetNumber l;

				itemsz = IndexTupleSize(itup);
				itemsz = MAXALIGN(itemsz);

				data += itemsz;

				l = PageAddItem(writepage, (Item) itup, itemsz, towrite[ninserted], false, false);
				if (l == InvalidOffsetNumber)
					elog(ERROR, "hash_xlog_move_page_contents: failed to add item to hash index page, size %d bytes",
						 (int) itemsz);

				ninserted++;
			}
		}

		/*
		 * number of tuples inserted must be same as requested in REDO record.
		 */
		Assert(ninserted == xldata->ntups);

		PageSetLSN(writepage, lsn);
		MarkBufferDirty(writebuf);
	}

	/* replay the record for deleting entries from overflow buffer */
	if (XLogReadBufferForRedo(record, 2, &deletebuf) == BLK_NEEDS_REDO)
	{
		Page		page;
		char	   *ptr;
		Size		len;

		ptr = XLogRecGetBlockData(record, 2, &len);

		page = (Page) BufferGetPage(deletebuf);

		if (len > 0)
		{
			OffsetNumber *unused;
			OffsetNumber *unend;

			unused = (OffsetNumber *) ptr;
			unend = (OffsetNumber *) ((char *) ptr + len);

			if ((unend - unused) > 0)
				PageIndexMultiDelete(page, unused, unend - unused);
		}

		PageSetLSN(page, lsn);
		MarkBufferDirty(deletebuf);
	}

	/*
	 * Replay is complete, now we can release the buffers. We release locks at
	 * end of replay operation to ensure that we hold lock on primary bucket
	 * page till end of operation.  We can optimize by releasing the lock on
	 * write buffer as soon as the operation for same is complete, if it is
	 * not same as primary bucket page, but that doesn't seem to be worth
	 * complicating the code.
	 */
	if (BufferIsValid(deletebuf))
		UnlockReleaseBuffer(deletebuf);

	if (BufferIsValid(writebuf))
		UnlockReleaseBuffer(writebuf);

	if (BufferIsValid(bucketbuf))
		UnlockReleaseBuffer(bucketbuf);
}