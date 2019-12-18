#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ dl_non_contending; scalar_t__ dl_runtime; } ;
struct task_struct {TYPE_1__ dl; } ;
struct TYPE_6__ {scalar_t__ dl_nr_running; } ;
struct rq {TYPE_2__ dl; } ;

/* Variables and functions */
 int /*<<< orphan*/  deadline_queue_pull_task (struct rq*) ; 
 int /*<<< orphan*/  sub_rq_bw (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  sub_running_bw (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  task_non_contending (struct task_struct*) ; 
 scalar_t__ task_on_rq_queued (struct task_struct*) ; 

__attribute__((used)) static void switched_from_dl(struct rq *rq, struct task_struct *p)
{
	/*
	 * task_non_contending() can start the "inactive timer" (if the 0-lag
	 * time is in the future). If the task switches back to dl before
	 * the "inactive timer" fires, it can continue to consume its current
	 * runtime using its current deadline. If it stays outside of
	 * SCHED_DEADLINE until the 0-lag time passes, inactive_task_timer()
	 * will reset the task parameters.
	 */
	if (task_on_rq_queued(p) && p->dl.dl_runtime)
		task_non_contending(p);

	if (!task_on_rq_queued(p)) {
		/*
		 * Inactive timer is armed. However, p is leaving DEADLINE and
		 * might migrate away from this rq while continuing to run on
		 * some other class. We need to remove its contribution from
		 * this rq running_bw now, or sub_rq_bw (below) will complain.
		 */
		if (p->dl.dl_non_contending)
			sub_running_bw(&p->dl, &rq->dl);
		sub_rq_bw(&p->dl, &rq->dl);
	}

	/*
	 * We cannot use inactive_task_timer() to invoke sub_running_bw()
	 * at the 0-lag time, because the task could have been migrated
	 * while SCHED_OTHER in the meanwhile.
	 */
	if (p->dl.dl_non_contending)
		p->dl.dl_non_contending = 0;

	/*
	 * Since this might be the only -deadline task on the rq,
	 * this is the right place to try to pull some other one
	 * from an overloaded CPU, if any.
	 */
	if (!task_on_rq_queued(p) || rq->dl.dl_nr_running)
		return;

	deadline_queue_pull_task(rq);
}