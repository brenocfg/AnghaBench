#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  parentOffset; int /*<<< orphan*/  deleteXid; int /*<<< orphan*/  rightLink; } ;
typedef  TYPE_1__ ginxlogDeletePage ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_8__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_2__ XLogReaderState ;
struct TYPE_9__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  rightlink; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BLK_NEEDS_REDO ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIN_DELETED ; 
 int /*<<< orphan*/  GinPageDeletePostingItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* GinPageGetOpaque (int /*<<< orphan*/ ) ; 
 int GinPageIsData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GinPageIsLeaf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GinPageSetDeleteXid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ XLogReadBufferForRedo (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ XLogRecGetData (TYPE_2__*) ; 

__attribute__((used)) static void
ginRedoDeletePage(XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	ginxlogDeletePage *data = (ginxlogDeletePage *) XLogRecGetData(record);
	Buffer		dbuffer;
	Buffer		pbuffer;
	Buffer		lbuffer;
	Page		page;

	/*
	 * Lock left page first in order to prevent possible deadlock with
	 * ginStepRight().
	 */
	if (XLogReadBufferForRedo(record, 2, &lbuffer) == BLK_NEEDS_REDO)
	{
		page = BufferGetPage(lbuffer);
		Assert(GinPageIsData(page));
		GinPageGetOpaque(page)->rightlink = data->rightLink;
		PageSetLSN(page, lsn);
		MarkBufferDirty(lbuffer);
	}

	if (XLogReadBufferForRedo(record, 0, &dbuffer) == BLK_NEEDS_REDO)
	{
		page = BufferGetPage(dbuffer);
		Assert(GinPageIsData(page));
		GinPageGetOpaque(page)->flags = GIN_DELETED;
		GinPageSetDeleteXid(page, data->deleteXid);
		PageSetLSN(page, lsn);
		MarkBufferDirty(dbuffer);
	}

	if (XLogReadBufferForRedo(record, 1, &pbuffer) == BLK_NEEDS_REDO)
	{
		page = BufferGetPage(pbuffer);
		Assert(GinPageIsData(page));
		Assert(!GinPageIsLeaf(page));
		GinPageDeletePostingItem(page, data->parentOffset);
		PageSetLSN(page, lsn);
		MarkBufferDirty(pbuffer);
	}

	if (BufferIsValid(lbuffer))
		UnlockReleaseBuffer(lbuffer);
	if (BufferIsValid(pbuffer))
		UnlockReleaseBuffer(pbuffer);
	if (BufferIsValid(dbuffer))
		UnlockReleaseBuffer(dbuffer);
}