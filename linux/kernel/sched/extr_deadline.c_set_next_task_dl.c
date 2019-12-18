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
 int /*<<< orphan*/  deadline_queue_push_tasks (struct rq*) ; 
 int /*<<< orphan*/  dequeue_pushable_dl_task (struct rq*,struct task_struct*) ; 
 int /*<<< orphan*/  dl_sched_class ; 
 scalar_t__ hrtick_enabled (struct rq*) ; 
 int /*<<< orphan*/  rq_clock_pelt (struct rq*) ; 
 int /*<<< orphan*/  rq_clock_task (struct rq*) ; 
 int /*<<< orphan*/  start_hrtick_dl (struct rq*,struct task_struct*) ; 
 int /*<<< orphan*/  update_dl_rq_load_avg (int /*<<< orphan*/ ,struct rq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_next_task_dl(struct rq *rq, struct task_struct *p)
{
	p->se.exec_start = rq_clock_task(rq);

	/* You can't push away the running task */
	dequeue_pushable_dl_task(rq, p);

	if (hrtick_enabled(rq))
		start_hrtick_dl(rq, p);

	if (rq->curr->sched_class != &dl_sched_class)
		update_dl_rq_load_avg(rq_clock_pelt(rq), rq, 0);

	deadline_queue_push_tasks(rq);
}