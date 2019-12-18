#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* offnum; } ;
typedef  TYPE_1__ xl_heap_confirm ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_5__ {int /*<<< orphan*/  t_ctid; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  int /*<<< orphan*/ * ItemId ;
typedef  TYPE_2__* HeapTupleHeader ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HeapTupleHeaderIsSpeculative (TYPE_2__*) ; 
 int /*<<< orphan*/  ItemIdIsNormal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerGetBlockNumber (int /*<<< orphan*/ *) ; 
 void* ItemPointerGetOffsetNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ MaxOffsetNumber ; 
 scalar_t__ PageGetItem (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PageGetItemId (scalar_t__,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (scalar_t__) ; 
 int /*<<< orphan*/  PageSetLSN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGBUF_STANDARD ; 
 int /*<<< orphan*/  RM_HEAP_ID ; 
 int /*<<< orphan*/  ReadBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  SizeOfHeapConfirm ; 
 scalar_t__ SpecTokenOffsetNumber ; 
 int /*<<< orphan*/  StaticAssertStmt (int,char*) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLOG_HEAP_CONFIRM ; 
 int /*<<< orphan*/  XLOG_INCLUDE_ORIGIN ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogSetRecordFlags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

void
heap_finish_speculative(Relation relation, ItemPointer tid)
{
	Buffer		buffer;
	Page		page;
	OffsetNumber offnum;
	ItemId		lp = NULL;
	HeapTupleHeader htup;

	buffer = ReadBuffer(relation, ItemPointerGetBlockNumber(tid));
	LockBuffer(buffer, BUFFER_LOCK_EXCLUSIVE);
	page = (Page) BufferGetPage(buffer);

	offnum = ItemPointerGetOffsetNumber(tid);
	if (PageGetMaxOffsetNumber(page) >= offnum)
		lp = PageGetItemId(page, offnum);

	if (PageGetMaxOffsetNumber(page) < offnum || !ItemIdIsNormal(lp))
		elog(ERROR, "invalid lp");

	htup = (HeapTupleHeader) PageGetItem(page, lp);

	/* SpecTokenOffsetNumber should be distinguishable from any real offset */
	StaticAssertStmt(MaxOffsetNumber < SpecTokenOffsetNumber,
					 "invalid speculative token constant");

	/* NO EREPORT(ERROR) from here till changes are logged */
	START_CRIT_SECTION();

	Assert(HeapTupleHeaderIsSpeculative(htup));

	MarkBufferDirty(buffer);

	/*
	 * Replace the speculative insertion token with a real t_ctid, pointing to
	 * itself like it does on regular tuples.
	 */
	htup->t_ctid = *tid;

	/* XLOG stuff */
	if (RelationNeedsWAL(relation))
	{
		xl_heap_confirm xlrec;
		XLogRecPtr	recptr;

		xlrec.offnum = ItemPointerGetOffsetNumber(tid);

		XLogBeginInsert();

		/* We want the same filtering on this as on a plain insert */
		XLogSetRecordFlags(XLOG_INCLUDE_ORIGIN);

		XLogRegisterData((char *) &xlrec, SizeOfHeapConfirm);
		XLogRegisterBuffer(0, buffer, REGBUF_STANDARD);

		recptr = XLogInsert(RM_HEAP_ID, XLOG_HEAP_CONFIRM);

		PageSetLSN(page, recptr);
	}

	END_CRIT_SECTION();

	UnlockReleaseBuffer(buffer);
}