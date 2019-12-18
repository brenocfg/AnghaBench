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
struct drr_sched {int /*<<< orphan*/  clhash; } ;
struct drr_class {scalar_t__ filter_cnt; int /*<<< orphan*/  common; int /*<<< orphan*/  qdisc; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  drr_destroy_class (struct Qdisc*,struct drr_class*) ; 
 int /*<<< orphan*/  qdisc_class_hash_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct drr_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_purge_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sch_tree_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_unlock (struct Qdisc*) ; 

__attribute__((used)) static int drr_delete_class(struct Qdisc *sch, unsigned long arg)
{
	struct drr_sched *q = qdisc_priv(sch);
	struct drr_class *cl = (struct drr_class *)arg;

	if (cl->filter_cnt > 0)
		return -EBUSY;

	sch_tree_lock(sch);

	qdisc_purge_queue(cl->qdisc);
	qdisc_class_hash_remove(&q->clhash, &cl->common);

	sch_tree_unlock(sch);

	drr_destroy_class(sch, cl);
	return 0;
}