#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sched_dl_entity {scalar_t__ dl_runtime; int /*<<< orphan*/  inactive_timer; scalar_t__ dl_non_contending; } ;
struct dl_rq {int dummy; } ;

/* Variables and functions */
 int ENQUEUE_MIGRATED ; 
 int /*<<< orphan*/  add_rq_bw (struct sched_dl_entity*,struct dl_rq*) ; 
 int /*<<< orphan*/  add_running_bw (struct sched_dl_entity*,struct dl_rq*) ; 
 struct dl_rq* dl_rq_of_se (struct sched_dl_entity*) ; 
 int /*<<< orphan*/  dl_task_of (struct sched_dl_entity*) ; 
 int hrtimer_try_to_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_task_struct (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void task_contending(struct sched_dl_entity *dl_se, int flags)
{
	struct dl_rq *dl_rq = dl_rq_of_se(dl_se);

	/*
	 * If this is a non-deadline task that has been boosted,
	 * do nothing
	 */
	if (dl_se->dl_runtime == 0)
		return;

	if (flags & ENQUEUE_MIGRATED)
		add_rq_bw(dl_se, dl_rq);

	if (dl_se->dl_non_contending) {
		dl_se->dl_non_contending = 0;
		/*
		 * If the timer handler is currently running and the
		 * timer cannot be cancelled, inactive_task_timer()
		 * will see that dl_not_contending is not set, and
		 * will not touch the rq's active utilization,
		 * so we are still safe.
		 */
		if (hrtimer_try_to_cancel(&dl_se->inactive_timer) == 1)
			put_task_struct(dl_task_of(dl_se));
	} else {
		/*
		 * Since "dl_non_contending" is not set, the
		 * task's utilization has already been removed from
		 * active utilization (either when the task blocked,
		 * when the "inactive timer" fired).
		 * So, add it back.
		 */
		add_running_bw(dl_se, dl_rq);
	}
}