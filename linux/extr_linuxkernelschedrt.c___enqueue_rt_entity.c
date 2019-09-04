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
struct sched_rt_entity {int on_list; int on_rq; int /*<<< orphan*/  run_list; } ;
struct rt_prio_array {int /*<<< orphan*/  bitmap; struct list_head* queue; } ;
struct rt_rq {int /*<<< orphan*/  rt_nr_running; struct rt_prio_array active; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 unsigned int ENQUEUE_HEAD ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __delist_rt_entity (struct sched_rt_entity*,struct rt_prio_array*) ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 struct rt_rq* group_rt_rq (struct sched_rt_entity*) ; 
 int /*<<< orphan*/  inc_rt_tasks (struct sched_rt_entity*,struct rt_rq*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 scalar_t__ move_entity (unsigned int) ; 
 struct rt_rq* rt_rq_of_se (struct sched_rt_entity*) ; 
 scalar_t__ rt_rq_throttled (struct rt_rq*) ; 
 int rt_se_prio (struct sched_rt_entity*) ; 

__attribute__((used)) static void __enqueue_rt_entity(struct sched_rt_entity *rt_se, unsigned int flags)
{
	struct rt_rq *rt_rq = rt_rq_of_se(rt_se);
	struct rt_prio_array *array = &rt_rq->active;
	struct rt_rq *group_rq = group_rt_rq(rt_se);
	struct list_head *queue = array->queue + rt_se_prio(rt_se);

	/*
	 * Don't enqueue the group if its throttled, or when empty.
	 * The latter is a consequence of the former when a child group
	 * get throttled and the current group doesn't have any other
	 * active members.
	 */
	if (group_rq && (rt_rq_throttled(group_rq) || !group_rq->rt_nr_running)) {
		if (rt_se->on_list)
			__delist_rt_entity(rt_se, array);
		return;
	}

	if (move_entity(flags)) {
		WARN_ON_ONCE(rt_se->on_list);
		if (flags & ENQUEUE_HEAD)
			list_add(&rt_se->run_list, queue);
		else
			list_add_tail(&rt_se->run_list, queue);

		__set_bit(rt_se_prio(rt_se), array->bitmap);
		rt_se->on_list = 1;
	}
	rt_se->on_rq = 1;

	inc_rt_tasks(rt_se, rt_rq);
}