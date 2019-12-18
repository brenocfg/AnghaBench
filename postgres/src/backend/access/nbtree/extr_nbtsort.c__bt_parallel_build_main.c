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
typedef  int /*<<< orphan*/  shm_toc ;
typedef  int /*<<< orphan*/  dsm_segment ;
struct TYPE_7__ {int isunique; int scantuplesortstates; int /*<<< orphan*/  indexrelid; int /*<<< orphan*/  heaprelid; int /*<<< orphan*/  isconcurrent; } ;
struct TYPE_6__ {int isunique; void* index; void* heap; } ;
typedef  int /*<<< orphan*/  Sharedsort ;
typedef  void* Relation ;
typedef  int /*<<< orphan*/  LOCKMODE ;
typedef  TYPE_1__ BTSpool ;
typedef  TYPE_2__ BTShared ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  PARALLEL_KEY_BTREE_SHARED ; 
 int /*<<< orphan*/  PARALLEL_KEY_QUERY_TEXT ; 
 int /*<<< orphan*/  PARALLEL_KEY_TUPLESORT ; 
 int /*<<< orphan*/  PARALLEL_KEY_TUPLESORT_SPOOL2 ; 
 int /*<<< orphan*/  ResetUsage () ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  STATE_RUNNING ; 
 int /*<<< orphan*/  ShareLock ; 
 int /*<<< orphan*/  ShareUpdateExclusiveLock ; 
 int /*<<< orphan*/  ShowUsage (char*) ; 
 int /*<<< orphan*/  _bt_parallel_scan_and_sort (TYPE_1__*,TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 char* debug_query_string ; 
 int /*<<< orphan*/  index_close (void*,int /*<<< orphan*/ ) ; 
 void* index_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ log_btree_build_stats ; 
 int maintenance_work_mem ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  pgstat_report_activity (int /*<<< orphan*/ ,char*) ; 
 void* shm_toc_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  table_close (void*,int /*<<< orphan*/ ) ; 
 void* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplesort_attach_shared (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
_bt_parallel_build_main(dsm_segment *seg, shm_toc *toc)
{
	char	   *sharedquery;
	BTSpool    *btspool;
	BTSpool    *btspool2;
	BTShared   *btshared;
	Sharedsort *sharedsort;
	Sharedsort *sharedsort2;
	Relation	heapRel;
	Relation	indexRel;
	LOCKMODE	heapLockmode;
	LOCKMODE	indexLockmode;
	int			sortmem;

#ifdef BTREE_BUILD_STATS
	if (log_btree_build_stats)
		ResetUsage();
#endif							/* BTREE_BUILD_STATS */

	/* Set debug_query_string for individual workers first */
	sharedquery = shm_toc_lookup(toc, PARALLEL_KEY_QUERY_TEXT, false);
	debug_query_string = sharedquery;

	/* Report the query string from leader */
	pgstat_report_activity(STATE_RUNNING, debug_query_string);

	/* Look up nbtree shared state */
	btshared = shm_toc_lookup(toc, PARALLEL_KEY_BTREE_SHARED, false);

	/* Open relations using lock modes known to be obtained by index.c */
	if (!btshared->isconcurrent)
	{
		heapLockmode = ShareLock;
		indexLockmode = AccessExclusiveLock;
	}
	else
	{
		heapLockmode = ShareUpdateExclusiveLock;
		indexLockmode = RowExclusiveLock;
	}

	/* Open relations within worker */
	heapRel = table_open(btshared->heaprelid, heapLockmode);
	indexRel = index_open(btshared->indexrelid, indexLockmode);

	/* Initialize worker's own spool */
	btspool = (BTSpool *) palloc0(sizeof(BTSpool));
	btspool->heap = heapRel;
	btspool->index = indexRel;
	btspool->isunique = btshared->isunique;

	/* Look up shared state private to tuplesort.c */
	sharedsort = shm_toc_lookup(toc, PARALLEL_KEY_TUPLESORT, false);
	tuplesort_attach_shared(sharedsort, seg);
	if (!btshared->isunique)
	{
		btspool2 = NULL;
		sharedsort2 = NULL;
	}
	else
	{
		/* Allocate memory for worker's own private secondary spool */
		btspool2 = (BTSpool *) palloc0(sizeof(BTSpool));

		/* Initialize worker's own secondary spool */
		btspool2->heap = btspool->heap;
		btspool2->index = btspool->index;
		btspool2->isunique = false;
		/* Look up shared state private to tuplesort.c */
		sharedsort2 = shm_toc_lookup(toc, PARALLEL_KEY_TUPLESORT_SPOOL2, false);
		tuplesort_attach_shared(sharedsort2, seg);
	}

	/* Perform sorting of spool, and possibly a spool2 */
	sortmem = maintenance_work_mem / btshared->scantuplesortstates;
	_bt_parallel_scan_and_sort(btspool, btspool2, btshared, sharedsort,
							   sharedsort2, sortmem, false);

#ifdef BTREE_BUILD_STATS
	if (log_btree_build_stats)
	{
		ShowUsage("BTREE BUILD (Worker Partial Spool) STATISTICS");
		ResetUsage();
	}
#endif							/* BTREE_BUILD_STATS */

	index_close(indexRel, indexLockmode);
	table_close(heapRel, heapLockmode);
}