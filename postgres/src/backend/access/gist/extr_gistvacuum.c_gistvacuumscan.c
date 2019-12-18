#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int estimated_count; scalar_t__ pages_free; scalar_t__ num_pages; scalar_t__ pages_deleted; scalar_t__ num_index_tuples; } ;
struct TYPE_11__ {TYPE_1__ stats; void* empty_leaf_set; void* internal_page_set; int /*<<< orphan*/  page_set_context; } ;
struct TYPE_10__ {int /*<<< orphan*/  startNSN; void* callback_state; int /*<<< orphan*/  callback; TYPE_4__* stats; TYPE_2__* info; } ;
struct TYPE_9__ {int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_2__ IndexVacuumInfo ;
typedef  int /*<<< orphan*/  IndexBulkDeleteCallback ;
typedef  TYPE_3__ GistVacState ;
typedef  TYPE_4__ GistBulkDeleteResult ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ExclusiveLock ; 
 scalar_t__ GIST_ROOT_BLKNO ; 
 int /*<<< orphan*/  GetInsertRecPtr () ; 
 int /*<<< orphan*/  IndexFreeSpaceMapVacuum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockRelationForExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELATION_IS_LOCAL (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationGetNumberOfBlocks (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockRelationForExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gistGetFakeLSN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gistvacuumpage (TYPE_3__*,scalar_t__,scalar_t__) ; 
 void* intset_create () ; 

__attribute__((used)) static void
gistvacuumscan(IndexVacuumInfo *info, GistBulkDeleteResult *stats,
			   IndexBulkDeleteCallback callback, void *callback_state)
{
	Relation	rel = info->index;
	GistVacState vstate;
	BlockNumber num_pages;
	bool		needLock;
	BlockNumber blkno;
	MemoryContext oldctx;

	/*
	 * Reset counts that will be incremented during the scan; needed in case
	 * of multiple scans during a single VACUUM command.
	 */
	stats->stats.estimated_count = false;
	stats->stats.num_index_tuples = 0;
	stats->stats.pages_deleted = 0;
	stats->stats.pages_free = 0;
	MemoryContextReset(stats->page_set_context);

	/*
	 * Create the integer sets to remember all the internal and the empty leaf
	 * pages in page_set_context.  Internally, the integer set will remember
	 * this context so that the subsequent allocations for these integer sets
	 * will be done from the same context.
	 */
	oldctx = MemoryContextSwitchTo(stats->page_set_context);
	stats->internal_page_set = intset_create();
	stats->empty_leaf_set = intset_create();
	MemoryContextSwitchTo(oldctx);

	/* Set up info to pass down to gistvacuumpage */
	vstate.info = info;
	vstate.stats = stats;
	vstate.callback = callback;
	vstate.callback_state = callback_state;
	if (RelationNeedsWAL(rel))
		vstate.startNSN = GetInsertRecPtr();
	else
		vstate.startNSN = gistGetFakeLSN(rel);

	/*
	 * The outer loop iterates over all index pages, in physical order (we
	 * hope the kernel will cooperate in providing read-ahead for speed).  It
	 * is critical that we visit all leaf pages, including ones added after we
	 * start the scan, else we might fail to delete some deletable tuples.
	 * Hence, we must repeatedly check the relation length.  We must acquire
	 * the relation-extension lock while doing so to avoid a race condition:
	 * if someone else is extending the relation, there is a window where
	 * bufmgr/smgr have created a new all-zero page but it hasn't yet been
	 * write-locked by gistNewBuffer().  If we manage to scan such a page
	 * here, we'll improperly assume it can be recycled.  Taking the lock
	 * synchronizes things enough to prevent a problem: either num_pages won't
	 * include the new page, or gistNewBuffer already has write lock on the
	 * buffer and it will be fully initialized before we can examine it.  (See
	 * also vacuumlazy.c, which has the same issue.)  Also, we need not worry
	 * if a page is added immediately after we look; the page splitting code
	 * already has write-lock on the left page before it adds a right page, so
	 * we must already have processed any tuples due to be moved into such a
	 * page.
	 *
	 * We can skip locking for new or temp relations, however, since no one
	 * else could be accessing them.
	 */
	needLock = !RELATION_IS_LOCAL(rel);

	blkno = GIST_ROOT_BLKNO;
	for (;;)
	{
		/* Get the current relation length */
		if (needLock)
			LockRelationForExtension(rel, ExclusiveLock);
		num_pages = RelationGetNumberOfBlocks(rel);
		if (needLock)
			UnlockRelationForExtension(rel, ExclusiveLock);

		/* Quit if we've scanned the whole relation */
		if (blkno >= num_pages)
			break;
		/* Iterate over pages, then loop back to recheck length */
		for (; blkno < num_pages; blkno++)
			gistvacuumpage(&vstate, blkno, blkno);
	}

	/*
	 * If we found any recyclable pages (and recorded them in the FSM), then
	 * forcibly update the upper-level FSM pages to ensure that searchers can
	 * find them.  It's possible that the pages were also found during
	 * previous scans and so this is a waste of time, but it's cheap enough
	 * relative to scanning the index that it shouldn't matter much, and
	 * making sure that free pages are available sooner not later seems
	 * worthwhile.
	 *
	 * Note that if no recyclable pages exist, we don't bother vacuuming the
	 * FSM at all.
	 */
	if (stats->stats.pages_free > 0)
		IndexFreeSpaceMapVacuum(rel);

	/* update statistics */
	stats->stats.num_pages = num_pages;
}