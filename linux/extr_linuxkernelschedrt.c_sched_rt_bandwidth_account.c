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
struct rt_rq {scalar_t__ rt_time; } ;
struct rt_bandwidth {scalar_t__ rt_runtime; int /*<<< orphan*/  rt_period_timer; } ;

/* Variables and functions */
 scalar_t__ hrtimer_active (int /*<<< orphan*/ *) ; 
 struct rt_bandwidth* sched_rt_bandwidth (struct rt_rq*) ; 

bool sched_rt_bandwidth_account(struct rt_rq *rt_rq)
{
	struct rt_bandwidth *rt_b = sched_rt_bandwidth(rt_rq);

	return (hrtimer_active(&rt_b->rt_period_timer) ||
		rt_rq->rt_time < rt_b->rt_runtime);
}