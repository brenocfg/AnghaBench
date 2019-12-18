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
typedef  int /*<<< orphan*/  xl_seq_rec ;
typedef  scalar_t__ uint8 ;
struct TYPE_8__ {int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ sequence_magic ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_9__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_2__ XLogReaderState ;
typedef  scalar_t__ Size ;
typedef  scalar_t__ Page ;
typedef  int /*<<< orphan*/  Item ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPageSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FirstOffsetNumber ; 
 scalar_t__ InvalidOffsetNumber ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PANIC ; 
 scalar_t__ PageAddItem (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ PageGetSpecialPointer (scalar_t__) ; 
 int /*<<< orphan*/  PageInit (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PageSetLSN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEQ_MAGIC ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ XLOG_SEQ_LOG ; 
 scalar_t__ XLR_INFO_MASK ; 
 int /*<<< orphan*/  XLogInitBufferForRedo (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ XLogRecGetData (TYPE_2__*) ; 
 scalar_t__ XLogRecGetDataLen (TYPE_2__*) ; 
 scalar_t__ XLogRecGetInfo (TYPE_2__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (scalar_t__) ; 

void
seq_redo(XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	uint8		info = XLogRecGetInfo(record) & ~XLR_INFO_MASK;
	Buffer		buffer;
	Page		page;
	Page		localpage;
	char	   *item;
	Size		itemsz;
	xl_seq_rec *xlrec = (xl_seq_rec *) XLogRecGetData(record);
	sequence_magic *sm;

	if (info != XLOG_SEQ_LOG)
		elog(PANIC, "seq_redo: unknown op code %u", info);

	buffer = XLogInitBufferForRedo(record, 0);
	page = (Page) BufferGetPage(buffer);

	/*
	 * We always reinit the page.  However, since this WAL record type is also
	 * used for updating sequences, it's possible that a hot-standby backend
	 * is examining the page concurrently; so we mustn't transiently trash the
	 * buffer.  The solution is to build the correct new page contents in
	 * local workspace and then memcpy into the buffer.  Then only bytes that
	 * are supposed to change will change, even transiently. We must palloc
	 * the local page for alignment reasons.
	 */
	localpage = (Page) palloc(BufferGetPageSize(buffer));

	PageInit(localpage, BufferGetPageSize(buffer), sizeof(sequence_magic));
	sm = (sequence_magic *) PageGetSpecialPointer(localpage);
	sm->magic = SEQ_MAGIC;

	item = (char *) xlrec + sizeof(xl_seq_rec);
	itemsz = XLogRecGetDataLen(record) - sizeof(xl_seq_rec);

	if (PageAddItem(localpage, (Item) item, itemsz,
					FirstOffsetNumber, false, false) == InvalidOffsetNumber)
		elog(PANIC, "seq_redo: failed to add item to page");

	PageSetLSN(localpage, lsn);

	memcpy(page, localpage, BufferGetPageSize(buffer));
	MarkBufferDirty(buffer);
	UnlockReleaseBuffer(buffer);

	pfree(localpage);
}