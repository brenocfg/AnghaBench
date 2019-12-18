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
typedef  scalar_t__ u64 ;
struct rt_rq {int rt_throttled; scalar_t__ rt_time; } ;
struct rt_bandwidth {int /*<<< orphan*/  rt_runtime; } ;

/* Variables and functions */
 scalar_t__ RUNTIME_INF ; 
 int /*<<< orphan*/  balance_runtime (struct rt_rq*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk_deferred_once (char*) ; 
 int rt_rq_throttled (struct rt_rq*) ; 
 struct rt_bandwidth* sched_rt_bandwidth (struct rt_rq*) ; 
 scalar_t__ sched_rt_period (struct rt_rq*) ; 
 int /*<<< orphan*/  sched_rt_rq_dequeue (struct rt_rq*) ; 
 scalar_t__ sched_rt_runtime (struct rt_rq*) ; 

__attribute__((used)) static int sched_rt_runtime_exceeded(struct rt_rq *rt_rq)
{
	u64 runtime = sched_rt_runtime(rt_rq);

	if (rt_rq->rt_throttled)
		return rt_rq_throttled(rt_rq);

	if (runtime >= sched_rt_period(rt_rq))
		return 0;

	balance_runtime(rt_rq);
	runtime = sched_rt_runtime(rt_rq);
	if (runtime == RUNTIME_INF)
		return 0;

	if (rt_rq->rt_time > runtime) {
		struct rt_bandwidth *rt_b = sched_rt_bandwidth(rt_rq);

		/*
		 * Don't actually throttle groups that have no runtime assigned
		 * but accrue some time due to boosting.
		 */
		if (likely(rt_b->rt_runtime)) {
			rt_rq->rt_throttled = 1;
			printk_deferred_once("sched: RT throttling activated\n");
		} else {
			/*
			 * In case we did anyway, make it go away,
			 * replenishment is a joke, since it will replenish us
			 * with exactly 0 ns.
			 */
			rt_rq->rt_time = 0;
		}

		if (rt_rq_throttled(rt_rq)) {
			sched_rt_rq_dequeue(rt_rq);
			return 1;
		}
	}

	return 0;
}