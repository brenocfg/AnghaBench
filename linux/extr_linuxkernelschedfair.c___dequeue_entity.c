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
struct sched_entity {int /*<<< orphan*/  run_node; } ;
struct cfs_rq {int /*<<< orphan*/  tasks_timeline; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb_erase_cached (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __dequeue_entity(struct cfs_rq *cfs_rq, struct sched_entity *se)
{
	rb_erase_cached(&se->run_node, &cfs_rq->tasks_timeline);
}