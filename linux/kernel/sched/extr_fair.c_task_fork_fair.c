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
struct sched_entity {int /*<<< orphan*/  vruntime; } ;
struct task_struct {struct sched_entity se; } ;
struct rq_flags {int dummy; } ;
struct rq {int dummy; } ;
struct cfs_rq {scalar_t__ min_vruntime; struct sched_entity* curr; } ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 scalar_t__ entity_before (struct sched_entity*,struct sched_entity*) ; 
 int /*<<< orphan*/  place_entity (struct cfs_rq*,struct sched_entity*,int) ; 
 int /*<<< orphan*/  resched_curr (struct rq*) ; 
 int /*<<< orphan*/  rq_lock (struct rq*,struct rq_flags*) ; 
 int /*<<< orphan*/  rq_unlock (struct rq*,struct rq_flags*) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sysctl_sched_child_runs_first ; 
 struct cfs_rq* task_cfs_rq (int /*<<< orphan*/ ) ; 
 struct rq* this_rq () ; 
 int /*<<< orphan*/  update_curr (struct cfs_rq*) ; 
 int /*<<< orphan*/  update_rq_clock (struct rq*) ; 

__attribute__((used)) static void task_fork_fair(struct task_struct *p)
{
	struct cfs_rq *cfs_rq;
	struct sched_entity *se = &p->se, *curr;
	struct rq *rq = this_rq();
	struct rq_flags rf;

	rq_lock(rq, &rf);
	update_rq_clock(rq);

	cfs_rq = task_cfs_rq(current);
	curr = cfs_rq->curr;
	if (curr) {
		update_curr(cfs_rq);
		se->vruntime = curr->vruntime;
	}
	place_entity(cfs_rq, se, 1);

	if (sysctl_sched_child_runs_first && curr && entity_before(curr, se)) {
		/*
		 * Upon rescheduling, sched_class::put_prev_task() will place
		 * 'current' within the tree based on its new key value.
		 */
		swap(curr->vruntime, se->vruntime);
		resched_curr(rq);
	}

	se->vruntime -= cfs_rq->min_vruntime;
	rq_unlock(rq, &rf);
}