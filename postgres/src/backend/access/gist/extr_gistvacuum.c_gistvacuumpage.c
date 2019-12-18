#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_15__ {scalar_t__ rightlink; } ;
struct TYPE_10__ {int tuples_removed; int num_index_tuples; int /*<<< orphan*/  pages_deleted; int /*<<< orphan*/  pages_free; } ;
struct TYPE_14__ {int /*<<< orphan*/  internal_page_set; TYPE_1__ stats; int /*<<< orphan*/  empty_leaf_set; } ;
struct TYPE_13__ {scalar_t__ startNSN; void* callback_state; scalar_t__ (* callback ) (int /*<<< orphan*/ *,void*) ;TYPE_2__* info; TYPE_5__* stats; } ;
struct TYPE_12__ {int /*<<< orphan*/  t_tid; } ;
struct TYPE_11__ {int /*<<< orphan*/  strategy; int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  TYPE_2__ IndexVacuumInfo ;
typedef  TYPE_3__* IndexTuple ;
typedef  scalar_t__ (* IndexBulkDeleteCallback ) (int /*<<< orphan*/ *,void*) ;
typedef  TYPE_4__ GistVacState ;
typedef  TYPE_5__ GistBulkDeleteResult ;
typedef  TYPE_6__* GISTPageOpaque ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 scalar_t__ FirstOffsetNumber ; 
 int /*<<< orphan*/  GIST_EXCLUSIVE ; 
 scalar_t__ GistFollowRight (scalar_t__) ; 
 int /*<<< orphan*/  GistMarkTuplesDeleted (scalar_t__) ; 
 scalar_t__ GistPageGetNSN (scalar_t__) ; 
 TYPE_6__* GistPageGetOpaque (scalar_t__) ; 
 scalar_t__ GistPageIsDeleted (scalar_t__) ; 
 scalar_t__ GistPageIsLeaf (scalar_t__) ; 
 scalar_t__ GistTupleIsInvalid (TYPE_3__*) ; 
 scalar_t__ InvalidBlockNumber ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int MaxOffsetNumber ; 
 scalar_t__ OffsetNumberNext (scalar_t__) ; 
 int /*<<< orphan*/  PageGetItem (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (scalar_t__,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (scalar_t__) ; 
 int /*<<< orphan*/  PageIndexMultiDelete (scalar_t__,scalar_t__*,int) ; 
 int /*<<< orphan*/  PageSetLSN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RBM_NORMAL ; 
 int /*<<< orphan*/  ReadBufferExtended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RecordFreeIndexPage (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gistGetFakeLSN (int /*<<< orphan*/ ) ; 
 scalar_t__ gistPageRecyclable (scalar_t__) ; 
 int /*<<< orphan*/  gistXLogUpdate (int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intset_add_member (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vacuum_delay_point () ; 

__attribute__((used)) static void
gistvacuumpage(GistVacState *vstate, BlockNumber blkno, BlockNumber orig_blkno)
{
	GistBulkDeleteResult *stats = vstate->stats;
	IndexVacuumInfo *info = vstate->info;
	IndexBulkDeleteCallback callback = vstate->callback;
	void	   *callback_state = vstate->callback_state;
	Relation	rel = info->index;
	Buffer		buffer;
	Page		page;
	BlockNumber recurse_to;

restart:
	recurse_to = InvalidBlockNumber;

	/* call vacuum_delay_point while not holding any buffer lock */
	vacuum_delay_point();

	buffer = ReadBufferExtended(rel, MAIN_FORKNUM, blkno, RBM_NORMAL,
								info->strategy);

	/*
	 * We are not going to stay here for a long time, aggressively grab an
	 * exclusive lock.
	 */
	LockBuffer(buffer, GIST_EXCLUSIVE);
	page = (Page) BufferGetPage(buffer);

	if (gistPageRecyclable(page))
	{
		/* Okay to recycle this page */
		RecordFreeIndexPage(rel, blkno);
		stats->stats.pages_free++;
		stats->stats.pages_deleted++;
	}
	else if (GistPageIsDeleted(page))
	{
		/* Already deleted, but can't recycle yet */
		stats->stats.pages_deleted++;
	}
	else if (GistPageIsLeaf(page))
	{
		OffsetNumber todelete[MaxOffsetNumber];
		int			ntodelete = 0;
		int			nremain;
		GISTPageOpaque opaque = GistPageGetOpaque(page);
		OffsetNumber maxoff = PageGetMaxOffsetNumber(page);

		/*
		 * Check whether we need to recurse back to earlier pages.  What we
		 * are concerned about is a page split that happened since we started
		 * the vacuum scan.  If the split moved some tuples to a lower page
		 * then we might have missed 'em.  If so, set up for tail recursion.
		 *
		 * This is similar to the checks we do during searches, when following
		 * a downlink, but we don't need to jump to higher-numbered pages,
		 * because we will process them later, anyway.
		 */
		if ((GistFollowRight(page) ||
			 vstate->startNSN < GistPageGetNSN(page)) &&
			(opaque->rightlink != InvalidBlockNumber) &&
			(opaque->rightlink < orig_blkno))
		{
			recurse_to = opaque->rightlink;
		}

		/*
		 * Scan over all items to see which ones need to be deleted according
		 * to the callback function.
		 */
		if (callback)
		{
			OffsetNumber off;

			for (off = FirstOffsetNumber;
				 off <= maxoff;
				 off = OffsetNumberNext(off))
			{
				ItemId		iid = PageGetItemId(page, off);
				IndexTuple	idxtuple = (IndexTuple) PageGetItem(page, iid);

				if (callback(&(idxtuple->t_tid), callback_state))
					todelete[ntodelete++] = off;
			}
		}

		/*
		 * Apply any needed deletes.  We issue just one WAL record per page,
		 * so as to minimize WAL traffic.
		 */
		if (ntodelete > 0)
		{
			START_CRIT_SECTION();

			MarkBufferDirty(buffer);

			PageIndexMultiDelete(page, todelete, ntodelete);
			GistMarkTuplesDeleted(page);

			if (RelationNeedsWAL(rel))
			{
				XLogRecPtr	recptr;

				recptr = gistXLogUpdate(buffer,
										todelete, ntodelete,
										NULL, 0, InvalidBuffer);
				PageSetLSN(page, recptr);
			}
			else
				PageSetLSN(page, gistGetFakeLSN(rel));

			END_CRIT_SECTION();

			stats->stats.tuples_removed += ntodelete;
			/* must recompute maxoff */
			maxoff = PageGetMaxOffsetNumber(page);
		}

		nremain = maxoff - FirstOffsetNumber + 1;
		if (nremain == 0)
		{
			/*
			 * The page is now completely empty.  Remember its block number,
			 * so that we will try to delete the page in the second stage.
			 *
			 * Skip this when recursing, because IntegerSet requires that the
			 * values are added in ascending order.  The next VACUUM will pick
			 * it up.
			 */
			if (blkno == orig_blkno)
				intset_add_member(stats->empty_leaf_set, blkno);
		}
		else
			stats->stats.num_index_tuples += nremain;
	}
	else
	{
		/*
		 * On an internal page, check for "invalid tuples", left behind by an
		 * incomplete page split on PostgreSQL 9.0 or below.  These are not
		 * created by newer PostgreSQL versions, but unfortunately, there is
		 * no version number anywhere in a GiST index, so we don't know
		 * whether this index might still contain invalid tuples or not.
		 */
		OffsetNumber maxoff = PageGetMaxOffsetNumber(page);
		OffsetNumber off;

		for (off = FirstOffsetNumber;
			 off <= maxoff;
			 off = OffsetNumberNext(off))
		{
			ItemId		iid = PageGetItemId(page, off);
			IndexTuple	idxtuple = (IndexTuple) PageGetItem(page, iid);

			if (GistTupleIsInvalid(idxtuple))
				ereport(LOG,
						(errmsg("index \"%s\" contains an inner tuple marked as invalid",
								RelationGetRelationName(rel)),
						 errdetail("This is caused by an incomplete page split at crash recovery before upgrading to PostgreSQL 9.1."),
						 errhint("Please REINDEX it.")));
		}

		/*
		 * Remember the block number of this page, so that we can revisit it
		 * later in gistvacuum_delete_empty_pages(), when we search for
		 * parents of empty leaf pages.
		 */
		if (blkno == orig_blkno)
			intset_add_member(stats->internal_page_set, blkno);
	}

	UnlockReleaseBuffer(buffer);

	/*
	 * This is really tail recursion, but if the compiler is too stupid to
	 * optimize it as such, we'd eat an uncomfortably large amount of stack
	 * space per recursion level (due to the deletable[] array).  A failure is
	 * improbable since the number of levels isn't likely to be large ... but
	 * just in case, let's hand-optimize into a loop.
	 */
	if (recurse_to != InvalidBlockNumber)
	{
		blkno = recurse_to;
		goto restart;
	}
}