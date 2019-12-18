#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  idxStat ;
struct TYPE_12__ {scalar_t__ nTotalPages; int /*<<< orphan*/  nEntries; int /*<<< orphan*/  nEntryPages; int /*<<< orphan*/  nDataPages; } ;
struct TYPE_11__ {void* num_pages; scalar_t__ pages_free; int /*<<< orphan*/  estimated_count; int /*<<< orphan*/  num_index_tuples; } ;
struct TYPE_10__ {int /*<<< orphan*/  index; int /*<<< orphan*/  strategy; int /*<<< orphan*/  estimated_count; int /*<<< orphan*/  num_heap_tuples; scalar_t__ analyze_only; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Page ;
typedef  TYPE_1__ IndexVacuumInfo ;
typedef  TYPE_2__ IndexBulkDeleteResult ;
typedef  TYPE_3__ GinStatsData ;
typedef  int /*<<< orphan*/  GinState ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 scalar_t__ GIN_ROOT_BLKNO ; 
 int /*<<< orphan*/  GIN_SHARE ; 
 scalar_t__ GinPageIsData (scalar_t__) ; 
 scalar_t__ GinPageIsLeaf (scalar_t__) ; 
 int /*<<< orphan*/  GinPageIsList (scalar_t__) ; 
 scalar_t__ GinPageIsRecyclable (scalar_t__) ; 
 int /*<<< orphan*/  IndexFreeSpaceMapVacuum (int /*<<< orphan*/ ) ; 
 scalar_t__ IsAutoVacuumWorkerProcess () ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockRelationForExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 scalar_t__ PageGetMaxOffsetNumber (scalar_t__) ; 
 int /*<<< orphan*/  RBM_NORMAL ; 
 int /*<<< orphan*/  RELATION_IS_LOCAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadBufferExtended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RecordFreeIndexPage (int /*<<< orphan*/ ,scalar_t__) ; 
 void* RelationGetNumberOfBlocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockRelationForExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ginInsertCleanup (int /*<<< orphan*/ *,int,int,int,TYPE_2__*) ; 
 int /*<<< orphan*/  ginUpdateStats (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  initGinState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  vacuum_delay_point () ; 

IndexBulkDeleteResult *
ginvacuumcleanup(IndexVacuumInfo *info, IndexBulkDeleteResult *stats)
{
	Relation	index = info->index;
	bool		needLock;
	BlockNumber npages,
				blkno;
	BlockNumber totFreePages;
	GinState	ginstate;
	GinStatsData idxStat;

	/*
	 * In an autovacuum analyze, we want to clean up pending insertions.
	 * Otherwise, an ANALYZE-only call is a no-op.
	 */
	if (info->analyze_only)
	{
		if (IsAutoVacuumWorkerProcess())
		{
			initGinState(&ginstate, index);
			ginInsertCleanup(&ginstate, false, true, true, stats);
		}
		return stats;
	}

	/*
	 * Set up all-zero stats and cleanup pending inserts if ginbulkdelete
	 * wasn't called
	 */
	if (stats == NULL)
	{
		stats = (IndexBulkDeleteResult *) palloc0(sizeof(IndexBulkDeleteResult));
		initGinState(&ginstate, index);
		ginInsertCleanup(&ginstate, !IsAutoVacuumWorkerProcess(),
						 false, true, stats);
	}

	memset(&idxStat, 0, sizeof(idxStat));

	/*
	 * XXX we always report the heap tuple count as the number of index
	 * entries.  This is bogus if the index is partial, but it's real hard to
	 * tell how many distinct heap entries are referenced by a GIN index.
	 */
	stats->num_index_tuples = info->num_heap_tuples;
	stats->estimated_count = info->estimated_count;

	/*
	 * Need lock unless it's local to this backend.
	 */
	needLock = !RELATION_IS_LOCAL(index);

	if (needLock)
		LockRelationForExtension(index, ExclusiveLock);
	npages = RelationGetNumberOfBlocks(index);
	if (needLock)
		UnlockRelationForExtension(index, ExclusiveLock);

	totFreePages = 0;

	for (blkno = GIN_ROOT_BLKNO; blkno < npages; blkno++)
	{
		Buffer		buffer;
		Page		page;

		vacuum_delay_point();

		buffer = ReadBufferExtended(index, MAIN_FORKNUM, blkno,
									RBM_NORMAL, info->strategy);
		LockBuffer(buffer, GIN_SHARE);
		page = (Page) BufferGetPage(buffer);

		if (GinPageIsRecyclable(page))
		{
			Assert(blkno != GIN_ROOT_BLKNO);
			RecordFreeIndexPage(index, blkno);
			totFreePages++;
		}
		else if (GinPageIsData(page))
		{
			idxStat.nDataPages++;
		}
		else if (!GinPageIsList(page))
		{
			idxStat.nEntryPages++;

			if (GinPageIsLeaf(page))
				idxStat.nEntries += PageGetMaxOffsetNumber(page);
		}

		UnlockReleaseBuffer(buffer);
	}

	/* Update the metapage with accurate page and entry counts */
	idxStat.nTotalPages = npages;
	ginUpdateStats(info->index, &idxStat, false);

	/* Finally, vacuum the FSM */
	IndexFreeSpaceMapVacuum(info->index);

	stats->pages_free = totFreePages;

	if (needLock)
		LockRelationForExtension(index, ExclusiveLock);
	stats->num_pages = RelationGetNumberOfBlocks(index);
	if (needLock)
		UnlockRelationForExtension(index, ExclusiveLock);

	return stats;
}