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
struct sched_rt_entity {scalar_t__ on_rq; int /*<<< orphan*/  on_list; } ;
struct rt_prio_array {int dummy; } ;
struct rt_rq {struct rt_prio_array active; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __delist_rt_entity (struct sched_rt_entity*,struct rt_prio_array*) ; 
 int /*<<< orphan*/  dec_rt_tasks (struct sched_rt_entity*,struct rt_rq*) ; 
 scalar_t__ move_entity (unsigned int) ; 
 struct rt_rq* rt_rq_of_se (struct sched_rt_entity*) ; 

__attribute__((used)) static void __dequeue_rt_entity(struct sched_rt_entity *rt_se, unsigned int flags)
{
	struct rt_rq *rt_rq = rt_rq_of_se(rt_se);
	struct rt_prio_array *array = &rt_rq->active;

	if (move_entity(flags)) {
		WARN_ON_ONCE(!rt_se->on_list);
		__delist_rt_entity(rt_se, array);
	}
	rt_se->on_rq = 0;

	dec_rt_tasks(rt_se, rt_rq);
}