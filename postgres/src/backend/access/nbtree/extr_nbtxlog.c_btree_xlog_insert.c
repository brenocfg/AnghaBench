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
struct TYPE_9__ {int /*<<< orphan*/  offnum; } ;
typedef  TYPE_1__ xl_btree_insert ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_10__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_2__ XLogReaderState ;
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Item ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 scalar_t__ BLK_NEEDS_REDO ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidOffsetNumber ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PANIC ; 
 scalar_t__ PageAddItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ XLogReadBufferForRedo (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* XLogRecGetBlockData (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ XLogRecGetData (TYPE_2__*) ; 
 int /*<<< orphan*/  _bt_clear_incomplete_split (TYPE_2__*,int) ; 
 int /*<<< orphan*/  _bt_restore_meta (TYPE_2__*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
btree_xlog_insert(bool isleaf, bool ismeta, XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	xl_btree_insert *xlrec = (xl_btree_insert *) XLogRecGetData(record);
	Buffer		buffer;
	Page		page;

	/*
	 * Insertion to an internal page finishes an incomplete split at the child
	 * level.  Clear the incomplete-split flag in the child.  Note: during
	 * normal operation, the child and parent pages are locked at the same
	 * time, so that clearing the flag and inserting the downlink appear
	 * atomic to other backends.  We don't bother with that during replay,
	 * because readers don't care about the incomplete-split flag and there
	 * cannot be updates happening.
	 */
	if (!isleaf)
		_bt_clear_incomplete_split(record, 1);
	if (XLogReadBufferForRedo(record, 0, &buffer) == BLK_NEEDS_REDO)
	{
		Size		datalen;
		char	   *datapos = XLogRecGetBlockData(record, 0, &datalen);

		page = BufferGetPage(buffer);

		if (PageAddItem(page, (Item) datapos, datalen, xlrec->offnum,
						false, false) == InvalidOffsetNumber)
			elog(PANIC, "btree_xlog_insert: failed to add item");

		PageSetLSN(page, lsn);
		MarkBufferDirty(buffer);
	}
	if (BufferIsValid(buffer))
		UnlockReleaseBuffer(buffer);

	/*
	 * Note: in normal operation, we'd update the metapage while still holding
	 * lock on the page we inserted into.  But during replay it's not
	 * necessary to hold that lock, since no other index updates can be
	 * happening concurrently, and readers will cope fine with following an
	 * obsolete link from the metapage.
	 */
	if (ismeta)
		_bt_restore_meta(record, 2);
}