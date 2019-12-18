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
struct sched_entity {int dummy; } ;
struct task_struct {struct sched_entity se; } ;
struct TYPE_3__ {scalar_t__ weight; } ;
struct TYPE_4__ {TYPE_1__ load; } ;
struct rq {TYPE_2__ cfs; } ;

/* Variables and functions */
 unsigned int NS_TO_JIFFIES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfs_rq_of (struct sched_entity*) ; 
 int /*<<< orphan*/  sched_slice (int /*<<< orphan*/ ,struct sched_entity*) ; 

__attribute__((used)) static unsigned int get_rr_interval_fair(struct rq *rq, struct task_struct *task)
{
	struct sched_entity *se = &task->se;
	unsigned int rr_interval = 0;

	/*
	 * Time slice is 0 for SCHED_OTHER tasks that are on an otherwise
	 * idle runqueue:
	 */
	if (rq->cfs.load.weight)
		rr_interval = NS_TO_JIFFIES(sched_slice(cfs_rq_of(se), se));

	return rr_interval;
}