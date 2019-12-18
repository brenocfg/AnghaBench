#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  tempCxt; } ;
struct TYPE_22__ {scalar_t__ bufferingMode; int freespace; scalar_t__ indtuples; TYPE_8__* giststate; int /*<<< orphan*/  gfbb; scalar_t__ indtuplesSize; TYPE_1__* heaprel; TYPE_1__* indexrel; } ;
struct TYPE_21__ {scalar_t__ buffering_mode; int fillfactor; } ;
struct TYPE_20__ {double heap_tuples; double index_tuples; } ;
struct TYPE_19__ {scalar_t__ rd_options; } ;
typedef  TYPE_1__* Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  IndexInfo ;
typedef  TYPE_2__ IndexBuildResult ;
typedef  TYPE_3__ GiSTOptions ;
typedef  TYPE_4__ GISTBuildState ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BLCKSZ ; 
 scalar_t__ BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_LEAF ; 
 int /*<<< orphan*/  GISTInitBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GIST_BUFFERING_ACTIVE ; 
 void* GIST_BUFFERING_AUTO ; 
 scalar_t__ GIST_BUFFERING_DISABLED ; 
 scalar_t__ GIST_BUFFERING_STATS ; 
 int GIST_DEFAULT_FILLFACTOR ; 
 scalar_t__ GIST_OPTION_BUFFERING_OFF ; 
 scalar_t__ GIST_OPTION_BUFFERING_ON ; 
 scalar_t__ GIST_ROOT_BLKNO ; 
 int /*<<< orphan*/  GistBuildLSN ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RelationGetNumberOfBlocks (TYPE_1__*) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_1__*) ; 
 scalar_t__ RelationNeedsWAL (TYPE_1__*) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  createTempGistContext () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  freeGISTstate (TYPE_8__*) ; 
 int /*<<< orphan*/  gistBuildCallback ; 
 int /*<<< orphan*/  gistEmptyAllBuffers (TYPE_4__*) ; 
 int /*<<< orphan*/  gistFreeBuildBuffers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gistNewBuffer (TYPE_1__*) ; 
 TYPE_8__* initGISTstate (TYPE_1__*) ; 
 int /*<<< orphan*/  log_newpage_range (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ palloc (int) ; 
 double table_index_build_scan (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

IndexBuildResult *
gistbuild(Relation heap, Relation index, IndexInfo *indexInfo)
{
	IndexBuildResult *result;
	double		reltuples;
	GISTBuildState buildstate;
	Buffer		buffer;
	Page		page;
	MemoryContext oldcxt = CurrentMemoryContext;
	int			fillfactor;

	buildstate.indexrel = index;
	buildstate.heaprel = heap;

	if (index->rd_options)
	{
		/* Get buffering mode from the options string */
		GiSTOptions *options = (GiSTOptions *) index->rd_options;

		if (options->buffering_mode == GIST_OPTION_BUFFERING_ON)
			buildstate.bufferingMode = GIST_BUFFERING_STATS;
		else if (options->buffering_mode == GIST_OPTION_BUFFERING_OFF)
			buildstate.bufferingMode = GIST_BUFFERING_DISABLED;
		else
			buildstate.bufferingMode = GIST_BUFFERING_AUTO;

		fillfactor = options->fillfactor;
	}
	else
	{
		/*
		 * By default, switch to buffering mode when the index grows too large
		 * to fit in cache.
		 */
		buildstate.bufferingMode = GIST_BUFFERING_AUTO;
		fillfactor = GIST_DEFAULT_FILLFACTOR;
	}
	/* Calculate target amount of free space to leave on pages */
	buildstate.freespace = BLCKSZ * (100 - fillfactor) / 100;

	/*
	 * We expect to be called exactly once for any index relation. If that's
	 * not the case, big trouble's what we have.
	 */
	if (RelationGetNumberOfBlocks(index) != 0)
		elog(ERROR, "index \"%s\" already contains data",
			 RelationGetRelationName(index));

	/* no locking is needed */
	buildstate.giststate = initGISTstate(index);

	/*
	 * Create a temporary memory context that is reset once for each tuple
	 * processed.  (Note: we don't bother to make this a child of the
	 * giststate's scanCxt, so we have to delete it separately at the end.)
	 */
	buildstate.giststate->tempCxt = createTempGistContext();

	/* initialize the root page */
	buffer = gistNewBuffer(index);
	Assert(BufferGetBlockNumber(buffer) == GIST_ROOT_BLKNO);
	page = BufferGetPage(buffer);

	START_CRIT_SECTION();

	GISTInitBuffer(buffer, F_LEAF);

	MarkBufferDirty(buffer);
	PageSetLSN(page, GistBuildLSN);

	UnlockReleaseBuffer(buffer);

	END_CRIT_SECTION();

	/* build the index */
	buildstate.indtuples = 0;
	buildstate.indtuplesSize = 0;

	/*
	 * Do the heap scan.
	 */
	reltuples = table_index_build_scan(heap, index, indexInfo, true, true,
									   gistBuildCallback,
									   (void *) &buildstate, NULL);

	/*
	 * If buffering was used, flush out all the tuples that are still in the
	 * buffers.
	 */
	if (buildstate.bufferingMode == GIST_BUFFERING_ACTIVE)
	{
		elog(DEBUG1, "all tuples processed, emptying buffers");
		gistEmptyAllBuffers(&buildstate);
		gistFreeBuildBuffers(buildstate.gfbb);
	}

	/* okay, all heap tuples are indexed */
	MemoryContextSwitchTo(oldcxt);
	MemoryContextDelete(buildstate.giststate->tempCxt);

	freeGISTstate(buildstate.giststate);

	/*
	 * We didn't write WAL records as we built the index, so if WAL-logging is
	 * required, write all pages to the WAL now.
	 */
	if (RelationNeedsWAL(index))
	{
		log_newpage_range(index, MAIN_FORKNUM,
						  0, RelationGetNumberOfBlocks(index),
						  true);
	}

	/*
	 * Return statistics
	 */
	result = (IndexBuildResult *) palloc(sizeof(IndexBuildResult));

	result->heap_tuples = reltuples;
	result->index_tuples = (double) buildstate.indtuples;

	return result;
}