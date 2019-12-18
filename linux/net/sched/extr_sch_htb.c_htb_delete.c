#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct htb_sched {TYPE_4__* hlevel; int /*<<< orphan*/  clhash; } ;
struct TYPE_6__ {int /*<<< orphan*/  q; } ;
struct htb_class {size_t level; scalar_t__ cmode; int /*<<< orphan*/  pq_node; scalar_t__ prio_activity; TYPE_3__* parent; int /*<<< orphan*/  common; TYPE_2__ leaf; scalar_t__ filter_cnt; scalar_t__ children; } ;
struct Qdisc {int /*<<< orphan*/  dev_queue; } ;
struct TYPE_8__ {int /*<<< orphan*/  wait_pq; } ;
struct TYPE_5__ {int /*<<< orphan*/  classid; } ;
struct TYPE_7__ {int /*<<< orphan*/  children; TYPE_1__ common; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ HTB_CAN_SEND ; 
 int /*<<< orphan*/  htb_deactivate (struct htb_sched*,struct htb_class*) ; 
 int /*<<< orphan*/  htb_destroy_class (struct Qdisc*,struct htb_class*) ; 
 scalar_t__ htb_parent_last_child (struct htb_class*) ; 
 int /*<<< orphan*/  htb_parent_to_leaf (struct htb_sched*,struct htb_class*,struct Qdisc*) ; 
 int /*<<< orphan*/  htb_safe_rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfifo_qdisc_ops ; 
 int /*<<< orphan*/  qdisc_class_hash_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct Qdisc* qdisc_create_dflt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct htb_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_purge_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sch_tree_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_unlock (struct Qdisc*) ; 

__attribute__((used)) static int htb_delete(struct Qdisc *sch, unsigned long arg)
{
	struct htb_sched *q = qdisc_priv(sch);
	struct htb_class *cl = (struct htb_class *)arg;
	struct Qdisc *new_q = NULL;
	int last_child = 0;

	/* TODO: why don't allow to delete subtree ? references ? does
	 * tc subsys guarantee us that in htb_destroy it holds no class
	 * refs so that we can remove children safely there ?
	 */
	if (cl->children || cl->filter_cnt)
		return -EBUSY;

	if (!cl->level && htb_parent_last_child(cl)) {
		new_q = qdisc_create_dflt(sch->dev_queue, &pfifo_qdisc_ops,
					  cl->parent->common.classid,
					  NULL);
		last_child = 1;
	}

	sch_tree_lock(sch);

	if (!cl->level)
		qdisc_purge_queue(cl->leaf.q);

	/* delete from hash and active; remainder in destroy_class */
	qdisc_class_hash_remove(&q->clhash, &cl->common);
	if (cl->parent)
		cl->parent->children--;

	if (cl->prio_activity)
		htb_deactivate(q, cl);

	if (cl->cmode != HTB_CAN_SEND)
		htb_safe_rb_erase(&cl->pq_node,
				  &q->hlevel[cl->level].wait_pq);

	if (last_child)
		htb_parent_to_leaf(q, cl, new_q);

	sch_tree_unlock(sch);

	htb_destroy_class(sch, cl);
	return 0;
}