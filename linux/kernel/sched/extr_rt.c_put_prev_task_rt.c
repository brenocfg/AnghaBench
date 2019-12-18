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
struct task_struct {int nr_cpus_allowed; int /*<<< orphan*/  rt; } ;
struct rq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  enqueue_pushable_task (struct rq*,struct task_struct*) ; 
 scalar_t__ on_rt_rq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rq_clock_pelt (struct rq*) ; 
 int /*<<< orphan*/  update_curr_rt (struct rq*) ; 
 int /*<<< orphan*/  update_rt_rq_load_avg (int /*<<< orphan*/ ,struct rq*,int) ; 

__attribute__((used)) static void put_prev_task_rt(struct rq *rq, struct task_struct *p)
{
	update_curr_rt(rq);

	update_rt_rq_load_avg(rq_clock_pelt(rq), rq, 1);

	/*
	 * The previous task needs to be made eligible for pushing
	 * if it is still active
	 */
	if (on_rt_rq(&p->rt) && p->nr_cpus_allowed > 1)
		enqueue_pushable_task(rq, p);
}