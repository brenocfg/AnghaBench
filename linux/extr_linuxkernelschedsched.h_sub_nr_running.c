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
struct rq {int /*<<< orphan*/  nr_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  sched_update_tick_dependency (struct rq*) ; 

__attribute__((used)) static inline void sub_nr_running(struct rq *rq, unsigned count)
{
	rq->nr_running -= count;
	/* Check if we still need preemption */
	sched_update_tick_dependency(rq);
}