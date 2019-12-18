#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_17__ {int isunique; TYPE_4__* spool2; int /*<<< orphan*/  havedead; int /*<<< orphan*/  const indtuples; TYPE_1__* btleader; TYPE_4__* spool; } ;
struct TYPE_16__ {int isunique; void* sortstate; void* index; void* heap; } ;
struct TYPE_15__ {int ii_Unique; scalar_t__ ii_ParallelWorkers; int /*<<< orphan*/  ii_BrokenHotChain; int /*<<< orphan*/  ii_Concurrent; } ;
struct TYPE_14__ {int isWorker; int /*<<< orphan*/  sharedsort; int /*<<< orphan*/  nParticipants; } ;
struct TYPE_13__ {int /*<<< orphan*/  sharedsort2; int /*<<< orphan*/  nparticipanttuplesorts; int /*<<< orphan*/  sharedsort; } ;
typedef  int /*<<< orphan*/  SortCoordinateData ;
typedef  TYPE_2__* SortCoordinate ;
typedef  void* Relation ;
typedef  TYPE_3__ IndexInfo ;
typedef  TYPE_4__ BTSpool ;
typedef  TYPE_5__ BTBuildState ;

/* Variables and functions */
 int /*<<< orphan*/  PROGRESS_BTREE_PHASE_INDEXBUILD_TABLESCAN ; 
 int /*<<< orphan*/  PROGRESS_CREATEIDX_SUBPHASE ; 
 int const PROGRESS_CREATEIDX_TUPLES_TOTAL ; 
 int const PROGRESS_SCAN_BLOCKS_DONE ; 
 int const PROGRESS_SCAN_BLOCKS_TOTAL ; 
 int /*<<< orphan*/  _bt_begin_parallel (TYPE_5__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  _bt_build_callback ; 
 double _bt_parallel_heapscan (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _bt_spooldestroy (TYPE_4__*) ; 
 int /*<<< orphan*/  maintenance_work_mem ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  pgstat_progress_update_multi_param (int,int const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pgstat_progress_update_param (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double table_index_build_scan (void*,void*,TYPE_3__*,int,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 void* tuplesort_begin_index_btree (void*,void*,int,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  work_mem ; 

__attribute__((used)) static double
_bt_spools_heapscan(Relation heap, Relation index, BTBuildState *buildstate,
					IndexInfo *indexInfo)
{
	BTSpool    *btspool = (BTSpool *) palloc0(sizeof(BTSpool));
	SortCoordinate coordinate = NULL;
	double		reltuples = 0;

	/*
	 * We size the sort area as maintenance_work_mem rather than work_mem to
	 * speed index creation.  This should be OK since a single backend can't
	 * run multiple index creations in parallel (see also: notes on
	 * parallelism and maintenance_work_mem below).
	 */
	btspool->heap = heap;
	btspool->index = index;
	btspool->isunique = indexInfo->ii_Unique;

	/* Save as primary spool */
	buildstate->spool = btspool;

	/* Report table scan phase started */
	pgstat_progress_update_param(PROGRESS_CREATEIDX_SUBPHASE,
								 PROGRESS_BTREE_PHASE_INDEXBUILD_TABLESCAN);

	/* Attempt to launch parallel worker scan when required */
	if (indexInfo->ii_ParallelWorkers > 0)
		_bt_begin_parallel(buildstate, indexInfo->ii_Concurrent,
						   indexInfo->ii_ParallelWorkers);

	/*
	 * If parallel build requested and at least one worker process was
	 * successfully launched, set up coordination state
	 */
	if (buildstate->btleader)
	{
		coordinate = (SortCoordinate) palloc0(sizeof(SortCoordinateData));
		coordinate->isWorker = false;
		coordinate->nParticipants =
			buildstate->btleader->nparticipanttuplesorts;
		coordinate->sharedsort = buildstate->btleader->sharedsort;
	}

	/*
	 * Begin serial/leader tuplesort.
	 *
	 * In cases where parallelism is involved, the leader receives the same
	 * share of maintenance_work_mem as a serial sort (it is generally treated
	 * in the same way as a serial sort once we return).  Parallel worker
	 * Tuplesortstates will have received only a fraction of
	 * maintenance_work_mem, though.
	 *
	 * We rely on the lifetime of the Leader Tuplesortstate almost not
	 * overlapping with any worker Tuplesortstate's lifetime.  There may be
	 * some small overlap, but that's okay because we rely on leader
	 * Tuplesortstate only allocating a small, fixed amount of memory here.
	 * When its tuplesort_performsort() is called (by our caller), and
	 * significant amounts of memory are likely to be used, all workers must
	 * have already freed almost all memory held by their Tuplesortstates
	 * (they are about to go away completely, too).  The overall effect is
	 * that maintenance_work_mem always represents an absolute high watermark
	 * on the amount of memory used by a CREATE INDEX operation, regardless of
	 * the use of parallelism or any other factor.
	 */
	buildstate->spool->sortstate =
		tuplesort_begin_index_btree(heap, index, buildstate->isunique,
									maintenance_work_mem, coordinate,
									false);

	/*
	 * If building a unique index, put dead tuples in a second spool to keep
	 * them out of the uniqueness check.  We expect that the second spool (for
	 * dead tuples) won't get very full, so we give it only work_mem.
	 */
	if (indexInfo->ii_Unique)
	{
		BTSpool    *btspool2 = (BTSpool *) palloc0(sizeof(BTSpool));
		SortCoordinate coordinate2 = NULL;

		/* Initialize secondary spool */
		btspool2->heap = heap;
		btspool2->index = index;
		btspool2->isunique = false;
		/* Save as secondary spool */
		buildstate->spool2 = btspool2;

		if (buildstate->btleader)
		{
			/*
			 * Set up non-private state that is passed to
			 * tuplesort_begin_index_btree() about the basic high level
			 * coordination of a parallel sort.
			 */
			coordinate2 = (SortCoordinate) palloc0(sizeof(SortCoordinateData));
			coordinate2->isWorker = false;
			coordinate2->nParticipants =
				buildstate->btleader->nparticipanttuplesorts;
			coordinate2->sharedsort = buildstate->btleader->sharedsort2;
		}

		/*
		 * We expect that the second one (for dead tuples) won't get very
		 * full, so we give it only work_mem
		 */
		buildstate->spool2->sortstate =
			tuplesort_begin_index_btree(heap, index, false, work_mem,
										coordinate2, false);
	}

	/* Fill spool using either serial or parallel heap scan */
	if (!buildstate->btleader)
		reltuples = table_index_build_scan(heap, index, indexInfo, true, true,
										   _bt_build_callback, (void *) buildstate,
										   NULL);
	else
		reltuples = _bt_parallel_heapscan(buildstate,
										  &indexInfo->ii_BrokenHotChain);

	/*
	 * Set the progress target for the next phase.  Reset the block number
	 * values set by table_index_build_scan
	 */
	{
		const int	index[] = {
			PROGRESS_CREATEIDX_TUPLES_TOTAL,
			PROGRESS_SCAN_BLOCKS_TOTAL,
			PROGRESS_SCAN_BLOCKS_DONE
		};
		const int64 val[] = {
			buildstate->indtuples,
			0, 0
		};

		pgstat_progress_update_multi_param(3, index, val);
	}

	/* okay, all heap tuples are spooled */
	if (buildstate->spool2 && !buildstate->havedead)
	{
		/* spool2 turns out to be unnecessary */
		_bt_spooldestroy(buildstate->spool2);
		buildstate->spool2 = NULL;
	}

	return reltuples;
}