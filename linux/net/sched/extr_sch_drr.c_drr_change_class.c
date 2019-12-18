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
typedef  scalar_t__ u32 ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct drr_sched {int /*<<< orphan*/  clhash; } ;
struct TYPE_2__ {scalar_t__ classid; } ;
struct drr_class {TYPE_1__ common; int /*<<< orphan*/ * qdisc; int /*<<< orphan*/  rate_est; int /*<<< orphan*/  bstats; scalar_t__ quantum; } ;
struct Qdisc {int /*<<< orphan*/  dev_queue; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  TCA_DRR_MAX ; 
 size_t TCA_DRR_QUANTUM ; 
 size_t TCA_OPTIONS ; 
 size_t TCA_RATE ; 
 int /*<<< orphan*/  drr_policy ; 
 int gen_replace_estimator (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nlattr*) ; 
 int /*<<< orphan*/  kfree (struct drr_class*) ; 
 struct drr_class* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_get_u32 (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  noop_qdisc ; 
 int /*<<< orphan*/  pfifo_qdisc_ops ; 
 scalar_t__ psched_mtu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_class_hash_grow (struct Qdisc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qdisc_class_hash_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * qdisc_create_dflt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qdisc_dev (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_hash_add (int /*<<< orphan*/ *,int) ; 
 struct drr_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qdisc_root_sleeping_running (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_unlock (struct Qdisc*) ; 

__attribute__((used)) static int drr_change_class(struct Qdisc *sch, u32 classid, u32 parentid,
			    struct nlattr **tca, unsigned long *arg,
			    struct netlink_ext_ack *extack)
{
	struct drr_sched *q = qdisc_priv(sch);
	struct drr_class *cl = (struct drr_class *)*arg;
	struct nlattr *opt = tca[TCA_OPTIONS];
	struct nlattr *tb[TCA_DRR_MAX + 1];
	u32 quantum;
	int err;

	if (!opt) {
		NL_SET_ERR_MSG(extack, "DRR options are required for this operation");
		return -EINVAL;
	}

	err = nla_parse_nested_deprecated(tb, TCA_DRR_MAX, opt, drr_policy,
					  extack);
	if (err < 0)
		return err;

	if (tb[TCA_DRR_QUANTUM]) {
		quantum = nla_get_u32(tb[TCA_DRR_QUANTUM]);
		if (quantum == 0) {
			NL_SET_ERR_MSG(extack, "Specified DRR quantum cannot be zero");
			return -EINVAL;
		}
	} else
		quantum = psched_mtu(qdisc_dev(sch));

	if (cl != NULL) {
		if (tca[TCA_RATE]) {
			err = gen_replace_estimator(&cl->bstats, NULL,
						    &cl->rate_est,
						    NULL,
						    qdisc_root_sleeping_running(sch),
						    tca[TCA_RATE]);
			if (err) {
				NL_SET_ERR_MSG(extack, "Failed to replace estimator");
				return err;
			}
		}

		sch_tree_lock(sch);
		if (tb[TCA_DRR_QUANTUM])
			cl->quantum = quantum;
		sch_tree_unlock(sch);

		return 0;
	}

	cl = kzalloc(sizeof(struct drr_class), GFP_KERNEL);
	if (cl == NULL)
		return -ENOBUFS;

	cl->common.classid = classid;
	cl->quantum	   = quantum;
	cl->qdisc	   = qdisc_create_dflt(sch->dev_queue,
					       &pfifo_qdisc_ops, classid,
					       NULL);
	if (cl->qdisc == NULL)
		cl->qdisc = &noop_qdisc;
	else
		qdisc_hash_add(cl->qdisc, true);

	if (tca[TCA_RATE]) {
		err = gen_replace_estimator(&cl->bstats, NULL, &cl->rate_est,
					    NULL,
					    qdisc_root_sleeping_running(sch),
					    tca[TCA_RATE]);
		if (err) {
			NL_SET_ERR_MSG(extack, "Failed to replace estimator");
			qdisc_put(cl->qdisc);
			kfree(cl);
			return err;
		}
	}

	sch_tree_lock(sch);
	qdisc_class_hash_insert(&q->clhash, &cl->common);
	sch_tree_unlock(sch);

	qdisc_class_hash_grow(sch, &q->clhash);

	*arg = (unsigned long)cl;
	return 0;
}