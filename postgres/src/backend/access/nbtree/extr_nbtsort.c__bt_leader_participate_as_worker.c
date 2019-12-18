#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  isunique; } ;
struct TYPE_12__ {TYPE_1__* spool; TYPE_3__* btleader; } ;
struct TYPE_11__ {int nparticipanttuplesorts; int /*<<< orphan*/  sharedsort2; int /*<<< orphan*/  sharedsort; TYPE_7__* btshared; } ;
struct TYPE_10__ {int isunique; int /*<<< orphan*/  index; int /*<<< orphan*/  heap; } ;
struct TYPE_9__ {int isunique; int /*<<< orphan*/  index; int /*<<< orphan*/  heap; } ;
typedef  TYPE_2__ BTSpool ;
typedef  TYPE_3__ BTLeader ;
typedef  TYPE_4__ BTBuildState ;

/* Variables and functions */
 int /*<<< orphan*/  ResetUsage () ; 
 int /*<<< orphan*/  ShowUsage (char*) ; 
 int /*<<< orphan*/  _bt_parallel_scan_and_sort (TYPE_2__*,TYPE_2__*,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ log_btree_build_stats ; 
 int maintenance_work_mem ; 
 scalar_t__ palloc0 (int) ; 

__attribute__((used)) static void
_bt_leader_participate_as_worker(BTBuildState *buildstate)
{
	BTLeader   *btleader = buildstate->btleader;
	BTSpool    *leaderworker;
	BTSpool    *leaderworker2;
	int			sortmem;

	/* Allocate memory and initialize private spool */
	leaderworker = (BTSpool *) palloc0(sizeof(BTSpool));
	leaderworker->heap = buildstate->spool->heap;
	leaderworker->index = buildstate->spool->index;
	leaderworker->isunique = buildstate->spool->isunique;

	/* Initialize second spool, if required */
	if (!btleader->btshared->isunique)
		leaderworker2 = NULL;
	else
	{
		/* Allocate memory for worker's own private secondary spool */
		leaderworker2 = (BTSpool *) palloc0(sizeof(BTSpool));

		/* Initialize worker's own secondary spool */
		leaderworker2->heap = leaderworker->heap;
		leaderworker2->index = leaderworker->index;
		leaderworker2->isunique = false;
	}

	/*
	 * Might as well use reliable figure when doling out maintenance_work_mem
	 * (when requested number of workers were not launched, this will be
	 * somewhat higher than it is for other workers).
	 */
	sortmem = maintenance_work_mem / btleader->nparticipanttuplesorts;

	/* Perform work common to all participants */
	_bt_parallel_scan_and_sort(leaderworker, leaderworker2, btleader->btshared,
							   btleader->sharedsort, btleader->sharedsort2,
							   sortmem, true);

#ifdef BTREE_BUILD_STATS
	if (log_btree_build_stats)
	{
		ShowUsage("BTREE BUILD (Leader Partial Spool) STATISTICS");
		ResetUsage();
	}
#endif							/* BTREE_BUILD_STATS */
}