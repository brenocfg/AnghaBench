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
struct sw_flow_actions {int /*<<< orphan*/  actions_len; int /*<<< orphan*/  actions; } ;
struct sw_flow {int /*<<< orphan*/  sf_acts; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  OVS_FLOW_ATTR_ACTIONS ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int ovs_nla_put_actions (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct sw_flow_actions* rcu_dereference_ovsl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovs_flow_cmd_fill_actions(const struct sw_flow *flow,
				     struct sk_buff *skb, int skb_orig_len)
{
	struct nlattr *start;
	int err;

	/* If OVS_FLOW_ATTR_ACTIONS doesn't fit, skip dumping the actions if
	 * this is the first flow to be dumped into 'skb'.  This is unusual for
	 * Netlink but individual action lists can be longer than
	 * NLMSG_GOODSIZE and thus entirely undumpable if we didn't do this.
	 * The userspace caller can always fetch the actions separately if it
	 * really wants them.  (Most userspace callers in fact don't care.)
	 *
	 * This can only fail for dump operations because the skb is always
	 * properly sized for single flows.
	 */
	start = nla_nest_start_noflag(skb, OVS_FLOW_ATTR_ACTIONS);
	if (start) {
		const struct sw_flow_actions *sf_acts;

		sf_acts = rcu_dereference_ovsl(flow->sf_acts);
		err = ovs_nla_put_actions(sf_acts->actions,
					  sf_acts->actions_len, skb);

		if (!err)
			nla_nest_end(skb, start);
		else {
			if (skb_orig_len)
				return err;

			nla_nest_cancel(skb, start);
		}
	} else if (skb_orig_len) {
		return -EMSGSIZE;
	}

	return 0;
}