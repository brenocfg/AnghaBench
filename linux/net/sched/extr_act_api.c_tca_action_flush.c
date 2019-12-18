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
typedef  int /*<<< orphan*/  u32 ;
struct tcamsg {scalar_t__ tca__pad2; scalar_t__ tca__pad1; int /*<<< orphan*/  tca_family; } ;
struct tc_action_ops {int (* walk ) (struct net*,struct sk_buff*,struct netlink_callback*,int /*<<< orphan*/ ,struct tc_action_ops const*,struct netlink_ext_ack*) ;int /*<<< orphan*/  owner; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int nlmsg_len; int nlmsg_flags; int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct netlink_callback {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NLMSG_GOODSIZE ; 
 int NLM_F_ECHO ; 
 int NLM_F_ROOT ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  RTM_DELACTION ; 
 int /*<<< orphan*/  RTNLGRP_TC ; 
 size_t TCA_ACT_KIND ; 
 int /*<<< orphan*/  TCA_ACT_MAX ; 
 int /*<<< orphan*/  TCA_ACT_TAB ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 struct tcamsg* nlmsg_data (struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int rtnetlink_send (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 
 int stub1 (struct net*,struct sk_buff*,struct netlink_callback*,int /*<<< orphan*/ ,struct tc_action_ops const*,struct netlink_ext_ack*) ; 
 struct tc_action_ops* tc_lookup_action (struct nlattr*) ; 
 int /*<<< orphan*/  tcf_action_policy ; 

__attribute__((used)) static int tca_action_flush(struct net *net, struct nlattr *nla,
			    struct nlmsghdr *n, u32 portid,
			    struct netlink_ext_ack *extack)
{
	struct sk_buff *skb;
	unsigned char *b;
	struct nlmsghdr *nlh;
	struct tcamsg *t;
	struct netlink_callback dcb;
	struct nlattr *nest;
	struct nlattr *tb[TCA_ACT_MAX + 1];
	const struct tc_action_ops *ops;
	struct nlattr *kind;
	int err = -ENOMEM;

	skb = alloc_skb(NLMSG_GOODSIZE, GFP_KERNEL);
	if (!skb)
		return err;

	b = skb_tail_pointer(skb);

	err = nla_parse_nested_deprecated(tb, TCA_ACT_MAX, nla,
					  tcf_action_policy, extack);
	if (err < 0)
		goto err_out;

	err = -EINVAL;
	kind = tb[TCA_ACT_KIND];
	ops = tc_lookup_action(kind);
	if (!ops) { /*some idjot trying to flush unknown action */
		NL_SET_ERR_MSG(extack, "Cannot flush unknown TC action");
		goto err_out;
	}

	nlh = nlmsg_put(skb, portid, n->nlmsg_seq, RTM_DELACTION,
			sizeof(*t), 0);
	if (!nlh) {
		NL_SET_ERR_MSG(extack, "Failed to create TC action flush notification");
		goto out_module_put;
	}
	t = nlmsg_data(nlh);
	t->tca_family = AF_UNSPEC;
	t->tca__pad1 = 0;
	t->tca__pad2 = 0;

	nest = nla_nest_start_noflag(skb, TCA_ACT_TAB);
	if (!nest) {
		NL_SET_ERR_MSG(extack, "Failed to add new netlink message");
		goto out_module_put;
	}

	err = ops->walk(net, skb, &dcb, RTM_DELACTION, ops, extack);
	if (err <= 0) {
		nla_nest_cancel(skb, nest);
		goto out_module_put;
	}

	nla_nest_end(skb, nest);

	nlh->nlmsg_len = skb_tail_pointer(skb) - b;
	nlh->nlmsg_flags |= NLM_F_ROOT;
	module_put(ops->owner);
	err = rtnetlink_send(skb, net, portid, RTNLGRP_TC,
			     n->nlmsg_flags & NLM_F_ECHO);
	if (err > 0)
		return 0;
	if (err < 0)
		NL_SET_ERR_MSG(extack, "Failed to send TC action flush notification");

	return err;

out_module_put:
	module_put(ops->owner);
err_out:
	kfree_skb(skb);
	return err;
}