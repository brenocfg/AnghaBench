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
struct tcmsg {scalar_t__ tcm_parent; scalar_t__ tcm_handle; int /*<<< orphan*/  tcm_block_index; int /*<<< orphan*/  tcm_ifindex; int /*<<< orphan*/  tcm_info; } ;
struct tcf_proto {TYPE_1__* ops; } ;
struct tcf_chain_info {int dummy; } ;
struct tcf_chain {int dummy; } ;
struct tcf_block {TYPE_1__* ops; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int /*<<< orphan*/  user_ns; } ;
struct Qdisc {int dummy; } ;
struct TYPE_2__ {void* (* get ) (struct tcf_proto*,scalar_t__) ;int /*<<< orphan*/  kind; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EINVAL ; 
 int ENOENT ; 
 int EPERM ; 
 scalar_t__ IS_ERR (struct tcf_proto*) ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int PTR_ERR (struct tcf_proto*) ; 
 int /*<<< orphan*/  RTM_DELTFILTER ; 
 size_t TCA_CHAIN ; 
 size_t TCA_KIND ; 
 int /*<<< orphan*/  TCA_MAX ; 
 scalar_t__ TC_ACT_EXT_VAL_MASK ; 
 scalar_t__ TC_H_MAJ (int /*<<< orphan*/ ) ; 
 scalar_t__ TC_H_MIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netlink_ns_capable (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_get_u32 (struct nlattr*) ; 
 scalar_t__ nla_strcmp (struct nlattr*,int /*<<< orphan*/ ) ; 
 struct tcmsg* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_parse (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  rtm_tca_policy ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 void* stub1 (struct tcf_proto*,scalar_t__) ; 
 struct tcf_proto* tcf_block_find (struct net*,struct Qdisc**,scalar_t__*,unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  tcf_chain_flush (struct tcf_chain*) ; 
 struct tcf_chain* tcf_chain_get (struct tcf_proto*,scalar_t__,int) ; 
 int /*<<< orphan*/  tcf_chain_put (struct tcf_chain*) ; 
 struct tcf_proto* tcf_chain_tp_find (struct tcf_chain*,struct tcf_chain_info*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  tcf_chain_tp_remove (struct tcf_chain*,struct tcf_chain_info*,struct tcf_proto*) ; 
 int /*<<< orphan*/  tcf_proto_destroy (struct tcf_proto*,struct netlink_ext_ack*) ; 
 int tfilter_del_notify (struct net*,struct sk_buff*,struct nlmsghdr*,struct tcf_proto*,struct tcf_proto*,struct Qdisc*,scalar_t__,void*,int,int*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  tfilter_notify (struct net*,struct sk_buff*,struct nlmsghdr*,struct tcf_proto*,struct tcf_proto*,struct Qdisc*,scalar_t__,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tfilter_notify_chain (struct net*,struct sk_buff*,struct tcf_proto*,struct Qdisc*,scalar_t__,struct nlmsghdr*,struct tcf_chain*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tc_del_tfilter(struct sk_buff *skb, struct nlmsghdr *n,
			  struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(skb->sk);
	struct nlattr *tca[TCA_MAX + 1];
	struct tcmsg *t;
	u32 protocol;
	u32 prio;
	u32 parent;
	u32 chain_index;
	struct Qdisc *q = NULL;
	struct tcf_chain_info chain_info;
	struct tcf_chain *chain = NULL;
	struct tcf_block *block;
	struct tcf_proto *tp = NULL;
	unsigned long cl = 0;
	void *fh = NULL;
	int err;

	if (!netlink_ns_capable(skb, net->user_ns, CAP_NET_ADMIN))
		return -EPERM;

	err = nlmsg_parse(n, sizeof(*t), tca, TCA_MAX, rtm_tca_policy, extack);
	if (err < 0)
		return err;

	t = nlmsg_data(n);
	protocol = TC_H_MIN(t->tcm_info);
	prio = TC_H_MAJ(t->tcm_info);
	parent = t->tcm_parent;

	if (prio == 0 && (protocol || t->tcm_handle || tca[TCA_KIND])) {
		NL_SET_ERR_MSG(extack, "Cannot flush filters with protocol, handle or kind set");
		return -ENOENT;
	}

	/* Find head of filter chain. */

	block = tcf_block_find(net, &q, &parent, &cl,
			       t->tcm_ifindex, t->tcm_block_index, extack);
	if (IS_ERR(block)) {
		err = PTR_ERR(block);
		goto errout;
	}

	chain_index = tca[TCA_CHAIN] ? nla_get_u32(tca[TCA_CHAIN]) : 0;
	if (chain_index > TC_ACT_EXT_VAL_MASK) {
		NL_SET_ERR_MSG(extack, "Specified chain index exceeds upper limit");
		err = -EINVAL;
		goto errout;
	}
	chain = tcf_chain_get(block, chain_index, false);
	if (!chain) {
		/* User requested flush on non-existent chain. Nothing to do,
		 * so just return success.
		 */
		if (prio == 0) {
			err = 0;
			goto errout;
		}
		NL_SET_ERR_MSG(extack, "Cannot find specified filter chain");
		err = -ENOENT;
		goto errout;
	}

	if (prio == 0) {
		tfilter_notify_chain(net, skb, block, q, parent, n,
				     chain, RTM_DELTFILTER);
		tcf_chain_flush(chain);
		err = 0;
		goto errout;
	}

	tp = tcf_chain_tp_find(chain, &chain_info, protocol,
			       prio, false);
	if (!tp || IS_ERR(tp)) {
		NL_SET_ERR_MSG(extack, "Filter with specified priority/protocol not found");
		err = tp ? PTR_ERR(tp) : -ENOENT;
		goto errout;
	} else if (tca[TCA_KIND] && nla_strcmp(tca[TCA_KIND], tp->ops->kind)) {
		NL_SET_ERR_MSG(extack, "Specified filter kind does not match existing one");
		err = -EINVAL;
		goto errout;
	}

	fh = tp->ops->get(tp, t->tcm_handle);

	if (!fh) {
		if (t->tcm_handle == 0) {
			tcf_chain_tp_remove(chain, &chain_info, tp);
			tfilter_notify(net, skb, n, tp, block, q, parent, fh,
				       RTM_DELTFILTER, false);
			tcf_proto_destroy(tp, extack);
			err = 0;
		} else {
			NL_SET_ERR_MSG(extack, "Specified filter handle not found");
			err = -ENOENT;
		}
	} else {
		bool last;

		err = tfilter_del_notify(net, skb, n, tp, block,
					 q, parent, fh, false, &last,
					 extack);
		if (err)
			goto errout;
		if (last) {
			tcf_chain_tp_remove(chain, &chain_info, tp);
			tcf_proto_destroy(tp, extack);
		}
	}

errout:
	if (chain)
		tcf_chain_put(chain);
	return err;
}