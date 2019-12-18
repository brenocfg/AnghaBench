#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  bt_blkno; } ;
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  TYPE_1__ BrinTuple ;
typedef  int /*<<< orphan*/  BrinRevmap ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BRIN_EVACUATE_PAGE ; 
 int /*<<< orphan*/  BRIN_IS_REGULAR_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUFFER_LOCK_SHARE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int BrinPageFlags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 scalar_t__ FirstOffsetNumber ; 
 int /*<<< orphan*/  ItemIdGetLength (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemIdIsUsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 TYPE_1__* brin_copy_tuple (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brin_doupdate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
brin_evacuate_page(Relation idxRel, BlockNumber pagesPerRange,
				   BrinRevmap *revmap, Buffer buf)
{
	OffsetNumber off;
	OffsetNumber maxoff;
	Page		page;
	BrinTuple  *btup = NULL;
	Size		btupsz = 0;

	page = BufferGetPage(buf);

	Assert(BrinPageFlags(page) & BRIN_EVACUATE_PAGE);

	maxoff = PageGetMaxOffsetNumber(page);
	for (off = FirstOffsetNumber; off <= maxoff; off++)
	{
		BrinTuple  *tup;
		Size		sz;
		ItemId		lp;

		CHECK_FOR_INTERRUPTS();

		lp = PageGetItemId(page, off);
		if (ItemIdIsUsed(lp))
		{
			sz = ItemIdGetLength(lp);
			tup = (BrinTuple *) PageGetItem(page, lp);
			tup = brin_copy_tuple(tup, sz, btup, &btupsz);

			LockBuffer(buf, BUFFER_LOCK_UNLOCK);

			if (!brin_doupdate(idxRel, pagesPerRange, revmap, tup->bt_blkno,
							   buf, off, tup, sz, tup, sz, false))
				off--;			/* retry */

			LockBuffer(buf, BUFFER_LOCK_SHARE);

			/* It's possible that someone extended the revmap over this page */
			if (!BRIN_IS_REGULAR_PAGE(page))
				break;
		}
	}

	UnlockReleaseBuffer(buf);
}