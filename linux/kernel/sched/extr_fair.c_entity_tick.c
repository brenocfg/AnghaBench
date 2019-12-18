#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sched_entity {int dummy; } ;
struct cfs_rq {int nr_running; } ;
struct TYPE_3__ {int /*<<< orphan*/  hrtick_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOUBLE_TICK ; 
 int /*<<< orphan*/  UPDATE_TG ; 
 int /*<<< orphan*/  check_preempt_tick (struct cfs_rq*,struct sched_entity*) ; 
 scalar_t__ hrtimer_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resched_curr (TYPE_1__*) ; 
 TYPE_1__* rq_of (struct cfs_rq*) ; 
 int /*<<< orphan*/  sched_feat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_cfs_group (struct sched_entity*) ; 
 int /*<<< orphan*/  update_curr (struct cfs_rq*) ; 
 int /*<<< orphan*/  update_load_avg (struct cfs_rq*,struct sched_entity*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
entity_tick(struct cfs_rq *cfs_rq, struct sched_entity *curr, int queued)
{
	/*
	 * Update run-time statistics of the 'current'.
	 */
	update_curr(cfs_rq);

	/*
	 * Ensure that runnable average is periodically updated.
	 */
	update_load_avg(cfs_rq, curr, UPDATE_TG);
	update_cfs_group(curr);

#ifdef CONFIG_SCHED_HRTICK
	/*
	 * queued ticks are scheduled to match the slice, so don't bother
	 * validating it and just reschedule.
	 */
	if (queued) {
		resched_curr(rq_of(cfs_rq));
		return;
	}
	/*
	 * don't let the period tick interfere with the hrtick preemption
	 */
	if (!sched_feat(DOUBLE_TICK) &&
			hrtimer_active(&rq_of(cfs_rq)->hrtick_timer))
		return;
#endif

	if (cfs_rq->nr_running > 1)
		check_preempt_tick(cfs_rq, curr);
}