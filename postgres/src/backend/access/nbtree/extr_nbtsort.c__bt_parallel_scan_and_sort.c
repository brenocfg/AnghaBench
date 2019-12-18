#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TableScanDesc ;
struct TYPE_18__ {int havedead; scalar_t__ indtuples; int /*<<< orphan*/ * btleader; TYPE_3__* spool2; TYPE_3__* spool; int /*<<< orphan*/  heap; int /*<<< orphan*/  isunique; } ;
struct TYPE_17__ {double reltuples; int havedead; int brokenhotchain; int /*<<< orphan*/  workersdonecv; int /*<<< orphan*/  mutex; int /*<<< orphan*/  indtuples; int /*<<< orphan*/  nparticipantsdone; int /*<<< orphan*/  isconcurrent; int /*<<< orphan*/  isunique; } ;
struct TYPE_16__ {int isunique; void* sortstate; int /*<<< orphan*/  index; int /*<<< orphan*/  heap; } ;
struct TYPE_15__ {scalar_t__ ii_BrokenHotChain; int /*<<< orphan*/  ii_Concurrent; } ;
struct TYPE_14__ {int isWorker; int nParticipants; int /*<<< orphan*/ * sharedsort; } ;
typedef  int /*<<< orphan*/  SortCoordinateData ;
typedef  TYPE_1__* SortCoordinate ;
typedef  int /*<<< orphan*/  Sharedsort ;
typedef  TYPE_2__ IndexInfo ;
typedef  TYPE_3__ BTSpool ;
typedef  TYPE_4__ BTShared ;
typedef  TYPE_5__ BTBuildState ;

/* Variables and functions */
 TYPE_2__* BuildIndexInfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConditionVariableSignal (int /*<<< orphan*/ *) ; 
 int Min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ParallelTableScanFromBTShared (TYPE_4__*) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _bt_build_callback ; 
 TYPE_1__* palloc0 (int) ; 
 int /*<<< orphan*/  table_beginscan_parallel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double table_index_build_scan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 void* tuplesort_begin_index_btree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  tuplesort_end (void*) ; 
 int /*<<< orphan*/  tuplesort_performsort (void*) ; 
 int /*<<< orphan*/  work_mem ; 

__attribute__((used)) static void
_bt_parallel_scan_and_sort(BTSpool *btspool, BTSpool *btspool2,
						   BTShared *btshared, Sharedsort *sharedsort,
						   Sharedsort *sharedsort2, int sortmem, bool progress)
{
	SortCoordinate coordinate;
	BTBuildState buildstate;
	TableScanDesc scan;
	double		reltuples;
	IndexInfo  *indexInfo;

	/* Initialize local tuplesort coordination state */
	coordinate = palloc0(sizeof(SortCoordinateData));
	coordinate->isWorker = true;
	coordinate->nParticipants = -1;
	coordinate->sharedsort = sharedsort;

	/* Begin "partial" tuplesort */
	btspool->sortstate = tuplesort_begin_index_btree(btspool->heap,
													 btspool->index,
													 btspool->isunique,
													 sortmem, coordinate,
													 false);

	/*
	 * Just as with serial case, there may be a second spool.  If so, a
	 * second, dedicated spool2 partial tuplesort is required.
	 */
	if (btspool2)
	{
		SortCoordinate coordinate2;

		/*
		 * We expect that the second one (for dead tuples) won't get very
		 * full, so we give it only work_mem (unless sortmem is less for
		 * worker).  Worker processes are generally permitted to allocate
		 * work_mem independently.
		 */
		coordinate2 = palloc0(sizeof(SortCoordinateData));
		coordinate2->isWorker = true;
		coordinate2->nParticipants = -1;
		coordinate2->sharedsort = sharedsort2;
		btspool2->sortstate =
			tuplesort_begin_index_btree(btspool->heap, btspool->index, false,
										Min(sortmem, work_mem), coordinate2,
										false);
	}

	/* Fill in buildstate for _bt_build_callback() */
	buildstate.isunique = btshared->isunique;
	buildstate.havedead = false;
	buildstate.heap = btspool->heap;
	buildstate.spool = btspool;
	buildstate.spool2 = btspool2;
	buildstate.indtuples = 0;
	buildstate.btleader = NULL;

	/* Join parallel scan */
	indexInfo = BuildIndexInfo(btspool->index);
	indexInfo->ii_Concurrent = btshared->isconcurrent;
	scan = table_beginscan_parallel(btspool->heap,
									ParallelTableScanFromBTShared(btshared));
	reltuples = table_index_build_scan(btspool->heap, btspool->index, indexInfo,
									   true, progress, _bt_build_callback,
									   (void *) &buildstate, scan);

	/*
	 * Execute this worker's part of the sort.
	 *
	 * Unlike leader and serial cases, we cannot avoid calling
	 * tuplesort_performsort() for spool2 if it ends up containing no dead
	 * tuples (this is disallowed for workers by tuplesort).
	 */
	tuplesort_performsort(btspool->sortstate);
	if (btspool2)
		tuplesort_performsort(btspool2->sortstate);

	/*
	 * Done.  Record ambuild statistics, and whether we encountered a broken
	 * HOT chain.
	 */
	SpinLockAcquire(&btshared->mutex);
	btshared->nparticipantsdone++;
	btshared->reltuples += reltuples;
	if (buildstate.havedead)
		btshared->havedead = true;
	btshared->indtuples += buildstate.indtuples;
	if (indexInfo->ii_BrokenHotChain)
		btshared->brokenhotchain = true;
	SpinLockRelease(&btshared->mutex);

	/* Notify leader */
	ConditionVariableSignal(&btshared->workersdonecv);

	/* We can end tuplesorts immediately */
	tuplesort_end(btspool->sortstate);
	if (btspool2)
		tuplesort_end(btspool2->sortstate);
}