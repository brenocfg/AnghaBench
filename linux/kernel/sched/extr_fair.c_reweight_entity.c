#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int period_contrib; int load_sum; int runnable_load_sum; void* runnable_load_avg; void* load_avg; } ;
struct sched_entity {unsigned long runnable_weight; scalar_t__ on_rq; TYPE_1__ avg; int /*<<< orphan*/  load; } ;
struct cfs_rq {struct sched_entity* curr; } ;

/* Variables and functions */
 int LOAD_AVG_MAX ; 
 int /*<<< orphan*/  account_entity_dequeue (struct cfs_rq*,struct sched_entity*) ; 
 int /*<<< orphan*/  account_entity_enqueue (struct cfs_rq*,struct sched_entity*) ; 
 int /*<<< orphan*/  dequeue_load_avg (struct cfs_rq*,struct sched_entity*) ; 
 int /*<<< orphan*/  dequeue_runnable_load_avg (struct cfs_rq*,struct sched_entity*) ; 
 void* div_u64 (int,int) ; 
 int /*<<< orphan*/  enqueue_load_avg (struct cfs_rq*,struct sched_entity*) ; 
 int /*<<< orphan*/  enqueue_runnable_load_avg (struct cfs_rq*,struct sched_entity*) ; 
 int se_runnable (struct sched_entity*) ; 
 int se_weight (struct sched_entity*) ; 
 int /*<<< orphan*/  update_curr (struct cfs_rq*) ; 
 int /*<<< orphan*/  update_load_set (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void reweight_entity(struct cfs_rq *cfs_rq, struct sched_entity *se,
			    unsigned long weight, unsigned long runnable)
{
	if (se->on_rq) {
		/* commit outstanding execution time */
		if (cfs_rq->curr == se)
			update_curr(cfs_rq);
		account_entity_dequeue(cfs_rq, se);
		dequeue_runnable_load_avg(cfs_rq, se);
	}
	dequeue_load_avg(cfs_rq, se);

	se->runnable_weight = runnable;
	update_load_set(&se->load, weight);

#ifdef CONFIG_SMP
	do {
		u32 divider = LOAD_AVG_MAX - 1024 + se->avg.period_contrib;

		se->avg.load_avg = div_u64(se_weight(se) * se->avg.load_sum, divider);
		se->avg.runnable_load_avg =
			div_u64(se_runnable(se) * se->avg.runnable_load_sum, divider);
	} while (0);
#endif

	enqueue_load_avg(cfs_rq, se);
	if (se->on_rq) {
		account_entity_enqueue(cfs_rq, se);
		enqueue_runnable_load_avg(cfs_rq, se);
	}
}