#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 scalar_t__ FirstOffsetNumber ; 
 int /*<<< orphan*/  GistClearPageHasGarbage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GistPageIsLeaf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 scalar_t__ ItemIdIsDead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int MaxIndexTuplesPerPage ; 
 scalar_t__ OffsetNumberNext (scalar_t__) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageIndexMultiDelete (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 scalar_t__ XLogStandbyInfoActive () ; 
 int /*<<< orphan*/  gistGetFakeLSN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gistXLogDelete (int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_compute_xid_horizon_for_tuples (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static void
gistprunepage(Relation rel, Page page, Buffer buffer, Relation heapRel)
{
	OffsetNumber deletable[MaxIndexTuplesPerPage];
	int			ndeletable = 0;
	OffsetNumber offnum,
				maxoff;
	TransactionId latestRemovedXid = InvalidTransactionId;

	Assert(GistPageIsLeaf(page));

	/*
	 * Scan over all items to see which ones need to be deleted according to
	 * LP_DEAD flags.
	 */
	maxoff = PageGetMaxOffsetNumber(page);
	for (offnum = FirstOffsetNumber;
		 offnum <= maxoff;
		 offnum = OffsetNumberNext(offnum))
	{
		ItemId		itemId = PageGetItemId(page, offnum);

		if (ItemIdIsDead(itemId))
			deletable[ndeletable++] = offnum;
	}

	if (XLogStandbyInfoActive() && RelationNeedsWAL(rel))
		latestRemovedXid =
			index_compute_xid_horizon_for_tuples(rel, heapRel, buffer,
												 deletable, ndeletable);

	if (ndeletable > 0)
	{
		START_CRIT_SECTION();

		PageIndexMultiDelete(page, deletable, ndeletable);

		/*
		 * Mark the page as not containing any LP_DEAD items.  This is not
		 * certainly true (there might be some that have recently been marked,
		 * but weren't included in our target-item list), but it will almost
		 * always be true and it doesn't seem worth an additional page scan to
		 * check it. Remember that F_HAS_GARBAGE is only a hint anyway.
		 */
		GistClearPageHasGarbage(page);

		MarkBufferDirty(buffer);

		/* XLOG stuff */
		if (RelationNeedsWAL(rel))
		{
			XLogRecPtr	recptr;

			recptr = gistXLogDelete(buffer,
									deletable, ndeletable,
									latestRemovedXid);

			PageSetLSN(page, recptr);
		}
		else
			PageSetLSN(page, gistGetFakeLSN(rel));

		END_CRIT_SECTION();
	}

	/*
	 * Note: if we didn't find any LP_DEAD items, then the page's
	 * F_HAS_GARBAGE hint bit is falsely set.  We do not bother expending a
	 * separate write to clear it, however.  We will clear it when we split
	 * the page.
	 */
}