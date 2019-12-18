#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct qfq_sched {int max_agg_classes; int min_slot_shift; int /*<<< orphan*/  nonfull_aggs; struct qfq_group* groups; int /*<<< orphan*/  clhash; int /*<<< orphan*/  filter_list; int /*<<< orphan*/  block; } ;
struct qfq_group {int index; int slot_shift; int /*<<< orphan*/ * slots; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct Qdisc {int dummy; } ;
struct TYPE_2__ {scalar_t__ tx_queue_len; } ;

/* Variables and functions */
 int FRAC_BITS ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ QFQ_MAX_AGG_CLASSES ; 
 int QFQ_MAX_INDEX ; 
 int QFQ_MAX_SLOTS ; 
 int QFQ_MTU_SHIFT ; 
 int __fls (int) ; 
 int qdisc_class_hash_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* qdisc_dev (struct Qdisc*) ; 
 struct qfq_sched* qdisc_priv (struct Qdisc*) ; 
 int tcf_block_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct Qdisc*,struct netlink_ext_ack*) ; 

__attribute__((used)) static int qfq_init_qdisc(struct Qdisc *sch, struct nlattr *opt,
			  struct netlink_ext_ack *extack)
{
	struct qfq_sched *q = qdisc_priv(sch);
	struct qfq_group *grp;
	int i, j, err;
	u32 max_cl_shift, maxbudg_shift, max_classes;

	err = tcf_block_get(&q->block, &q->filter_list, sch, extack);
	if (err)
		return err;

	err = qdisc_class_hash_init(&q->clhash);
	if (err < 0)
		return err;

	if (qdisc_dev(sch)->tx_queue_len + 1 > QFQ_MAX_AGG_CLASSES)
		max_classes = QFQ_MAX_AGG_CLASSES;
	else
		max_classes = qdisc_dev(sch)->tx_queue_len + 1;
	/* max_cl_shift = floor(log_2(max_classes)) */
	max_cl_shift = __fls(max_classes);
	q->max_agg_classes = 1<<max_cl_shift;

	/* maxbudg_shift = log2(max_len * max_classes_per_agg) */
	maxbudg_shift = QFQ_MTU_SHIFT + max_cl_shift;
	q->min_slot_shift = FRAC_BITS + maxbudg_shift - QFQ_MAX_INDEX;

	for (i = 0; i <= QFQ_MAX_INDEX; i++) {
		grp = &q->groups[i];
		grp->index = i;
		grp->slot_shift = q->min_slot_shift + i;
		for (j = 0; j < QFQ_MAX_SLOTS; j++)
			INIT_HLIST_HEAD(&grp->slots[j]);
	}

	INIT_HLIST_HEAD(&q->nonfull_aggs);

	return 0;
}