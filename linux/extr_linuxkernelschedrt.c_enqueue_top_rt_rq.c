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
struct rt_rq {int rt_queued; int /*<<< orphan*/  rt_nr_running; } ;
struct rq {struct rt_rq rt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  add_nr_running (struct rq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpufreq_update_util (struct rq*,int /*<<< orphan*/ ) ; 
 struct rq* rq_of_rt_rq (struct rt_rq*) ; 
 scalar_t__ rt_rq_throttled (struct rt_rq*) ; 

__attribute__((used)) static void
enqueue_top_rt_rq(struct rt_rq *rt_rq)
{
	struct rq *rq = rq_of_rt_rq(rt_rq);

	BUG_ON(&rq->rt != rt_rq);

	if (rt_rq->rt_queued)
		return;

	if (rt_rq_throttled(rt_rq))
		return;

	if (rt_rq->rt_nr_running) {
		add_nr_running(rq, rt_rq->rt_nr_running);
		rt_rq->rt_queued = 1;
	}

	/* Kick cpufreq (see the comment in kernel/sched/sched.h). */
	cpufreq_update_util(rq, 0);
}