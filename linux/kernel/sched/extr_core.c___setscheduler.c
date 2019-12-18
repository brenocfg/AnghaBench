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
struct task_struct {int /*<<< orphan*/ * sched_class; int /*<<< orphan*/  prio; } ;
struct sched_attr {int sched_flags; } ;
struct rq {int dummy; } ;

/* Variables and functions */
 int SCHED_FLAG_KEEP_PARAMS ; 
 int /*<<< orphan*/  __setscheduler_params (struct task_struct*,struct sched_attr const*) ; 
 scalar_t__ dl_prio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dl_sched_class ; 
 int /*<<< orphan*/  fair_sched_class ; 
 int /*<<< orphan*/  normal_prio (struct task_struct*) ; 
 int /*<<< orphan*/  rt_effective_prio (struct task_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ rt_prio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_sched_class ; 

__attribute__((used)) static void __setscheduler(struct rq *rq, struct task_struct *p,
			   const struct sched_attr *attr, bool keep_boost)
{
	/*
	 * If params can't change scheduling class changes aren't allowed
	 * either.
	 */
	if (attr->sched_flags & SCHED_FLAG_KEEP_PARAMS)
		return;

	__setscheduler_params(p, attr);

	/*
	 * Keep a potential priority boosting if called from
	 * sched_setscheduler().
	 */
	p->prio = normal_prio(p);
	if (keep_boost)
		p->prio = rt_effective_prio(p, p->prio);

	if (dl_prio(p->prio))
		p->sched_class = &dl_sched_class;
	else if (rt_prio(p->prio))
		p->sched_class = &rt_sched_class;
	else
		p->sched_class = &fair_sched_class;
}