#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ xl_seq_rec ;
struct TYPE_14__ {int /*<<< orphan*/  magic; } ;
typedef  TYPE_2__ sequence_magic ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_17__ {int /*<<< orphan*/  t_ctid; int /*<<< orphan*/  t_infomask; } ;
struct TYPE_16__ {int t_len; TYPE_9__* t_data; } ;
struct TYPE_15__ {int /*<<< orphan*/  rd_node; } ;
typedef  TYPE_3__* Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  Item ;
typedef  TYPE_4__* HeapTuple ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 scalar_t__ BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPageSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FirstCommandId ; 
 scalar_t__ FirstOffsetNumber ; 
 int /*<<< orphan*/  FrozenTransactionId ; 
 int /*<<< orphan*/  GetTopTransactionId () ; 
 int /*<<< orphan*/  HEAP_XMAX_INVALID ; 
 int /*<<< orphan*/  HeapTupleHeaderSetCmin (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderSetXmax (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderSetXmin (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderSetXminFrozen (TYPE_9__*) ; 
 int /*<<< orphan*/  InvalidOffsetNumber ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 int /*<<< orphan*/  ItemPointerSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_NEW ; 
 scalar_t__ PageAddItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageInit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGBUF_WILL_INIT ; 
 int /*<<< orphan*/  RM_SEQ_ID ; 
 int /*<<< orphan*/  ReadBuffer (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ RelationNeedsWAL (TYPE_3__*) ; 
 int /*<<< orphan*/  SEQ_MAGIC ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLOG_SEQ_LOG ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
fill_seq_with_data(Relation rel, HeapTuple tuple)
{
	Buffer		buf;
	Page		page;
	sequence_magic *sm;
	OffsetNumber offnum;

	/* Initialize first page of relation with special magic number */

	buf = ReadBuffer(rel, P_NEW);
	Assert(BufferGetBlockNumber(buf) == 0);

	page = BufferGetPage(buf);

	PageInit(page, BufferGetPageSize(buf), sizeof(sequence_magic));
	sm = (sequence_magic *) PageGetSpecialPointer(page);
	sm->magic = SEQ_MAGIC;

	/* Now insert sequence tuple */

	LockBuffer(buf, BUFFER_LOCK_EXCLUSIVE);

	/*
	 * Since VACUUM does not process sequences, we have to force the tuple to
	 * have xmin = FrozenTransactionId now.  Otherwise it would become
	 * invisible to SELECTs after 2G transactions.  It is okay to do this
	 * because if the current transaction aborts, no other xact will ever
	 * examine the sequence tuple anyway.
	 */
	HeapTupleHeaderSetXmin(tuple->t_data, FrozenTransactionId);
	HeapTupleHeaderSetXminFrozen(tuple->t_data);
	HeapTupleHeaderSetCmin(tuple->t_data, FirstCommandId);
	HeapTupleHeaderSetXmax(tuple->t_data, InvalidTransactionId);
	tuple->t_data->t_infomask |= HEAP_XMAX_INVALID;
	ItemPointerSet(&tuple->t_data->t_ctid, 0, FirstOffsetNumber);

	/* check the comment above nextval_internal()'s equivalent call. */
	if (RelationNeedsWAL(rel))
		GetTopTransactionId();

	START_CRIT_SECTION();

	MarkBufferDirty(buf);

	offnum = PageAddItem(page, (Item) tuple->t_data, tuple->t_len,
						 InvalidOffsetNumber, false, false);
	if (offnum != FirstOffsetNumber)
		elog(ERROR, "failed to add sequence tuple to page");

	/* XLOG stuff */
	if (RelationNeedsWAL(rel))
	{
		xl_seq_rec	xlrec;
		XLogRecPtr	recptr;

		XLogBeginInsert();
		XLogRegisterBuffer(0, buf, REGBUF_WILL_INIT);

		xlrec.node = rel->rd_node;

		XLogRegisterData((char *) &xlrec, sizeof(xl_seq_rec));
		XLogRegisterData((char *) tuple->t_data, tuple->t_len);

		recptr = XLogInsert(RM_SEQ_ID, XLOG_SEQ_LOG);

		PageSetLSN(page, recptr);
	}

	END_CRIT_SECTION();

	UnlockReleaseBuffer(buf);
}