#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
struct TYPE_9__ {int pages_removed; } ;
struct TYPE_12__ {TYPE_1__ stats; int /*<<< orphan*/  empty_leaf_set; int /*<<< orphan*/  internal_page_set; } ;
struct TYPE_11__ {int /*<<< orphan*/  t_tid; } ;
struct TYPE_10__ {int /*<<< orphan*/  strategy; int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Page ;
typedef  int OffsetNumber ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  TYPE_2__ IndexVacuumInfo ;
typedef  TYPE_3__* IndexTuple ;
typedef  TYPE_4__ GistBulkDeleteResult ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ FirstOffsetNumber ; 
 int /*<<< orphan*/  GIST_EXCLUSIVE ; 
 int /*<<< orphan*/  GIST_SHARE ; 
 int /*<<< orphan*/  GIST_UNLOCK ; 
 scalar_t__ GistPageIsDeleted (scalar_t__) ; 
 scalar_t__ GistPageIsLeaf (scalar_t__) ; 
 scalar_t__ ItemPointerGetBlockNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 int MaxOffsetNumber ; 
 int OffsetNumberNext (int) ; 
 int /*<<< orphan*/  PageGetItem (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (scalar_t__,int) ; 
 scalar_t__ PageGetMaxOffsetNumber (scalar_t__) ; 
 scalar_t__ PageIsNew (scalar_t__) ; 
 int /*<<< orphan*/  RBM_NORMAL ; 
 int /*<<< orphan*/  ReadBufferExtended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gistcheckpage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gistdeletepage (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intset_begin_iterate (int /*<<< orphan*/ ) ; 
 scalar_t__ intset_is_member (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ intset_iterate_next (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ intset_num_entries (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gistvacuum_delete_empty_pages(IndexVacuumInfo *info, GistBulkDeleteResult *stats)
{
	Relation	rel = info->index;
	BlockNumber empty_pages_remaining;
	uint64		blkno;

	/*
	 * Rescan all inner pages to find those that have empty child pages.
	 */
	empty_pages_remaining = intset_num_entries(stats->empty_leaf_set);
	intset_begin_iterate(stats->internal_page_set);
	while (empty_pages_remaining > 0 &&
		   intset_iterate_next(stats->internal_page_set, &blkno))
	{
		Buffer		buffer;
		Page		page;
		OffsetNumber off,
					maxoff;
		OffsetNumber todelete[MaxOffsetNumber];
		BlockNumber leafs_to_delete[MaxOffsetNumber];
		int			ntodelete;
		int			deleted;

		buffer = ReadBufferExtended(rel, MAIN_FORKNUM, (BlockNumber) blkno,
									RBM_NORMAL, info->strategy);

		LockBuffer(buffer, GIST_SHARE);
		page = (Page) BufferGetPage(buffer);

		if (PageIsNew(page) || GistPageIsDeleted(page) || GistPageIsLeaf(page))
		{
			/*
			 * This page was an internal page earlier, but now it's something
			 * else. Shouldn't happen...
			 */
			Assert(false);
			UnlockReleaseBuffer(buffer);
			continue;
		}

		/*
		 * Scan all the downlinks, and see if any of them point to empty leaf
		 * pages.
		 */
		maxoff = PageGetMaxOffsetNumber(page);
		ntodelete = 0;
		for (off = FirstOffsetNumber;
			 off <= maxoff && ntodelete < maxoff - 1;
			 off = OffsetNumberNext(off))
		{
			ItemId		iid = PageGetItemId(page, off);
			IndexTuple	idxtuple = (IndexTuple) PageGetItem(page, iid);
			BlockNumber leafblk;

			leafblk = ItemPointerGetBlockNumber(&(idxtuple->t_tid));
			if (intset_is_member(stats->empty_leaf_set, leafblk))
			{
				leafs_to_delete[ntodelete] = leafblk;
				todelete[ntodelete++] = off;
			}
		}

		/*
		 * In order to avoid deadlock, child page must be locked before
		 * parent, so we must release the lock on the parent, lock the child,
		 * and then re-acquire the lock the parent.  (And we wouldn't want to
		 * do I/O, while holding a lock, anyway.)
		 *
		 * At the instant that we're not holding a lock on the parent, the
		 * downlink might get moved by a concurrent insert, so we must
		 * re-check that it still points to the same child page after we have
		 * acquired both locks.  Also, another backend might have inserted a
		 * tuple to the page, so that it is no longer empty.  gistdeletepage()
		 * re-checks all these conditions.
		 */
		LockBuffer(buffer, GIST_UNLOCK);

		deleted = 0;
		for (int i = 0; i < ntodelete; i++)
		{
			Buffer		leafbuf;

			/*
			 * Don't remove the last downlink from the parent.  That would
			 * confuse the insertion code.
			 */
			if (PageGetMaxOffsetNumber(page) == FirstOffsetNumber)
				break;

			leafbuf = ReadBufferExtended(rel, MAIN_FORKNUM, leafs_to_delete[i],
										 RBM_NORMAL, info->strategy);
			LockBuffer(leafbuf, GIST_EXCLUSIVE);
			gistcheckpage(rel, leafbuf);

			LockBuffer(buffer, GIST_EXCLUSIVE);
			if (gistdeletepage(info, stats,
							   buffer, todelete[i] - deleted,
							   leafbuf))
				deleted++;
			LockBuffer(buffer, GIST_UNLOCK);

			UnlockReleaseBuffer(leafbuf);
		}

		ReleaseBuffer(buffer);

		/* update stats */
		stats->stats.pages_removed += deleted;

		/*
		 * We can stop the scan as soon as we have seen the downlinks, even if
		 * we were not able to remove them all.
		 */
		empty_pages_remaining -= ntodelete;
	}
}