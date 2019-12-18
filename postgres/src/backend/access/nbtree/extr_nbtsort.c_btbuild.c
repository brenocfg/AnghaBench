#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int havedead; scalar_t__ indtuples; int /*<<< orphan*/ * btleader; int /*<<< orphan*/ * spool2; int /*<<< orphan*/ * spool; int /*<<< orphan*/  heap; int /*<<< orphan*/  isunique; } ;
struct TYPE_9__ {double heap_tuples; scalar_t__ index_tuples; } ;
struct TYPE_8__ {int /*<<< orphan*/  ii_Unique; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ IndexInfo ;
typedef  TYPE_2__ IndexBuildResult ;
typedef  TYPE_3__ BTBuildState ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ RelationGetNumberOfBlocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResetUsage () ; 
 int /*<<< orphan*/  ShowUsage (char*) ; 
 int /*<<< orphan*/  _bt_end_parallel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _bt_leafbuild (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _bt_spooldestroy (int /*<<< orphan*/ *) ; 
 double _bt_spools_heapscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ log_btree_build_stats ; 
 scalar_t__ palloc (int) ; 

IndexBuildResult *
btbuild(Relation heap, Relation index, IndexInfo *indexInfo)
{
	IndexBuildResult *result;
	BTBuildState buildstate;
	double		reltuples;

#ifdef BTREE_BUILD_STATS
	if (log_btree_build_stats)
		ResetUsage();
#endif							/* BTREE_BUILD_STATS */

	buildstate.isunique = indexInfo->ii_Unique;
	buildstate.havedead = false;
	buildstate.heap = heap;
	buildstate.spool = NULL;
	buildstate.spool2 = NULL;
	buildstate.indtuples = 0;
	buildstate.btleader = NULL;

	/*
	 * We expect to be called exactly once for any index relation. If that's
	 * not the case, big trouble's what we have.
	 */
	if (RelationGetNumberOfBlocks(index) != 0)
		elog(ERROR, "index \"%s\" already contains data",
			 RelationGetRelationName(index));

	reltuples = _bt_spools_heapscan(heap, index, &buildstate, indexInfo);

	/*
	 * Finish the build by (1) completing the sort of the spool file, (2)
	 * inserting the sorted tuples into btree pages and (3) building the upper
	 * levels.  Finally, it may also be necessary to end use of parallelism.
	 */
	_bt_leafbuild(buildstate.spool, buildstate.spool2);
	_bt_spooldestroy(buildstate.spool);
	if (buildstate.spool2)
		_bt_spooldestroy(buildstate.spool2);
	if (buildstate.btleader)
		_bt_end_parallel(buildstate.btleader);

	result = (IndexBuildResult *) palloc(sizeof(IndexBuildResult));

	result->heap_tuples = reltuples;
	result->index_tuples = buildstate.indtuples;

#ifdef BTREE_BUILD_STATS
	if (log_btree_build_stats)
	{
		ShowUsage("BTREE BUILD STATS");
		ResetUsage();
	}
#endif							/* BTREE_BUILD_STATS */

	return result;
}