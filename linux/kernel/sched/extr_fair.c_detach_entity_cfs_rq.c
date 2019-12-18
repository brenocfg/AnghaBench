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
struct sched_entity {int dummy; } ;
struct cfs_rq {int dummy; } ;

/* Variables and functions */
 struct cfs_rq* cfs_rq_of (struct sched_entity*) ; 
 int /*<<< orphan*/  detach_entity_load_avg (struct cfs_rq*,struct sched_entity*) ; 
 int /*<<< orphan*/  propagate_entity_cfs_rq (struct sched_entity*) ; 
 int /*<<< orphan*/  update_load_avg (struct cfs_rq*,struct sched_entity*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tg_load_avg (struct cfs_rq*,int) ; 

__attribute__((used)) static void detach_entity_cfs_rq(struct sched_entity *se)
{
	struct cfs_rq *cfs_rq = cfs_rq_of(se);

	/* Catch up with the cfs_rq and remove our load when we leave */
	update_load_avg(cfs_rq, se, 0);
	detach_entity_load_avg(cfs_rq, se);
	update_tg_load_avg(cfs_rq, false);
	propagate_entity_cfs_rq(se);
}