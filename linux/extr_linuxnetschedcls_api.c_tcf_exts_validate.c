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
struct tcf_proto {int dummy; } ;
struct tcf_exts {size_t action; size_t police; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 

int tcf_exts_validate(struct net *net, struct tcf_proto *tp, struct nlattr **tb,
		      struct nlattr *rate_tlv, struct tcf_exts *exts, bool ovr,
		      struct netlink_ext_ack *extack)
{
#ifdef CONFIG_NET_CLS_ACT
	{
		struct tc_action *act;
		size_t attr_size = 0;

		if (exts->police && tb[exts->police]) {
			act = tcf_action_init_1(net, tp, tb[exts->police],
						rate_tlv, "police", ovr,
						TCA_ACT_BIND, true, extack);
			if (IS_ERR(act))
				return PTR_ERR(act);

			act->type = exts->type = TCA_OLD_COMPAT;
			exts->actions[0] = act;
			exts->nr_actions = 1;
		} else if (exts->action && tb[exts->action]) {
			int err;

			err = tcf_action_init(net, tp, tb[exts->action],
					      rate_tlv, NULL, ovr, TCA_ACT_BIND,
					      exts->actions, &attr_size, true,
					      extack);
			if (err < 0)
				return err;
			exts->nr_actions = err;
		}
		exts->net = net;
	}
#else
	if ((exts->action && tb[exts->action]) ||
	    (exts->police && tb[exts->police])) {
		NL_SET_ERR_MSG(extack, "Classifier actions are not supported per compile options (CONFIG_NET_CLS_ACT)");
		return -EOPNOTSUPP;
	}
#endif

	return 0;
}