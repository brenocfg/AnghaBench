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
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_5__ {scalar_t__ pd_prune_xid; } ;
struct TYPE_4__ {scalar_t__ new_prune_xid; int nredirected; int ndead; int nunused; int /*<<< orphan*/  latestRemovedXid; int /*<<< orphan*/  nowunused; int /*<<< orphan*/  nowdead; int /*<<< orphan*/  redirected; scalar_t__* marked; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ PruneState ;
typedef  TYPE_2__* PageHeader ;
typedef  scalar_t__ Page ;
typedef  size_t OffsetNumber ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 size_t FirstOffsetNumber ; 
 scalar_t__ InvalidTransactionId ; 
 scalar_t__ ItemIdIsDead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemIdIsUsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirtyHint (int /*<<< orphan*/ ,int) ; 
 size_t OffsetNumberNext (size_t) ; 
 int /*<<< orphan*/  PageClearFull (scalar_t__) ; 
 int /*<<< orphan*/  PageGetItemId (scalar_t__,size_t) ; 
 size_t PageGetMaxOffsetNumber (scalar_t__) ; 
 scalar_t__ PageIsFull (scalar_t__) ; 
 int /*<<< orphan*/  PageSetLSN (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  heap_page_prune_execute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ heap_prune_chain (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  log_heap_clean (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pgstat_update_heap_dead_tuples (int /*<<< orphan*/ ,int) ; 

int
heap_page_prune(Relation relation, Buffer buffer, TransactionId OldestXmin,
				bool report_stats, TransactionId *latestRemovedXid)
{
	int			ndeleted = 0;
	Page		page = BufferGetPage(buffer);
	OffsetNumber offnum,
				maxoff;
	PruneState	prstate;

	/*
	 * Our strategy is to scan the page and make lists of items to change,
	 * then apply the changes within a critical section.  This keeps as much
	 * logic as possible out of the critical section, and also ensures that
	 * WAL replay will work the same as the normal case.
	 *
	 * First, initialize the new pd_prune_xid value to zero (indicating no
	 * prunable tuples).  If we find any tuples which may soon become
	 * prunable, we will save the lowest relevant XID in new_prune_xid. Also
	 * initialize the rest of our working state.
	 */
	prstate.new_prune_xid = InvalidTransactionId;
	prstate.latestRemovedXid = *latestRemovedXid;
	prstate.nredirected = prstate.ndead = prstate.nunused = 0;
	memset(prstate.marked, 0, sizeof(prstate.marked));

	/* Scan the page */
	maxoff = PageGetMaxOffsetNumber(page);
	for (offnum = FirstOffsetNumber;
		 offnum <= maxoff;
		 offnum = OffsetNumberNext(offnum))
	{
		ItemId		itemid;

		/* Ignore items already processed as part of an earlier chain */
		if (prstate.marked[offnum])
			continue;

		/* Nothing to do if slot is empty or already dead */
		itemid = PageGetItemId(page, offnum);
		if (!ItemIdIsUsed(itemid) || ItemIdIsDead(itemid))
			continue;

		/* Process this item or chain of items */
		ndeleted += heap_prune_chain(relation, buffer, offnum,
									 OldestXmin,
									 &prstate);
	}

	/* Any error while applying the changes is critical */
	START_CRIT_SECTION();

	/* Have we found any prunable items? */
	if (prstate.nredirected > 0 || prstate.ndead > 0 || prstate.nunused > 0)
	{
		/*
		 * Apply the planned item changes, then repair page fragmentation, and
		 * update the page's hint bit about whether it has free line pointers.
		 */
		heap_page_prune_execute(buffer,
								prstate.redirected, prstate.nredirected,
								prstate.nowdead, prstate.ndead,
								prstate.nowunused, prstate.nunused);

		/*
		 * Update the page's pd_prune_xid field to either zero, or the lowest
		 * XID of any soon-prunable tuple.
		 */
		((PageHeader) page)->pd_prune_xid = prstate.new_prune_xid;

		/*
		 * Also clear the "page is full" flag, since there's no point in
		 * repeating the prune/defrag process until something else happens to
		 * the page.
		 */
		PageClearFull(page);

		MarkBufferDirty(buffer);

		/*
		 * Emit a WAL XLOG_HEAP2_CLEAN record showing what we did
		 */
		if (RelationNeedsWAL(relation))
		{
			XLogRecPtr	recptr;

			recptr = log_heap_clean(relation, buffer,
									prstate.redirected, prstate.nredirected,
									prstate.nowdead, prstate.ndead,
									prstate.nowunused, prstate.nunused,
									prstate.latestRemovedXid);

			PageSetLSN(BufferGetPage(buffer), recptr);
		}
	}
	else
	{
		/*
		 * If we didn't prune anything, but have found a new value for the
		 * pd_prune_xid field, update it and mark the buffer dirty. This is
		 * treated as a non-WAL-logged hint.
		 *
		 * Also clear the "page is full" flag if it is set, since there's no
		 * point in repeating the prune/defrag process until something else
		 * happens to the page.
		 */
		if (((PageHeader) page)->pd_prune_xid != prstate.new_prune_xid ||
			PageIsFull(page))
		{
			((PageHeader) page)->pd_prune_xid = prstate.new_prune_xid;
			PageClearFull(page);
			MarkBufferDirtyHint(buffer, true);
		}
	}

	END_CRIT_SECTION();

	/*
	 * If requested, report the number of tuples reclaimed to pgstats. This is
	 * ndeleted minus ndead, because we don't want to count a now-DEAD root
	 * item as a deletion for this purpose.
	 */
	if (report_stats && ndeleted > prstate.ndead)
		pgstat_update_heap_dead_tuples(relation, ndeleted - prstate.ndead);

	*latestRemovedXid = prstate.latestRemovedXid;

	/*
	 * XXX Should we update the FSM information of this page ?
	 *
	 * There are two schools of thought here. We may not want to update FSM
	 * information so that the page is not used for unrelated UPDATEs/INSERTs
	 * and any free space in this page will remain available for further
	 * UPDATEs in *this* page, thus improving chances for doing HOT updates.
	 *
	 * But for a large table and where a page does not receive further UPDATEs
	 * for a long time, we might waste this space by not updating the FSM
	 * information. The relation may get extended and fragmented further.
	 *
	 * One possibility is to leave "fillfactor" worth of space in this page
	 * and update FSM with the remaining space.
	 */

	return ndeleted;
}