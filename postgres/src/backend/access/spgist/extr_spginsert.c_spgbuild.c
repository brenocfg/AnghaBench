#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int isBuild; } ;
struct TYPE_6__ {double heap_tuples; scalar_t__ index_tuples; } ;
struct TYPE_5__ {scalar_t__ indtuples; int /*<<< orphan*/  tmpCtx; TYPE_4__ spgstate; } ;
typedef  TYPE_1__ SpGistBuildState ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  IndexInfo ;
typedef  TYPE_2__ IndexBuildResult ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationGetNumberOfBlocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int SPGIST_LEAF ; 
 scalar_t__ SPGIST_METAPAGE_BLKNO ; 
 int SPGIST_NULLS ; 
 scalar_t__ SPGIST_NULL_BLKNO ; 
 scalar_t__ SPGIST_ROOT_BLKNO ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  SpGistInitBuffer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SpGistInitMetapage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpGistNewBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpGistUpdateMetaPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initSpGistState (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_newpage_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  spgistBuildCallback ; 
 double table_index_build_scan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

IndexBuildResult *
spgbuild(Relation heap, Relation index, IndexInfo *indexInfo)
{
	IndexBuildResult *result;
	double		reltuples;
	SpGistBuildState buildstate;
	Buffer		metabuffer,
				rootbuffer,
				nullbuffer;

	if (RelationGetNumberOfBlocks(index) != 0)
		elog(ERROR, "index \"%s\" already contains data",
			 RelationGetRelationName(index));

	/*
	 * Initialize the meta page and root pages
	 */
	metabuffer = SpGistNewBuffer(index);
	rootbuffer = SpGistNewBuffer(index);
	nullbuffer = SpGistNewBuffer(index);

	Assert(BufferGetBlockNumber(metabuffer) == SPGIST_METAPAGE_BLKNO);
	Assert(BufferGetBlockNumber(rootbuffer) == SPGIST_ROOT_BLKNO);
	Assert(BufferGetBlockNumber(nullbuffer) == SPGIST_NULL_BLKNO);

	START_CRIT_SECTION();

	SpGistInitMetapage(BufferGetPage(metabuffer));
	MarkBufferDirty(metabuffer);
	SpGistInitBuffer(rootbuffer, SPGIST_LEAF);
	MarkBufferDirty(rootbuffer);
	SpGistInitBuffer(nullbuffer, SPGIST_LEAF | SPGIST_NULLS);
	MarkBufferDirty(nullbuffer);


	END_CRIT_SECTION();

	UnlockReleaseBuffer(metabuffer);
	UnlockReleaseBuffer(rootbuffer);
	UnlockReleaseBuffer(nullbuffer);

	/*
	 * Now insert all the heap data into the index
	 */
	initSpGistState(&buildstate.spgstate, index);
	buildstate.spgstate.isBuild = true;
	buildstate.indtuples = 0;

	buildstate.tmpCtx = AllocSetContextCreate(CurrentMemoryContext,
											  "SP-GiST build temporary context",
											  ALLOCSET_DEFAULT_SIZES);

	reltuples = table_index_build_scan(heap, index, indexInfo, true, true,
									   spgistBuildCallback, (void *) &buildstate,
									   NULL);

	MemoryContextDelete(buildstate.tmpCtx);

	SpGistUpdateMetaPage(index);

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

	result = (IndexBuildResult *) palloc0(sizeof(IndexBuildResult));
	result->heap_tuples = reltuples;
	result->index_tuples = buildstate.indtuples;

	return result;
}