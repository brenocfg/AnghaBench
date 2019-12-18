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
struct TYPE_8__ {int /*<<< orphan*/  ntodelete; int /*<<< orphan*/  latestRemovedXid; } ;
typedef  TYPE_1__ gistxlogDelete ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_9__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_2__ XLogReaderState ;
typedef  int /*<<< orphan*/  RelFileNode ;
typedef  scalar_t__ Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 scalar_t__ BLK_NEEDS_REDO ; 
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GistClearPageHasGarbage (scalar_t__) ; 
 int /*<<< orphan*/  GistMarkTuplesDeleted (scalar_t__) ; 
 scalar_t__ InHotStandby ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageIndexMultiDelete (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResolveRecoveryConflictWithSnapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SizeOfGistxlogDelete ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ XLogReadBufferForRedo (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLogRecGetBlockTag (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ XLogRecGetData (TYPE_2__*) ; 
 scalar_t__ XLogRecGetDataLen (TYPE_2__*) ; 

__attribute__((used)) static void
gistRedoDeleteRecord(XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	gistxlogDelete *xldata = (gistxlogDelete *) XLogRecGetData(record);
	Buffer		buffer;
	Page		page;

	/*
	 * If we have any conflict processing to do, it must happen before we
	 * update the page.
	 *
	 * GiST delete records can conflict with standby queries.  You might think
	 * that vacuum records would conflict as well, but we've handled that
	 * already.  XLOG_HEAP2_CLEANUP_INFO records provide the highest xid
	 * cleaned by the vacuum of the heap and so we can resolve any conflicts
	 * just once when that arrives.  After that we know that no conflicts
	 * exist from individual gist vacuum records on that index.
	 */
	if (InHotStandby)
	{
		RelFileNode rnode;

		XLogRecGetBlockTag(record, 0, &rnode, NULL, NULL);

		ResolveRecoveryConflictWithSnapshot(xldata->latestRemovedXid, rnode);
	}

	if (XLogReadBufferForRedo(record, 0, &buffer) == BLK_NEEDS_REDO)
	{
		page = (Page) BufferGetPage(buffer);

		if (XLogRecGetDataLen(record) > SizeOfGistxlogDelete)
		{
			OffsetNumber *todelete;

			todelete = (OffsetNumber *) ((char *) xldata + SizeOfGistxlogDelete);

			PageIndexMultiDelete(page, todelete, xldata->ntodelete);
		}

		GistClearPageHasGarbage(page);
		GistMarkTuplesDeleted(page);

		PageSetLSN(page, lsn);
		MarkBufferDirty(buffer);
	}

	if (BufferIsValid(buffer))
		UnlockReleaseBuffer(buffer);
}