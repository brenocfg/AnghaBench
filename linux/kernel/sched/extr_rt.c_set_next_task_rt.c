#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  exec_start; } ;
struct task_struct {TYPE_1__ se; } ;
struct rq {TYPE_2__* curr; } ;
struct TYPE_4__ {int /*<<< orphan*/ * sched_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  dequeue_pushable_task (struct rq*,struct task_struct*) ; 
 int /*<<< orphan*/  rq_clock_pelt (struct rq*) ; 
 int /*<<< orphan*/  rq_clock_task (struct rq*) ; 
 int /*<<< orphan*/  rt_queue_push_tasks (struct rq*) ; 
 int /*<<< orphan*/  rt_sched_class ; 
 int /*<<< orphan*/  update_rt_rq_load_avg (int /*<<< orphan*/ ,struct rq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_next_task_rt(struct rq *rq, struct task_struct *p)
{
	p->se.exec_start = rq_clock_task(rq);

	/* The running task is never eligible for pushing */
	dequeue_pushable_task(rq, p);

	/*
	 * If prev task was rt, put_prev_task() has already updated the
	 * utilization. We only care of the case where we start to schedule a
	 * rt task
	 */
	if (rq->curr->sched_class != &rt_sched_class)
		update_rt_rq_load_avg(rq_clock_pelt(rq), rq, 0);

	rt_queue_push_tasks(rq);
}