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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  dl_bw; int /*<<< orphan*/  inactive_timer; scalar_t__ dl_non_contending; } ;
struct task_struct {TYPE_1__ dl; } ;
struct rq {int /*<<< orphan*/  dl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int SCHED_FLAG_SUGOV ; 
 int /*<<< orphan*/  __add_rq_bw (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __sub_rq_bw (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hrtimer_try_to_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  sub_running_bw (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ task_on_rq_queued (struct task_struct*) ; 
 struct rq* task_rq (struct task_struct*) ; 

void dl_change_utilization(struct task_struct *p, u64 new_bw)
{
	struct rq *rq;

	BUG_ON(p->dl.flags & SCHED_FLAG_SUGOV);

	if (task_on_rq_queued(p))
		return;

	rq = task_rq(p);
	if (p->dl.dl_non_contending) {
		sub_running_bw(&p->dl, &rq->dl);
		p->dl.dl_non_contending = 0;
		/*
		 * If the timer handler is currently running and the
		 * timer cannot be cancelled, inactive_task_timer()
		 * will see that dl_not_contending is not set, and
		 * will not touch the rq's active utilization,
		 * so we are still safe.
		 */
		if (hrtimer_try_to_cancel(&p->dl.inactive_timer) == 1)
			put_task_struct(p);
	}
	__sub_rq_bw(p->dl.dl_bw, &rq->dl);
	__add_rq_bw(new_bw, &rq->dl);
}