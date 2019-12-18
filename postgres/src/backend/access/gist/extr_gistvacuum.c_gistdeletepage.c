#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_7__ {int /*<<< orphan*/  pages_deleted; } ;
struct TYPE_10__ {TYPE_1__ stats; } ;
struct TYPE_9__ {int /*<<< orphan*/  t_tid; } ;
struct TYPE_8__ {int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  TYPE_2__ IndexVacuumInfo ;
typedef  TYPE_3__* IndexTuple ;
typedef  TYPE_4__ GistBulkDeleteResult ;
typedef  int /*<<< orphan*/  FullTransactionId ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 scalar_t__ FirstOffsetNumber ; 
 scalar_t__ GistFollowRight (int /*<<< orphan*/ ) ; 
 scalar_t__ GistPageIsDeleted (int /*<<< orphan*/ ) ; 
 scalar_t__ GistPageIsLeaf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GistPageSetDeleted (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidOffsetNumber ; 
 scalar_t__ ItemPointerGetBlockNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageIndexTupleDelete (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageIsNew (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadNextFullTransactionId () ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  gistGetFakeLSN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gistXLogPageDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool
gistdeletepage(IndexVacuumInfo *info, GistBulkDeleteResult *stats,
			   Buffer parentBuffer, OffsetNumber downlink,
			   Buffer leafBuffer)
{
	Page		parentPage = BufferGetPage(parentBuffer);
	Page		leafPage = BufferGetPage(leafBuffer);
	ItemId		iid;
	IndexTuple	idxtuple;
	XLogRecPtr	recptr;
	FullTransactionId txid;

	/*
	 * Check that the leaf is still empty and deletable.
	 */
	if (!GistPageIsLeaf(leafPage))
	{
		/* a leaf page should never become a non-leaf page */
		Assert(false);
		return false;
	}

	if (GistFollowRight(leafPage))
		return false;			/* don't mess with a concurrent page split */

	if (PageGetMaxOffsetNumber(leafPage) != InvalidOffsetNumber)
		return false;			/* not empty anymore */

	/*
	 * Ok, the leaf is deletable.  Is the downlink in the parent page still
	 * valid?  It might have been moved by a concurrent insert.  We could try
	 * to re-find it by scanning the page again, possibly moving right if the
	 * was split.  But for now, let's keep it simple and just give up.  The
	 * next VACUUM will pick it up.
	 */
	if (PageIsNew(parentPage) || GistPageIsDeleted(parentPage) ||
		GistPageIsLeaf(parentPage))
	{
		/* shouldn't happen, internal pages are never deleted */
		Assert(false);
		return false;
	}

	if (PageGetMaxOffsetNumber(parentPage) < downlink
		|| PageGetMaxOffsetNumber(parentPage) <= FirstOffsetNumber)
		return false;

	iid = PageGetItemId(parentPage, downlink);
	idxtuple = (IndexTuple) PageGetItem(parentPage, iid);
	if (BufferGetBlockNumber(leafBuffer) !=
		ItemPointerGetBlockNumber(&(idxtuple->t_tid)))
		return false;

	/*
	 * All good, proceed with the deletion.
	 *
	 * The page cannot be immediately recycled, because in-progress scans that
	 * saw the downlink might still visit it.  Mark the page with the current
	 * next-XID counter, so that we know when it can be recycled.  Once that
	 * XID becomes older than GlobalXmin, we know that all scans that are
	 * currently in progress must have ended.  (That's much more conservative
	 * than needed, but let's keep it safe and simple.)
	 */
	txid = ReadNextFullTransactionId();

	START_CRIT_SECTION();

	/* mark the page as deleted */
	MarkBufferDirty(leafBuffer);
	GistPageSetDeleted(leafPage, txid);
	stats->stats.pages_deleted++;

	/* remove the downlink from the parent */
	MarkBufferDirty(parentBuffer);
	PageIndexTupleDelete(parentPage, downlink);

	if (RelationNeedsWAL(info->index))
		recptr = gistXLogPageDelete(leafBuffer, txid, parentBuffer, downlink);
	else
		recptr = gistGetFakeLSN(info->index);
	PageSetLSN(parentPage, recptr);
	PageSetLSN(leafPage, recptr);

	END_CRIT_SECTION();

	return true;
}