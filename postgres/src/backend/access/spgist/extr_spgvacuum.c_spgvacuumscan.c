#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ lastFilledBlock; TYPE_2__* stats; int /*<<< orphan*/ * pendingList; int /*<<< orphan*/  myXmin; int /*<<< orphan*/  spgstate; TYPE_1__* info; } ;
typedef  TYPE_3__ spgBulkDeleteState ;
struct TYPE_11__ {int /*<<< orphan*/  xmin; } ;
struct TYPE_9__ {int estimated_count; scalar_t__ pages_deleted; scalar_t__ pages_free; scalar_t__ num_pages; int /*<<< orphan*/  pages_removed; scalar_t__ num_index_tuples; } ;
struct TYPE_8__ {int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ExclusiveLock ; 
 TYPE_7__* GetActiveSnapshot () ; 
 int /*<<< orphan*/  IndexFreeSpaceMapVacuum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockRelationForExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELATION_IS_LOCAL (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationGetNumberOfBlocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationTruncate (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ SPGIST_LAST_FIXED_BLKNO ; 
 scalar_t__ SPGIST_METAPAGE_BLKNO ; 
 int /*<<< orphan*/  SpGistUpdateMetaPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockRelationForExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initSpGistState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spgprocesspending (TYPE_3__*) ; 
 int /*<<< orphan*/  spgvacuumpage (TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static void
spgvacuumscan(spgBulkDeleteState *bds)
{
	Relation	index = bds->info->index;
	bool		needLock;
	BlockNumber num_pages,
				blkno;

	/* Finish setting up spgBulkDeleteState */
	initSpGistState(&bds->spgstate, index);
	bds->pendingList = NULL;
	bds->myXmin = GetActiveSnapshot()->xmin;
	bds->lastFilledBlock = SPGIST_LAST_FIXED_BLKNO;

	/*
	 * Reset counts that will be incremented during the scan; needed in case
	 * of multiple scans during a single VACUUM command
	 */
	bds->stats->estimated_count = false;
	bds->stats->num_index_tuples = 0;
	bds->stats->pages_deleted = 0;

	/* We can skip locking for new or temp relations */
	needLock = !RELATION_IS_LOCAL(index);

	/*
	 * The outer loop iterates over all index pages except the metapage, in
	 * physical order (we hope the kernel will cooperate in providing
	 * read-ahead for speed).  It is critical that we visit all leaf pages,
	 * including ones added after we start the scan, else we might fail to
	 * delete some deletable tuples.  See more extensive comments about this
	 * in btvacuumscan().
	 */
	blkno = SPGIST_METAPAGE_BLKNO + 1;
	for (;;)
	{
		/* Get the current relation length */
		if (needLock)
			LockRelationForExtension(index, ExclusiveLock);
		num_pages = RelationGetNumberOfBlocks(index);
		if (needLock)
			UnlockRelationForExtension(index, ExclusiveLock);

		/* Quit if we've scanned the whole relation */
		if (blkno >= num_pages)
			break;
		/* Iterate over pages, then loop back to recheck length */
		for (; blkno < num_pages; blkno++)
		{
			spgvacuumpage(bds, blkno);
			/* empty the pending-list after each page */
			if (bds->pendingList != NULL)
				spgprocesspending(bds);
		}
	}

	/* Propagate local lastUsedPages cache to metablock */
	SpGistUpdateMetaPage(index);

	/*
	 * If we found any empty pages (and recorded them in the FSM), then
	 * forcibly update the upper-level FSM pages to ensure that searchers can
	 * find them.  It's possible that the pages were also found during
	 * previous scans and so this is a waste of time, but it's cheap enough
	 * relative to scanning the index that it shouldn't matter much, and
	 * making sure that free pages are available sooner not later seems
	 * worthwhile.
	 *
	 * Note that if no empty pages exist, we don't bother vacuuming the FSM at
	 * all.
	 */
	if (bds->stats->pages_deleted > 0)
		IndexFreeSpaceMapVacuum(index);

	/*
	 * Truncate index if possible
	 *
	 * XXX disabled because it's unsafe due to possible concurrent inserts.
	 * We'd have to rescan the pages to make sure they're still empty, and it
	 * doesn't seem worth it.  Note that btree doesn't do this either.
	 *
	 * Another reason not to truncate is that it could invalidate the cached
	 * pages-with-freespace pointers in the metapage and other backends'
	 * relation caches, that is leave them pointing to nonexistent pages.
	 * Adding RelationGetNumberOfBlocks calls to protect the places that use
	 * those pointers would be unduly expensive.
	 */
#ifdef NOT_USED
	if (num_pages > bds->lastFilledBlock + 1)
	{
		BlockNumber lastBlock = num_pages - 1;

		num_pages = bds->lastFilledBlock + 1;
		RelationTruncate(index, num_pages);
		bds->stats->pages_removed += lastBlock - bds->lastFilledBlock;
		bds->stats->pages_deleted -= lastBlock - bds->lastFilledBlock;
	}
#endif

	/* Report final stats */
	bds->stats->num_pages = num_pages;
	bds->stats->pages_free = bds->stats->pages_deleted;
}