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
struct TYPE_3__ {int /*<<< orphan*/  lastBlockVacuumed; } ;
typedef  TYPE_1__ xl_btree_vacuum ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_4__ {int /*<<< orphan*/  btpo_flags; scalar_t__ btpo_cycleid; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;
typedef  TYPE_2__* BTPageOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  BTP_HAS_GARBAGE ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageIndexMultiDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGBUF_STANDARD ; 
 int /*<<< orphan*/  RM_BTREE_ID ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  SizeOfBtreeVacuum ; 
 int /*<<< orphan*/  XLOG_BTREE_VACUUM ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBufData (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int /*<<< orphan*/ ) ; 

void
_bt_delitems_vacuum(Relation rel, Buffer buf,
					OffsetNumber *itemnos, int nitems,
					BlockNumber lastBlockVacuumed)
{
	Page		page = BufferGetPage(buf);
	BTPageOpaque opaque;

	/* No ereport(ERROR) until changes are logged */
	START_CRIT_SECTION();

	/* Fix the page */
	if (nitems > 0)
		PageIndexMultiDelete(page, itemnos, nitems);

	/*
	 * We can clear the vacuum cycle ID since this page has certainly been
	 * processed by the current vacuum scan.
	 */
	opaque = (BTPageOpaque) PageGetSpecialPointer(page);
	opaque->btpo_cycleid = 0;

	/*
	 * Mark the page as not containing any LP_DEAD items.  This is not
	 * certainly true (there might be some that have recently been marked, but
	 * weren't included in our target-item list), but it will almost always be
	 * true and it doesn't seem worth an additional page scan to check it.
	 * Remember that BTP_HAS_GARBAGE is only a hint anyway.
	 */
	opaque->btpo_flags &= ~BTP_HAS_GARBAGE;

	MarkBufferDirty(buf);

	/* XLOG stuff */
	if (RelationNeedsWAL(rel))
	{
		XLogRecPtr	recptr;
		xl_btree_vacuum xlrec_vacuum;

		xlrec_vacuum.lastBlockVacuumed = lastBlockVacuumed;

		XLogBeginInsert();
		XLogRegisterBuffer(0, buf, REGBUF_STANDARD);
		XLogRegisterData((char *) &xlrec_vacuum, SizeOfBtreeVacuum);

		/*
		 * The target-offsets array is not in the buffer, but pretend that it
		 * is.  When XLogInsert stores the whole buffer, the offsets array
		 * need not be stored too.
		 */
		if (nitems > 0)
			XLogRegisterBufData(0, (char *) itemnos, nitems * sizeof(OffsetNumber));

		recptr = XLogInsert(RM_BTREE_ID, XLOG_BTREE_VACUUM);

		PageSetLSN(page, recptr);
	}

	END_CRIT_SECTION();
}