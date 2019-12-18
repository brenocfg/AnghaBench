#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_9__ {scalar_t__ lastBlockVacuumed; scalar_t__ lastBlockLocked; scalar_t__ totFreePages; int /*<<< orphan*/  oldestBtpoXact; int /*<<< orphan*/  pagedelcontext; int /*<<< orphan*/  cycleid; void* callback_state; int /*<<< orphan*/  callback; TYPE_2__* stats; TYPE_1__* info; } ;
struct TYPE_8__ {int estimated_count; scalar_t__ pages_free; scalar_t__ num_pages; scalar_t__ pages_deleted; scalar_t__ num_index_tuples; } ;
struct TYPE_7__ {int /*<<< orphan*/  strategy; scalar_t__ report_progress; int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ IndexVacuumInfo ;
typedef  TYPE_2__ IndexBulkDeleteResult ;
typedef  int /*<<< orphan*/  IndexBulkDeleteCallback ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;
typedef  TYPE_3__ BTVacState ;
typedef  int /*<<< orphan*/  BTCycleId ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ BTREE_METAPAGE ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 int /*<<< orphan*/  IndexFreeSpaceMapVacuum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 int /*<<< orphan*/  LockBufferForCleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockRelationForExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROGRESS_SCAN_BLOCKS_DONE ; 
 int /*<<< orphan*/  PROGRESS_SCAN_BLOCKS_TOTAL ; 
 int /*<<< orphan*/  RBM_NORMAL ; 
 int /*<<< orphan*/  RELATION_IS_LOCAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadBufferExtended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RelationGetNumberOfBlocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockRelationForExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XLogStandbyInfoActive () ; 
 int /*<<< orphan*/  _bt_checkpage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_delitems_vacuum (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  _bt_relbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btvacuumpage (TYPE_3__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pgstat_progress_update_param (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
btvacuumscan(IndexVacuumInfo *info, IndexBulkDeleteResult *stats,
			 IndexBulkDeleteCallback callback, void *callback_state,
			 BTCycleId cycleid, TransactionId *oldestBtpoXact)
{
	Relation	rel = info->index;
	BTVacState	vstate;
	BlockNumber num_pages;
	BlockNumber blkno;
	bool		needLock;

	/*
	 * Reset counts that will be incremented during the scan; needed in case
	 * of multiple scans during a single VACUUM command
	 */
	stats->estimated_count = false;
	stats->num_index_tuples = 0;
	stats->pages_deleted = 0;

	/* Set up info to pass down to btvacuumpage */
	vstate.info = info;
	vstate.stats = stats;
	vstate.callback = callback;
	vstate.callback_state = callback_state;
	vstate.cycleid = cycleid;
	vstate.lastBlockVacuumed = BTREE_METAPAGE;	/* Initialise at first block */
	vstate.lastBlockLocked = BTREE_METAPAGE;
	vstate.totFreePages = 0;
	vstate.oldestBtpoXact = InvalidTransactionId;

	/* Create a temporary memory context to run _bt_pagedel in */
	vstate.pagedelcontext = AllocSetContextCreate(CurrentMemoryContext,
												  "_bt_pagedel",
												  ALLOCSET_DEFAULT_SIZES);

	/*
	 * The outer loop iterates over all index pages except the metapage, in
	 * physical order (we hope the kernel will cooperate in providing
	 * read-ahead for speed).  It is critical that we visit all leaf pages,
	 * including ones added after we start the scan, else we might fail to
	 * delete some deletable tuples.  Hence, we must repeatedly check the
	 * relation length.  We must acquire the relation-extension lock while
	 * doing so to avoid a race condition: if someone else is extending the
	 * relation, there is a window where bufmgr/smgr have created a new
	 * all-zero page but it hasn't yet been write-locked by _bt_getbuf(). If
	 * we manage to scan such a page here, we'll improperly assume it can be
	 * recycled.  Taking the lock synchronizes things enough to prevent a
	 * problem: either num_pages won't include the new page, or _bt_getbuf
	 * already has write lock on the buffer and it will be fully initialized
	 * before we can examine it.  (See also vacuumlazy.c, which has the same
	 * issue.)	Also, we need not worry if a page is added immediately after
	 * we look; the page splitting code already has write-lock on the left
	 * page before it adds a right page, so we must already have processed any
	 * tuples due to be moved into such a page.
	 *
	 * We can skip locking for new or temp relations, however, since no one
	 * else could be accessing them.
	 */
	needLock = !RELATION_IS_LOCAL(rel);

	blkno = BTREE_METAPAGE + 1;
	for (;;)
	{
		/* Get the current relation length */
		if (needLock)
			LockRelationForExtension(rel, ExclusiveLock);
		num_pages = RelationGetNumberOfBlocks(rel);
		if (needLock)
			UnlockRelationForExtension(rel, ExclusiveLock);

		if (info->report_progress)
			pgstat_progress_update_param(PROGRESS_SCAN_BLOCKS_TOTAL,
										 num_pages);

		/* Quit if we've scanned the whole relation */
		if (blkno >= num_pages)
			break;
		/* Iterate over pages, then loop back to recheck length */
		for (; blkno < num_pages; blkno++)
		{
			btvacuumpage(&vstate, blkno, blkno);
			if (info->report_progress)
				pgstat_progress_update_param(PROGRESS_SCAN_BLOCKS_DONE,
											 blkno);
		}
	}

	/*
	 * Check to see if we need to issue one final WAL record for this index,
	 * which may be needed for correctness on a hot standby node when non-MVCC
	 * index scans could take place.
	 *
	 * If the WAL is replayed in hot standby, the replay process needs to get
	 * cleanup locks on all index leaf pages, just as we've been doing here.
	 * However, we won't issue any WAL records about pages that have no items
	 * to be deleted.  For pages between pages we've vacuumed, the replay code
	 * will take locks under the direction of the lastBlockVacuumed fields in
	 * the XLOG_BTREE_VACUUM WAL records.  To cover pages after the last one
	 * we vacuum, we need to issue a dummy XLOG_BTREE_VACUUM WAL record
	 * against the last leaf page in the index, if that one wasn't vacuumed.
	 */
	if (XLogStandbyInfoActive() &&
		vstate.lastBlockVacuumed < vstate.lastBlockLocked)
	{
		Buffer		buf;

		/*
		 * The page should be valid, but we can't use _bt_getbuf() because we
		 * want to use a nondefault buffer access strategy.  Since we aren't
		 * going to delete any items, getting cleanup lock again is probably
		 * overkill, but for consistency do that anyway.
		 */
		buf = ReadBufferExtended(rel, MAIN_FORKNUM, vstate.lastBlockLocked,
								 RBM_NORMAL, info->strategy);
		LockBufferForCleanup(buf);
		_bt_checkpage(rel, buf);
		_bt_delitems_vacuum(rel, buf, NULL, 0, vstate.lastBlockVacuumed);
		_bt_relbuf(rel, buf);
	}

	MemoryContextDelete(vstate.pagedelcontext);

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
	if (vstate.totFreePages > 0)
		IndexFreeSpaceMapVacuum(rel);

	/* update statistics */
	stats->num_pages = num_pages;
	stats->pages_free = vstate.totFreePages;

	if (oldestBtpoXact)
		*oldestBtpoXact = vstate.oldestBtpoXact;
}