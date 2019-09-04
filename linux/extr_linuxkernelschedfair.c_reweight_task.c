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
struct load_weight {int /*<<< orphan*/  inv_weight; } ;
struct sched_entity {struct load_weight load; } ;
struct task_struct {struct sched_entity se; } ;
struct cfs_rq {int dummy; } ;

/* Variables and functions */
 struct cfs_rq* cfs_rq_of (struct sched_entity*) ; 
 int /*<<< orphan*/  reweight_entity (struct cfs_rq*,struct sched_entity*,unsigned long,unsigned long) ; 
 unsigned long scale_load (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sched_prio_to_weight ; 
 int /*<<< orphan*/ * sched_prio_to_wmult ; 

void reweight_task(struct task_struct *p, int prio)
{
	struct sched_entity *se = &p->se;
	struct cfs_rq *cfs_rq = cfs_rq_of(se);
	struct load_weight *load = &se->load;
	unsigned long weight = scale_load(sched_prio_to_weight[prio]);

	reweight_entity(cfs_rq, se, weight, weight);
	load->inv_weight = sched_prio_to_wmult[prio];
}