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
struct sched_dl_entity {int /*<<< orphan*/  deadline; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int ENQUEUE_REPLENISH ; 
 int ENQUEUE_RESTORE ; 
 int ENQUEUE_WAKEUP ; 
 int /*<<< orphan*/  __enqueue_dl_entity (struct sched_dl_entity*) ; 
 int /*<<< orphan*/  dl_rq_of_se (struct sched_dl_entity*) ; 
 scalar_t__ dl_time_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_dl_rq (struct sched_dl_entity*) ; 
 int /*<<< orphan*/  replenish_dl_entity (struct sched_dl_entity*,struct sched_dl_entity*) ; 
 int /*<<< orphan*/  rq_clock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rq_of_dl_rq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_new_dl_entity (struct sched_dl_entity*) ; 
 int /*<<< orphan*/  task_contending (struct sched_dl_entity*,int) ; 
 int /*<<< orphan*/  update_dl_entity (struct sched_dl_entity*,struct sched_dl_entity*) ; 

__attribute__((used)) static void
enqueue_dl_entity(struct sched_dl_entity *dl_se,
		  struct sched_dl_entity *pi_se, int flags)
{
	BUG_ON(on_dl_rq(dl_se));

	/*
	 * If this is a wakeup or a new instance, the scheduling
	 * parameters of the task might need updating. Otherwise,
	 * we want a replenishment of its runtime.
	 */
	if (flags & ENQUEUE_WAKEUP) {
		task_contending(dl_se, flags);
		update_dl_entity(dl_se, pi_se);
	} else if (flags & ENQUEUE_REPLENISH) {
		replenish_dl_entity(dl_se, pi_se);
	} else if ((flags & ENQUEUE_RESTORE) &&
		  dl_time_before(dl_se->deadline,
				 rq_clock(rq_of_dl_rq(dl_rq_of_se(dl_se))))) {
		setup_new_dl_entity(dl_se);
	}

	__enqueue_dl_entity(dl_se);
}