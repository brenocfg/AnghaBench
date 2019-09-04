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
struct TYPE_3__ {int /*<<< orphan*/  weight; } ;
struct sched_entity {TYPE_1__ load; } ;
struct cfs_rq {int /*<<< orphan*/  nr_running; int /*<<< orphan*/  load; } ;
struct TYPE_4__ {int /*<<< orphan*/  load; } ;

/* Variables and functions */
 int /*<<< orphan*/  parent_entity (struct sched_entity*) ; 
 TYPE_2__* rq_of (struct cfs_rq*) ; 
 int /*<<< orphan*/  update_load_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
account_entity_dequeue(struct cfs_rq *cfs_rq, struct sched_entity *se)
{
	update_load_sub(&cfs_rq->load, se->load.weight);
	if (!parent_entity(se))
		update_load_sub(&rq_of(cfs_rq)->load, se->load.weight);
#ifdef CONFIG_SMP
	if (entity_is_task(se)) {
		account_numa_dequeue(rq_of(cfs_rq), task_of(se));
		list_del_init(&se->group_node);
	}
#endif
	cfs_rq->nr_running--;
}