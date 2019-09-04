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
struct tc_cbs_qopt {int idleslope; int sendslope; scalar_t__ offload; int /*<<< orphan*/  locredit; int /*<<< orphan*/  hicredit; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int speed; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;
struct cbs_sched_data {int port_rate; int idleslope; int sendslope; scalar_t__ offload; int /*<<< orphan*/  locredit; int /*<<< orphan*/  hicredit; } ;
struct Qdisc {int dummy; } ;
typedef  int s64 ;

/* Variables and functions */
 int BYTES_PER_KBIT ; 
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int SPEED_1000 ; 
 int /*<<< orphan*/  TCA_CBS_MAX ; 
 size_t TCA_CBS_PARMS ; 
 int /*<<< orphan*/  __ethtool_get_link_ksettings (struct net_device*,struct ethtool_link_ksettings*) ; 
 int /*<<< orphan*/  cbs_disable_offload (struct net_device*,struct cbs_sched_data*) ; 
 int cbs_enable_offload (struct net_device*,struct cbs_sched_data*,struct tc_cbs_qopt*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  cbs_policy ; 
 struct tc_cbs_qopt* nla_data (struct nlattr*) ; 
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 struct net_device* qdisc_dev (struct Qdisc*) ; 
 struct cbs_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int cbs_change(struct Qdisc *sch, struct nlattr *opt,
		      struct netlink_ext_ack *extack)
{
	struct cbs_sched_data *q = qdisc_priv(sch);
	struct net_device *dev = qdisc_dev(sch);
	struct nlattr *tb[TCA_CBS_MAX + 1];
	struct tc_cbs_qopt *qopt;
	int err;

	err = nla_parse_nested(tb, TCA_CBS_MAX, opt, cbs_policy, extack);
	if (err < 0)
		return err;

	if (!tb[TCA_CBS_PARMS]) {
		NL_SET_ERR_MSG(extack, "Missing CBS parameter which are mandatory");
		return -EINVAL;
	}

	qopt = nla_data(tb[TCA_CBS_PARMS]);

	if (!qopt->offload) {
		struct ethtool_link_ksettings ecmd;
		s64 link_speed;

		if (!__ethtool_get_link_ksettings(dev, &ecmd))
			link_speed = ecmd.base.speed;
		else
			link_speed = SPEED_1000;

		q->port_rate = link_speed * 1000 * BYTES_PER_KBIT;

		cbs_disable_offload(dev, q);
	} else {
		err = cbs_enable_offload(dev, q, qopt, extack);
		if (err < 0)
			return err;
	}

	/* Everything went OK, save the parameters used. */
	q->hicredit = qopt->hicredit;
	q->locredit = qopt->locredit;
	q->idleslope = qopt->idleslope * BYTES_PER_KBIT;
	q->sendslope = qopt->sendslope * BYTES_PER_KBIT;
	q->offload = qopt->offload;

	return 0;
}