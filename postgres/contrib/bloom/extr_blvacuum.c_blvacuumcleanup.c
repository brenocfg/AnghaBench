#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ num_index_tuples; scalar_t__ pages_free; scalar_t__ num_pages; } ;
struct TYPE_6__ {int /*<<< orphan*/  index; int /*<<< orphan*/  strategy; scalar_t__ analyze_only; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Page ;
typedef  TYPE_1__ IndexVacuumInfo ;
typedef  TYPE_2__ IndexBulkDeleteResult ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 scalar_t__ BLOOM_HEAD_BLKNO ; 
 int /*<<< orphan*/  BUFFER_LOCK_SHARE ; 
 scalar_t__ BloomPageGetMaxOffset (scalar_t__) ; 
 scalar_t__ BloomPageIsDeleted (scalar_t__) ; 
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IndexFreeSpaceMapVacuum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 scalar_t__ PageIsNew (scalar_t__) ; 
 int /*<<< orphan*/  RBM_NORMAL ; 
 int /*<<< orphan*/  ReadBufferExtended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RecordFreeIndexPage (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ RelationGetNumberOfBlocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  vacuum_delay_point () ; 

IndexBulkDeleteResult *
blvacuumcleanup(IndexVacuumInfo *info, IndexBulkDeleteResult *stats)
{
	Relation	index = info->index;
	BlockNumber npages,
				blkno;

	if (info->analyze_only)
		return stats;

	if (stats == NULL)
		stats = (IndexBulkDeleteResult *) palloc0(sizeof(IndexBulkDeleteResult));

	/*
	 * Iterate over the pages: insert deleted pages into FSM and collect
	 * statistics.
	 */
	npages = RelationGetNumberOfBlocks(index);
	stats->num_pages = npages;
	stats->pages_free = 0;
	stats->num_index_tuples = 0;
	for (blkno = BLOOM_HEAD_BLKNO; blkno < npages; blkno++)
	{
		Buffer		buffer;
		Page		page;

		vacuum_delay_point();

		buffer = ReadBufferExtended(index, MAIN_FORKNUM, blkno,
									RBM_NORMAL, info->strategy);
		LockBuffer(buffer, BUFFER_LOCK_SHARE);
		page = (Page) BufferGetPage(buffer);

		if (PageIsNew(page) || BloomPageIsDeleted(page))
		{
			RecordFreeIndexPage(index, blkno);
			stats->pages_free++;
		}
		else
		{
			stats->num_index_tuples += BloomPageGetMaxOffset(page);
		}

		UnlockReleaseBuffer(buffer);
	}

	IndexFreeSpaceMapVacuum(info->index);

	return stats;
}