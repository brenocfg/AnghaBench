#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct Qdisc {int limit; } ;
struct TYPE_3__ {int tx_queue_len; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 size_t TCA_GRED_DPS ; 
 size_t TCA_GRED_LIMIT ; 
 int /*<<< orphan*/  TCA_GRED_MAX ; 
 size_t TCA_GRED_PARMS ; 
 size_t TCA_GRED_STAB ; 
 int gred_change_table_def (struct Qdisc*,struct nlattr*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  gred_policy ; 
 int nla_get_u32 (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int psched_mtu (TYPE_1__*) ; 
 TYPE_1__* qdisc_dev (struct Qdisc*) ; 

__attribute__((used)) static int gred_init(struct Qdisc *sch, struct nlattr *opt,
		     struct netlink_ext_ack *extack)
{
	struct nlattr *tb[TCA_GRED_MAX + 1];
	int err;

	if (!opt)
		return -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_GRED_MAX, opt, gred_policy,
					  extack);
	if (err < 0)
		return err;

	if (tb[TCA_GRED_PARMS] || tb[TCA_GRED_STAB]) {
		NL_SET_ERR_MSG_MOD(extack,
				   "virtual queue configuration can't be specified at initialization time");
		return -EINVAL;
	}

	if (tb[TCA_GRED_LIMIT])
		sch->limit = nla_get_u32(tb[TCA_GRED_LIMIT]);
	else
		sch->limit = qdisc_dev(sch)->tx_queue_len
		             * psched_mtu(qdisc_dev(sch));

	return gred_change_table_def(sch, tb[TCA_GRED_DPS], extack);
}