#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nitems; int /*<<< orphan*/  latestRemovedXid; } ;
typedef  TYPE_1__ xl_btree_delete ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_4__ {int /*<<< orphan*/  btpo_flags; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  TYPE_2__* BTPageOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BTP_HAS_GARBAGE ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageIndexMultiDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGBUF_STANDARD ; 
 int /*<<< orphan*/  RM_BTREE_ID ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int SizeOfBtreeDelete ; 
 int /*<<< orphan*/  XLOG_BTREE_DELETE ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 
 scalar_t__ XLogStandbyInfoActive () ; 
 int /*<<< orphan*/  index_compute_xid_horizon_for_tuples (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void
_bt_delitems_delete(Relation rel, Buffer buf,
					OffsetNumber *itemnos, int nitems,
					Relation heapRel)
{
	Page		page = BufferGetPage(buf);
	BTPageOpaque opaque;
	TransactionId latestRemovedXid = InvalidTransactionId;

	/* Shouldn't be called unless there's something to do */
	Assert(nitems > 0);

	if (XLogStandbyInfoActive() && RelationNeedsWAL(rel))
		latestRemovedXid =
			index_compute_xid_horizon_for_tuples(rel, heapRel, buf,
												 itemnos, nitems);

	/* No ereport(ERROR) until changes are logged */
	START_CRIT_SECTION();

	/* Fix the page */
	PageIndexMultiDelete(page, itemnos, nitems);

	/*
	 * Unlike _bt_delitems_vacuum, we *must not* clear the vacuum cycle ID,
	 * because this is not called by VACUUM.
	 */

	/*
	 * Mark the page as not containing any LP_DEAD items.  This is not
	 * certainly true (there might be some that have recently been marked, but
	 * weren't included in our target-item list), but it will almost always be
	 * true and it doesn't seem worth an additional page scan to check it.
	 * Remember that BTP_HAS_GARBAGE is only a hint anyway.
	 */
	opaque = (BTPageOpaque) PageGetSpecialPointer(page);
	opaque->btpo_flags &= ~BTP_HAS_GARBAGE;

	MarkBufferDirty(buf);

	/* XLOG stuff */
	if (RelationNeedsWAL(rel))
	{
		XLogRecPtr	recptr;
		xl_btree_delete xlrec_delete;

		xlrec_delete.latestRemovedXid = latestRemovedXid;
		xlrec_delete.nitems = nitems;

		XLogBeginInsert();
		XLogRegisterBuffer(0, buf, REGBUF_STANDARD);
		XLogRegisterData((char *) &xlrec_delete, SizeOfBtreeDelete);

		/*
		 * We need the target-offsets array whether or not we store the whole
		 * buffer, to allow us to find the latestRemovedXid on a standby
		 * server.
		 */
		XLogRegisterData((char *) itemnos, nitems * sizeof(OffsetNumber));

		recptr = XLogInsert(RM_BTREE_ID, XLOG_BTREE_DELETE);

		PageSetLSN(page, recptr);
	}

	END_CRIT_SECTION();
}