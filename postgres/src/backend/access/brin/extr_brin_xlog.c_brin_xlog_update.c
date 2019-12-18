#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  insert; int /*<<< orphan*/  oldOffnum; } ;
typedef  TYPE_1__ xl_brin_update ;
typedef  scalar_t__ XLogRedoAction ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_8__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_2__ XLogReaderState ;
typedef  scalar_t__ Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 scalar_t__ BLK_NEEDS_REDO ; 
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageIndexTupleDeleteNoCompact (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ XLogReadBufferForRedo (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ XLogRecGetData (TYPE_2__*) ; 
 int /*<<< orphan*/  brin_xlog_insert_update (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
brin_xlog_update(XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	xl_brin_update *xlrec = (xl_brin_update *) XLogRecGetData(record);
	Buffer		buffer;
	XLogRedoAction action;

	/* First remove the old tuple */
	action = XLogReadBufferForRedo(record, 2, &buffer);
	if (action == BLK_NEEDS_REDO)
	{
		Page		page;
		OffsetNumber offnum;

		page = (Page) BufferGetPage(buffer);

		offnum = xlrec->oldOffnum;

		PageIndexTupleDeleteNoCompact(page, offnum);

		PageSetLSN(page, lsn);
		MarkBufferDirty(buffer);
	}

	/* Then insert the new tuple and update revmap, like in an insertion. */
	brin_xlog_insert_update(record, &xlrec->insert);

	if (BufferIsValid(buffer))
		UnlockReleaseBuffer(buffer);
}