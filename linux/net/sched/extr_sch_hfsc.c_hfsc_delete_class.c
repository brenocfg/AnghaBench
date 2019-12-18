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
struct hfsc_class {scalar_t__ level; scalar_t__ filter_cnt; int /*<<< orphan*/  cl_common; int /*<<< orphan*/  qdisc; int /*<<< orphan*/  cl_parent; int /*<<< orphan*/  siblings; } ;
struct hfsc_sched {int /*<<< orphan*/  clhash; struct hfsc_class root; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  hfsc_adjust_levels (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfsc_destroy_class (struct Qdisc*,struct hfsc_class*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qdisc_class_hash_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct hfsc_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_purge_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sch_tree_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_unlock (struct Qdisc*) ; 

__attribute__((used)) static int
hfsc_delete_class(struct Qdisc *sch, unsigned long arg)
{
	struct hfsc_sched *q = qdisc_priv(sch);
	struct hfsc_class *cl = (struct hfsc_class *)arg;

	if (cl->level > 0 || cl->filter_cnt > 0 || cl == &q->root)
		return -EBUSY;

	sch_tree_lock(sch);

	list_del(&cl->siblings);
	hfsc_adjust_levels(cl->cl_parent);

	qdisc_purge_queue(cl->qdisc);
	qdisc_class_hash_remove(&q->clhash, &cl->cl_common);

	sch_tree_unlock(sch);

	hfsc_destroy_class(sch, cl);
	return 0;
}