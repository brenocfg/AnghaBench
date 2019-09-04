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
struct TYPE_2__ {int /*<<< orphan*/  exec_start; } ;
struct task_struct {TYPE_1__ se; } ;
struct rq {struct task_struct* curr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dequeue_pushable_dl_task (struct rq*,struct task_struct*) ; 
 int /*<<< orphan*/  rq_clock_task (struct rq*) ; 

__attribute__((used)) static void set_curr_task_dl(struct rq *rq)
{
	struct task_struct *p = rq->curr;

	p->se.exec_start = rq_clock_task(rq);

	/* You can't push away the running task */
	dequeue_pushable_dl_task(rq, p);
}