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
struct sched_entity {int /*<<< orphan*/  on_rq; } ;
struct task_struct {struct sched_entity se; } ;
struct rq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfs_rq_of (struct sched_entity*) ; 
 int /*<<< orphan*/  set_next_buddy (struct sched_entity*) ; 
 scalar_t__ throttled_hierarchy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yield_task_fair (struct rq*) ; 

__attribute__((used)) static bool yield_to_task_fair(struct rq *rq, struct task_struct *p, bool preempt)
{
	struct sched_entity *se = &p->se;

	/* throttled hierarchies are not runnable */
	if (!se->on_rq || throttled_hierarchy(cfs_rq_of(se)))
		return false;

	/* Tell the scheduler that we'd really like pse to run next. */
	set_next_buddy(se);

	yield_task_fair(rq);

	return true;
}