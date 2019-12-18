#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  tempCxt; } ;
struct TYPE_20__ {scalar_t__ bufferingMode; int indtuples; TYPE_1__* gfbb; TYPE_7__* giststate; int /*<<< orphan*/  indtuplesSize; int /*<<< orphan*/  heaprel; int /*<<< orphan*/  freespace; } ;
struct TYPE_19__ {int /*<<< orphan*/  t_tid; } ;
struct TYPE_18__ {int /*<<< orphan*/  rd_smgr; } ;
struct TYPE_17__ {int /*<<< orphan*/  levelStep; int /*<<< orphan*/  pagesPerBuffer; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  TYPE_3__* IndexTuple ;
typedef  TYPE_4__ GISTBuildState ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int BUFFERING_MODE_SWITCH_CHECK_STEP ; 
 int BUFFERING_MODE_TUPLE_SIZE_STATS_TARGET ; 
 scalar_t__ GIST_BUFFERING_ACTIVE ; 
 scalar_t__ GIST_BUFFERING_AUTO ; 
 scalar_t__ GIST_BUFFERING_STATS ; 
 scalar_t__ IndexTupleSize (TYPE_3__*) ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calculatePagesPerBuffer (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ effective_cache_size ; 
 int /*<<< orphan*/  gistBufferingBuildInsert (TYPE_4__*,TYPE_3__*) ; 
 TYPE_3__* gistFormTuple (TYPE_7__*,TYPE_2__*,int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  gistInitBuffering (TYPE_4__*) ; 
 int /*<<< orphan*/  gistdoinsert (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ smgrnblocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gistBuildCallback(Relation index,
				  ItemPointer tid,
				  Datum *values,
				  bool *isnull,
				  bool tupleIsAlive,
				  void *state)
{
	GISTBuildState *buildstate = (GISTBuildState *) state;
	IndexTuple	itup;
	MemoryContext oldCtx;

	oldCtx = MemoryContextSwitchTo(buildstate->giststate->tempCxt);

	/* form an index tuple and point it at the heap tuple */
	itup = gistFormTuple(buildstate->giststate, index, values, isnull, true);
	itup->t_tid = *tid;

	if (buildstate->bufferingMode == GIST_BUFFERING_ACTIVE)
	{
		/* We have buffers, so use them. */
		gistBufferingBuildInsert(buildstate, itup);
	}
	else
	{
		/*
		 * There's no buffers (yet). Since we already have the index relation
		 * locked, we call gistdoinsert directly.
		 */
		gistdoinsert(index, itup, buildstate->freespace,
					 buildstate->giststate, buildstate->heaprel, true);
	}

	/* Update tuple count and total size. */
	buildstate->indtuples += 1;
	buildstate->indtuplesSize += IndexTupleSize(itup);

	MemoryContextSwitchTo(oldCtx);
	MemoryContextReset(buildstate->giststate->tempCxt);

	if (buildstate->bufferingMode == GIST_BUFFERING_ACTIVE &&
		buildstate->indtuples % BUFFERING_MODE_TUPLE_SIZE_STATS_TARGET == 0)
	{
		/* Adjust the target buffer size now */
		buildstate->gfbb->pagesPerBuffer =
			calculatePagesPerBuffer(buildstate, buildstate->gfbb->levelStep);
	}

	/*
	 * In 'auto' mode, check if the index has grown too large to fit in cache,
	 * and switch to buffering mode if it has.
	 *
	 * To avoid excessive calls to smgrnblocks(), only check this every
	 * BUFFERING_MODE_SWITCH_CHECK_STEP index tuples
	 */
	if ((buildstate->bufferingMode == GIST_BUFFERING_AUTO &&
		 buildstate->indtuples % BUFFERING_MODE_SWITCH_CHECK_STEP == 0 &&
		 effective_cache_size < smgrnblocks(index->rd_smgr, MAIN_FORKNUM)) ||
		(buildstate->bufferingMode == GIST_BUFFERING_STATS &&
		 buildstate->indtuples >= BUFFERING_MODE_TUPLE_SIZE_STATS_TARGET))
	{
		/*
		 * Index doesn't fit in effective cache anymore. Try to switch to
		 * buffering build mode.
		 */
		gistInitBuffering(buildstate);
	}
}