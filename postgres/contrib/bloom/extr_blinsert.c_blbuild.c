#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buildstate ;
struct TYPE_8__ {scalar_t__ count; int /*<<< orphan*/  indtuples; int /*<<< orphan*/  tmpCtx; int /*<<< orphan*/  blstate; } ;
struct TYPE_7__ {double heap_tuples; int /*<<< orphan*/  index_tuples; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  IndexInfo ;
typedef  TYPE_1__ IndexBuildResult ;
typedef  TYPE_2__ BloomBuildState ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BloomInitMetapage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationGetNumberOfBlocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bloomBuildCallback ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flushCachedPage (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  initBloomState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initCachedPage (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ palloc (int) ; 
 double table_index_build_scan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

IndexBuildResult *
blbuild(Relation heap, Relation index, IndexInfo *indexInfo)
{
	IndexBuildResult *result;
	double		reltuples;
	BloomBuildState buildstate;

	if (RelationGetNumberOfBlocks(index) != 0)
		elog(ERROR, "index \"%s\" already contains data",
			 RelationGetRelationName(index));

	/* Initialize the meta page */
	BloomInitMetapage(index);

	/* Initialize the bloom build state */
	memset(&buildstate, 0, sizeof(buildstate));
	initBloomState(&buildstate.blstate, index);
	buildstate.tmpCtx = AllocSetContextCreate(CurrentMemoryContext,
											  "Bloom build temporary context",
											  ALLOCSET_DEFAULT_SIZES);
	initCachedPage(&buildstate);

	/* Do the heap scan */
	reltuples = table_index_build_scan(heap, index, indexInfo, true, true,
									   bloomBuildCallback, (void *) &buildstate,
									   NULL);

	/* Flush last page if needed (it will be, unless heap was empty) */
	if (buildstate.count > 0)
		flushCachedPage(index, &buildstate);

	MemoryContextDelete(buildstate.tmpCtx);

	result = (IndexBuildResult *) palloc(sizeof(IndexBuildResult));
	result->heap_tuples = reltuples;
	result->index_tuples = buildstate.indtuples;

	return result;
}