#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ xmax; int /*<<< orphan*/  offnum; int /*<<< orphan*/  infobits_set; int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__ xl_heap_delete ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  scalar_t__ TransactionId ;
struct TYPE_15__ {int /*<<< orphan*/  t_self; TYPE_4__* t_data; int /*<<< orphan*/  t_len; int /*<<< orphan*/  t_tableOid; } ;
struct TYPE_11__ {scalar_t__ t_xmin; } ;
struct TYPE_12__ {TYPE_1__ t_heap; } ;
struct TYPE_14__ {int t_infomask; int /*<<< orphan*/  t_infomask2; int /*<<< orphan*/  t_ctid; TYPE_2__ t_choice; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  TYPE_4__* HeapTupleHeader ;
typedef  TYPE_5__ HeapTupleData ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GetCurrentTransactionId () ; 
 int /*<<< orphan*/  HEAP_KEYS_UPDATED ; 
 int HEAP_MOVED ; 
 int HEAP_XMAX_BITS ; 
 scalar_t__ HeapTupleHasExternal (TYPE_5__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderIsHeapOnly (TYPE_4__*) ; 
 scalar_t__ HeapTupleHeaderIsSpeculative (TYPE_4__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderSetXmin (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 scalar_t__ IsToastRelation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemIdGetLength (int /*<<< orphan*/ ) ; 
 int ItemIdIsNormal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemPointerGetBlockNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerGetOffsetNumber (int /*<<< orphan*/ *) ; 
 int ItemPointerIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageIsAllVisible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetPrunable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGBUF_STANDARD ; 
 int /*<<< orphan*/  RM_HEAP_ID ; 
 int /*<<< orphan*/  ReadBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RecentGlobalXmin ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  SizeOfHeapDelete ; 
 int TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLH_DELETE_IS_SUPER ; 
 int /*<<< orphan*/  XLOG_HEAP_DELETE ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compute_infobits (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  heap_toast_delete (int /*<<< orphan*/ ,TYPE_5__*,int) ; 
 int /*<<< orphan*/  pgstat_count_heap_delete (int /*<<< orphan*/ ) ; 

void
heap_abort_speculative(Relation relation, ItemPointer tid)
{
	TransactionId xid = GetCurrentTransactionId();
	ItemId		lp;
	HeapTupleData tp;
	Page		page;
	BlockNumber block;
	Buffer		buffer;

	Assert(ItemPointerIsValid(tid));

	block = ItemPointerGetBlockNumber(tid);
	buffer = ReadBuffer(relation, block);
	page = BufferGetPage(buffer);

	LockBuffer(buffer, BUFFER_LOCK_EXCLUSIVE);

	/*
	 * Page can't be all visible, we just inserted into it, and are still
	 * running.
	 */
	Assert(!PageIsAllVisible(page));

	lp = PageGetItemId(page, ItemPointerGetOffsetNumber(tid));
	Assert(ItemIdIsNormal(lp));

	tp.t_tableOid = RelationGetRelid(relation);
	tp.t_data = (HeapTupleHeader) PageGetItem(page, lp);
	tp.t_len = ItemIdGetLength(lp);
	tp.t_self = *tid;

	/*
	 * Sanity check that the tuple really is a speculatively inserted tuple,
	 * inserted by us.
	 */
	if (tp.t_data->t_choice.t_heap.t_xmin != xid)
		elog(ERROR, "attempted to kill a tuple inserted by another transaction");
	if (!(IsToastRelation(relation) || HeapTupleHeaderIsSpeculative(tp.t_data)))
		elog(ERROR, "attempted to kill a non-speculative tuple");
	Assert(!HeapTupleHeaderIsHeapOnly(tp.t_data));

	/*
	 * No need to check for serializable conflicts here.  There is never a
	 * need for a combocid, either.  No need to extract replica identity, or
	 * do anything special with infomask bits.
	 */

	START_CRIT_SECTION();

	/*
	 * The tuple will become DEAD immediately.  Flag that this page
	 * immediately is a candidate for pruning by setting xmin to
	 * RecentGlobalXmin.  That's not pretty, but it doesn't seem worth
	 * inventing a nicer API for this.
	 */
	Assert(TransactionIdIsValid(RecentGlobalXmin));
	PageSetPrunable(page, RecentGlobalXmin);

	/* store transaction information of xact deleting the tuple */
	tp.t_data->t_infomask &= ~(HEAP_XMAX_BITS | HEAP_MOVED);
	tp.t_data->t_infomask2 &= ~HEAP_KEYS_UPDATED;

	/*
	 * Set the tuple header xmin to InvalidTransactionId.  This makes the
	 * tuple immediately invisible everyone.  (In particular, to any
	 * transactions waiting on the speculative token, woken up later.)
	 */
	HeapTupleHeaderSetXmin(tp.t_data, InvalidTransactionId);

	/* Clear the speculative insertion token too */
	tp.t_data->t_ctid = tp.t_self;

	MarkBufferDirty(buffer);

	/*
	 * XLOG stuff
	 *
	 * The WAL records generated here match heap_delete().  The same recovery
	 * routines are used.
	 */
	if (RelationNeedsWAL(relation))
	{
		xl_heap_delete xlrec;
		XLogRecPtr	recptr;

		xlrec.flags = XLH_DELETE_IS_SUPER;
		xlrec.infobits_set = compute_infobits(tp.t_data->t_infomask,
											  tp.t_data->t_infomask2);
		xlrec.offnum = ItemPointerGetOffsetNumber(&tp.t_self);
		xlrec.xmax = xid;

		XLogBeginInsert();
		XLogRegisterData((char *) &xlrec, SizeOfHeapDelete);
		XLogRegisterBuffer(0, buffer, REGBUF_STANDARD);

		/* No replica identity & replication origin logged */

		recptr = XLogInsert(RM_HEAP_ID, XLOG_HEAP_DELETE);

		PageSetLSN(page, recptr);
	}

	END_CRIT_SECTION();

	LockBuffer(buffer, BUFFER_LOCK_UNLOCK);

	if (HeapTupleHasExternal(&tp))
	{
		Assert(!IsToastRelation(relation));
		heap_toast_delete(relation, &tp, true);
	}

	/*
	 * Never need to mark tuple for invalidation, since catalogs don't support
	 * speculative insertion
	 */

	/* Now we can release the buffer */
	ReleaseBuffer(buffer);

	/* count deletion, as we counted the insertion too */
	pgstat_count_heap_delete(relation);
}