#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  new_bucket_flag; int /*<<< orphan*/  old_bucket_flag; } ;
typedef  TYPE_1__ xl_hash_split_complete ;
typedef  scalar_t__ XLogRedoAction ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_8__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_2__ XLogReaderState ;
struct TYPE_9__ {int /*<<< orphan*/  hasho_flag; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_3__* HashPageOpaque ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 scalar_t__ BLK_NEEDS_REDO ; 
 scalar_t__ BLK_RESTORED ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ XLogReadBufferForRedo (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ XLogRecGetData (TYPE_2__*) ; 

__attribute__((used)) static void
hash_xlog_split_complete(XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	xl_hash_split_complete *xlrec = (xl_hash_split_complete *) XLogRecGetData(record);
	Buffer		oldbuf;
	Buffer		newbuf;
	XLogRedoAction action;

	/* replay the record for old bucket */
	action = XLogReadBufferForRedo(record, 0, &oldbuf);

	/*
	 * Note that we still update the page even if it was restored from a full
	 * page image, because the bucket flag is not included in the image.
	 */
	if (action == BLK_NEEDS_REDO || action == BLK_RESTORED)
	{
		Page		oldpage;
		HashPageOpaque oldopaque;

		oldpage = BufferGetPage(oldbuf);
		oldopaque = (HashPageOpaque) PageGetSpecialPointer(oldpage);

		oldopaque->hasho_flag = xlrec->old_bucket_flag;

		PageSetLSN(oldpage, lsn);
		MarkBufferDirty(oldbuf);
	}
	if (BufferIsValid(oldbuf))
		UnlockReleaseBuffer(oldbuf);

	/* replay the record for new bucket */
	action = XLogReadBufferForRedo(record, 1, &newbuf);

	/*
	 * Note that we still update the page even if it was restored from a full
	 * page image, because the bucket flag is not included in the image.
	 */
	if (action == BLK_NEEDS_REDO || action == BLK_RESTORED)
	{
		Page		newpage;
		HashPageOpaque nopaque;

		newpage = BufferGetPage(newbuf);
		nopaque = (HashPageOpaque) PageGetSpecialPointer(newpage);

		nopaque->hasho_flag = xlrec->new_bucket_flag;

		PageSetLSN(newpage, lsn);
		MarkBufferDirty(newbuf);
	}
	if (BufferIsValid(newbuf))
		UnlockReleaseBuffer(newbuf);
}