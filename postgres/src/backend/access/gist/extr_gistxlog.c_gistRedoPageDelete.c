#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  downlinkOffset; int /*<<< orphan*/  deleteXid; } ;
typedef  TYPE_1__ gistxlogPageDelete ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_7__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_2__ XLogReaderState ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 scalar_t__ BLK_NEEDS_REDO ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GistPageSetDeleted (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageIndexTupleDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ XLogReadBufferForRedo (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ XLogRecGetData (TYPE_2__*) ; 

__attribute__((used)) static void
gistRedoPageDelete(XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	gistxlogPageDelete *xldata = (gistxlogPageDelete *) XLogRecGetData(record);
	Buffer		parentBuffer;
	Buffer		leafBuffer;

	if (XLogReadBufferForRedo(record, 0, &leafBuffer) == BLK_NEEDS_REDO)
	{
		Page		page = (Page) BufferGetPage(leafBuffer);

		GistPageSetDeleted(page, xldata->deleteXid);

		PageSetLSN(page, lsn);
		MarkBufferDirty(leafBuffer);
	}

	if (XLogReadBufferForRedo(record, 1, &parentBuffer) == BLK_NEEDS_REDO)
	{
		Page		page = (Page) BufferGetPage(parentBuffer);

		PageIndexTupleDelete(page, xldata->downlinkOffset);

		PageSetLSN(page, lsn);
		MarkBufferDirty(parentBuffer);
	}

	if (BufferIsValid(parentBuffer))
		UnlockReleaseBuffer(parentBuffer);
	if (BufferIsValid(leafBuffer))
		UnlockReleaseBuffer(leafBuffer);
}