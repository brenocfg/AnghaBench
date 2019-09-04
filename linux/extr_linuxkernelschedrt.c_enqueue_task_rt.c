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
struct sched_rt_entity {scalar_t__ timeout; } ;
struct task_struct {int nr_cpus_allowed; struct sched_rt_entity rt; } ;
struct rq {int dummy; } ;

/* Variables and functions */
 int ENQUEUE_WAKEUP ; 
 int /*<<< orphan*/  enqueue_pushable_task (struct rq*,struct task_struct*) ; 
 int /*<<< orphan*/  enqueue_rt_entity (struct sched_rt_entity*,int) ; 
 int /*<<< orphan*/  task_current (struct rq*,struct task_struct*) ; 

__attribute__((used)) static void
enqueue_task_rt(struct rq *rq, struct task_struct *p, int flags)
{
	struct sched_rt_entity *rt_se = &p->rt;

	if (flags & ENQUEUE_WAKEUP)
		rt_se->timeout = 0;

	enqueue_rt_entity(rt_se, flags);

	if (!task_current(rq, p) && p->nr_cpus_allowed > 1)
		enqueue_pushable_task(rq, p);
}