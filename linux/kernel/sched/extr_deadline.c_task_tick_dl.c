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
struct TYPE_2__ {scalar_t__ runtime; } ;
struct task_struct {TYPE_1__ dl; } ;
struct rq {int /*<<< orphan*/  dl; } ;

/* Variables and functions */
 scalar_t__ hrtick_enabled (struct rq*) ; 
 scalar_t__ is_leftmost (struct task_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rq_clock_pelt (struct rq*) ; 
 int /*<<< orphan*/  start_hrtick_dl (struct rq*,struct task_struct*) ; 
 int /*<<< orphan*/  update_curr_dl (struct rq*) ; 
 int /*<<< orphan*/  update_dl_rq_load_avg (int /*<<< orphan*/ ,struct rq*,int) ; 

__attribute__((used)) static void task_tick_dl(struct rq *rq, struct task_struct *p, int queued)
{
	update_curr_dl(rq);

	update_dl_rq_load_avg(rq_clock_pelt(rq), rq, 1);
	/*
	 * Even when we have runtime, update_curr_dl() might have resulted in us
	 * not being the leftmost task anymore. In that case NEED_RESCHED will
	 * be set and schedule() will start a new hrtick for the next task.
	 */
	if (hrtick_enabled(rq) && queued && p->dl.runtime > 0 &&
	    is_leftmost(p, &rq->dl))
		start_hrtick_dl(rq, p);
}