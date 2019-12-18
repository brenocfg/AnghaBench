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
struct tc_etf_qopt {int clockid; int /*<<< orphan*/  delta; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct etf_sched_data {int clockid; int /*<<< orphan*/  watchdog; int /*<<< orphan*/  get_time; int /*<<< orphan*/  skip_sock_check; scalar_t__ deadline_mode; scalar_t__ offload; int /*<<< orphan*/  delta; scalar_t__ queue; } ;
struct Qdisc {scalar_t__ dev_queue; } ;

/* Variables and functions */
#define  CLOCK_BOOTTIME 131 
#define  CLOCK_MONOTONIC 130 
#define  CLOCK_REALTIME 129 
#define  CLOCK_TAI 128 
 scalar_t__ DEADLINE_MODE_IS_ON (struct tc_etf_qopt*) ; 
 int EINVAL ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 scalar_t__ OFFLOAD_IS_ON (struct tc_etf_qopt*) ; 
 int /*<<< orphan*/  SKIP_SOCK_CHECK_IS_SET (struct tc_etf_qopt*) ; 
 int /*<<< orphan*/  TCA_ETF_MAX ; 
 size_t TCA_ETF_PARMS ; 
 int etf_enable_offload (struct net_device*,struct etf_sched_data*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  etf_policy ; 
 int /*<<< orphan*/  ktime_get ; 
 int /*<<< orphan*/  ktime_get_boottime ; 
 int /*<<< orphan*/  ktime_get_clocktai ; 
 int /*<<< orphan*/  ktime_get_real ; 
 scalar_t__ netdev_get_tx_queue (struct net_device*,int /*<<< orphan*/ ) ; 
 struct tc_etf_qopt* nla_data (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,char*,char*) ; 
 struct net_device* qdisc_dev (struct Qdisc*) ; 
 struct etf_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_watchdog_init_clockid (int /*<<< orphan*/ *,struct Qdisc*,int) ; 
 int validate_input_params (struct tc_etf_qopt*,struct netlink_ext_ack*) ; 

__attribute__((used)) static int etf_init(struct Qdisc *sch, struct nlattr *opt,
		    struct netlink_ext_ack *extack)
{
	struct etf_sched_data *q = qdisc_priv(sch);
	struct net_device *dev = qdisc_dev(sch);
	struct nlattr *tb[TCA_ETF_MAX + 1];
	struct tc_etf_qopt *qopt;
	int err;

	if (!opt) {
		NL_SET_ERR_MSG(extack,
			       "Missing ETF qdisc options which are mandatory");
		return -EINVAL;
	}

	err = nla_parse_nested_deprecated(tb, TCA_ETF_MAX, opt, etf_policy,
					  extack);
	if (err < 0)
		return err;

	if (!tb[TCA_ETF_PARMS]) {
		NL_SET_ERR_MSG(extack, "Missing mandatory ETF parameters");
		return -EINVAL;
	}

	qopt = nla_data(tb[TCA_ETF_PARMS]);

	pr_debug("delta %d clockid %d offload %s deadline %s\n",
		 qopt->delta, qopt->clockid,
		 OFFLOAD_IS_ON(qopt) ? "on" : "off",
		 DEADLINE_MODE_IS_ON(qopt) ? "on" : "off");

	err = validate_input_params(qopt, extack);
	if (err < 0)
		return err;

	q->queue = sch->dev_queue - netdev_get_tx_queue(dev, 0);

	if (OFFLOAD_IS_ON(qopt)) {
		err = etf_enable_offload(dev, q, extack);
		if (err < 0)
			return err;
	}

	/* Everything went OK, save the parameters used. */
	q->delta = qopt->delta;
	q->clockid = qopt->clockid;
	q->offload = OFFLOAD_IS_ON(qopt);
	q->deadline_mode = DEADLINE_MODE_IS_ON(qopt);
	q->skip_sock_check = SKIP_SOCK_CHECK_IS_SET(qopt);

	switch (q->clockid) {
	case CLOCK_REALTIME:
		q->get_time = ktime_get_real;
		break;
	case CLOCK_MONOTONIC:
		q->get_time = ktime_get;
		break;
	case CLOCK_BOOTTIME:
		q->get_time = ktime_get_boottime;
		break;
	case CLOCK_TAI:
		q->get_time = ktime_get_clocktai;
		break;
	default:
		NL_SET_ERR_MSG(extack, "Clockid is not supported");
		return -ENOTSUPP;
	}

	qdisc_watchdog_init_clockid(&q->watchdog, sch, q->clockid);

	return 0;
}