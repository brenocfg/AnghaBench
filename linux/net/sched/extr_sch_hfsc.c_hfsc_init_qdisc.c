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
struct tc_hfsc_qopt {int /*<<< orphan*/  defcls; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  classid; } ;
struct TYPE_3__ {TYPE_2__ cl_common; void* cf_tree; void* vt_tree; int /*<<< orphan*/  children; int /*<<< orphan*/ * qdisc; struct hfsc_sched* sched; int /*<<< orphan*/  filter_list; int /*<<< orphan*/  block; } ;
struct hfsc_sched {int /*<<< orphan*/  clhash; TYPE_1__ root; void* eligible; int /*<<< orphan*/  defcls; int /*<<< orphan*/  watchdog; } ;
struct Qdisc {int /*<<< orphan*/  handle; int /*<<< orphan*/  dev_queue; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 void* RB_ROOT ; 
 struct tc_hfsc_qopt* nla_data (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 int /*<<< orphan*/  noop_qdisc ; 
 int /*<<< orphan*/  pfifo_qdisc_ops ; 
 int /*<<< orphan*/  qdisc_class_hash_grow (struct Qdisc*,int /*<<< orphan*/ *) ; 
 int qdisc_class_hash_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qdisc_class_hash_insert (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * qdisc_create_dflt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qdisc_hash_add (int /*<<< orphan*/ *,int) ; 
 struct hfsc_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_watchdog_init (int /*<<< orphan*/ *,struct Qdisc*) ; 
 int tcf_block_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct Qdisc*,struct netlink_ext_ack*) ; 

__attribute__((used)) static int
hfsc_init_qdisc(struct Qdisc *sch, struct nlattr *opt,
		struct netlink_ext_ack *extack)
{
	struct hfsc_sched *q = qdisc_priv(sch);
	struct tc_hfsc_qopt *qopt;
	int err;

	qdisc_watchdog_init(&q->watchdog, sch);

	if (!opt || nla_len(opt) < sizeof(*qopt))
		return -EINVAL;
	qopt = nla_data(opt);

	q->defcls = qopt->defcls;
	err = qdisc_class_hash_init(&q->clhash);
	if (err < 0)
		return err;
	q->eligible = RB_ROOT;

	err = tcf_block_get(&q->root.block, &q->root.filter_list, sch, extack);
	if (err)
		return err;

	q->root.cl_common.classid = sch->handle;
	q->root.sched   = q;
	q->root.qdisc = qdisc_create_dflt(sch->dev_queue, &pfifo_qdisc_ops,
					  sch->handle, NULL);
	if (q->root.qdisc == NULL)
		q->root.qdisc = &noop_qdisc;
	else
		qdisc_hash_add(q->root.qdisc, true);
	INIT_LIST_HEAD(&q->root.children);
	q->root.vt_tree = RB_ROOT;
	q->root.cf_tree = RB_ROOT;

	qdisc_class_hash_insert(&q->clhash, &q->root.cl_common);
	qdisc_class_hash_grow(sch, &q->clhash);

	return 0;
}