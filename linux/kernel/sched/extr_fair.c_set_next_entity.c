#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_9__ {int /*<<< orphan*/  slice_max; } ;
struct TYPE_8__ {int weight; } ;
struct sched_entity {scalar_t__ sum_exec_runtime; scalar_t__ prev_sum_exec_runtime; TYPE_4__ statistics; TYPE_3__ load; scalar_t__ on_rq; } ;
struct cfs_rq {struct sched_entity* curr; } ;
struct TYPE_6__ {int weight; } ;
struct TYPE_7__ {TYPE_1__ load; } ;
struct TYPE_10__ {TYPE_2__ cfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  UPDATE_TG ; 
 int /*<<< orphan*/  __dequeue_entity (struct cfs_rq*,struct sched_entity*) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_5__* rq_of (struct cfs_rq*) ; 
 scalar_t__ schedstat_enabled () ; 
 int /*<<< orphan*/  schedstat_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ schedstat_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_load_avg (struct cfs_rq*,struct sched_entity*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_stats_curr_start (struct cfs_rq*,struct sched_entity*) ; 
 int /*<<< orphan*/  update_stats_wait_end (struct cfs_rq*,struct sched_entity*) ; 

__attribute__((used)) static void
set_next_entity(struct cfs_rq *cfs_rq, struct sched_entity *se)
{
	/* 'current' is not kept within the tree. */
	if (se->on_rq) {
		/*
		 * Any task has to be enqueued before it get to execute on
		 * a CPU. So account for the time it spent waiting on the
		 * runqueue.
		 */
		update_stats_wait_end(cfs_rq, se);
		__dequeue_entity(cfs_rq, se);
		update_load_avg(cfs_rq, se, UPDATE_TG);
	}

	update_stats_curr_start(cfs_rq, se);
	cfs_rq->curr = se;

	/*
	 * Track our maximum slice length, if the CPU's load is at
	 * least twice that of our own weight (i.e. dont track it
	 * when there are only lesser-weight tasks around):
	 */
	if (schedstat_enabled() &&
	    rq_of(cfs_rq)->cfs.load.weight >= 2*se->load.weight) {
		schedstat_set(se->statistics.slice_max,
			max((u64)schedstat_val(se->statistics.slice_max),
			    se->sum_exec_runtime - se->prev_sum_exec_runtime));
	}

	se->prev_sum_exec_runtime = se->sum_exec_runtime;
}