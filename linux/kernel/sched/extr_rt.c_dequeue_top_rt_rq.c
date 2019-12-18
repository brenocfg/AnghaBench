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
struct rt_rq {scalar_t__ rt_queued; int /*<<< orphan*/  rt_nr_running; } ;
struct rq {int /*<<< orphan*/  nr_running; struct rt_rq rt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct rq* rq_of_rt_rq (struct rt_rq*) ; 
 int /*<<< orphan*/  sub_nr_running (struct rq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dequeue_top_rt_rq(struct rt_rq *rt_rq)
{
	struct rq *rq = rq_of_rt_rq(rt_rq);

	BUG_ON(&rq->rt != rt_rq);

	if (!rt_rq->rt_queued)
		return;

	BUG_ON(!rq->nr_running);

	sub_nr_running(rq, rt_rq->rt_nr_running);
	rt_rq->rt_queued = 0;

}