#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct tcmsg {scalar_t__ tcm_parent; int /*<<< orphan*/  tcm_handle; int /*<<< orphan*/  tcm_block_index; int /*<<< orphan*/  tcm_ifindex; int /*<<< orphan*/  tcm_info; } ;
struct tcf_proto {TYPE_3__* ops; } ;
struct tcf_chain_info {int dummy; } ;
struct tcf_chain {int /*<<< orphan*/  filter_chain_lock; } ;
struct tcf_block {TYPE_3__* ops; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct Qdisc {TYPE_2__* ops; } ;
struct TYPE_6__ {void* (* get ) (struct tcf_proto*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  kind; } ;
struct TYPE_5__ {TYPE_1__* cl_ops; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int IFNAMSIZ ; 
 scalar_t__ IS_ERR (struct tcf_proto*) ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int PTR_ERR (struct tcf_proto*) ; 
 int QDISC_CLASS_OPS_DOIT_UNLOCKED ; 
 int /*<<< orphan*/  RTM_NEWTFILTER ; 
 size_t TCA_CHAIN ; 
 size_t TCA_KIND ; 
 int /*<<< orphan*/  TCA_MAX ; 
 scalar_t__ TC_ACT_EXT_VAL_MASK ; 
 scalar_t__ TC_H_MAJ (int /*<<< orphan*/ ) ; 
 scalar_t__ TC_H_MIN (int /*<<< orphan*/ ) ; 
 struct tcf_proto* __tcf_block_find (struct net*,struct Qdisc*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int __tcf_qdisc_cl_find (struct Qdisc*,scalar_t__,unsigned long*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int __tcf_qdisc_find (struct net*,struct Qdisc**,scalar_t__*,int /*<<< orphan*/ ,int,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nla_get_u32 (struct nlattr*) ; 
 scalar_t__ nla_strcmp (struct nlattr*,int /*<<< orphan*/ ) ; 
 struct tcmsg* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_parse_deprecated (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  rtm_tca_policy ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 void* stub1 (struct tcf_proto*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_block_release (struct Qdisc*,struct tcf_proto*,int) ; 
 struct tcf_chain* tcf_chain_get (struct tcf_proto*,scalar_t__,int) ; 
 int /*<<< orphan*/  tcf_chain_put (struct tcf_chain*) ; 
 struct tcf_proto* tcf_chain_tp_find (struct tcf_chain*,struct tcf_chain_info*,scalar_t__,scalar_t__,int) ; 
 scalar_t__ tcf_proto_check_kind (struct nlattr*,char*) ; 
 int /*<<< orphan*/  tcf_proto_is_unlocked (char*) ; 
 int /*<<< orphan*/  tcf_proto_put (struct tcf_proto*,int,int /*<<< orphan*/ *) ; 
 int tfilter_notify (struct net*,struct sk_buff*,struct nlmsghdr*,struct tcf_proto*,struct tcf_proto*,struct Qdisc*,scalar_t__,void*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tfilter_put (struct tcf_proto*,void*) ; 

__attribute__((used)) static int tc_get_tfilter(struct sk_buff *skb, struct nlmsghdr *n,
			  struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(skb->sk);
	struct nlattr *tca[TCA_MAX + 1];
	char name[IFNAMSIZ];
	struct tcmsg *t;
	u32 protocol;
	u32 prio;
	u32 parent;
	u32 chain_index;
	struct Qdisc *q = NULL;
	struct tcf_chain_info chain_info;
	struct tcf_chain *chain = NULL;
	struct tcf_block *block = NULL;
	struct tcf_proto *tp = NULL;
	unsigned long cl = 0;
	void *fh = NULL;
	int err;
	bool rtnl_held = false;

	err = nlmsg_parse_deprecated(n, sizeof(*t), tca, TCA_MAX,
				     rtm_tca_policy, extack);
	if (err < 0)
		return err;

	t = nlmsg_data(n);
	protocol = TC_H_MIN(t->tcm_info);
	prio = TC_H_MAJ(t->tcm_info);
	parent = t->tcm_parent;

	if (prio == 0) {
		NL_SET_ERR_MSG(extack, "Invalid filter command with priority of zero");
		return -ENOENT;
	}

	/* Find head of filter chain. */

	err = __tcf_qdisc_find(net, &q, &parent, t->tcm_ifindex, false, extack);
	if (err)
		return err;

	if (tcf_proto_check_kind(tca[TCA_KIND], name)) {
		NL_SET_ERR_MSG(extack, "Specified TC filter name too long");
		err = -EINVAL;
		goto errout;
	}
	/* Take rtnl mutex if block is shared (no qdisc found), qdisc is not
	 * unlocked, classifier type is not specified, classifier is not
	 * unlocked.
	 */
	if ((q && !(q->ops->cl_ops->flags & QDISC_CLASS_OPS_DOIT_UNLOCKED)) ||
	    !tcf_proto_is_unlocked(name)) {
		rtnl_held = true;
		rtnl_lock();
	}

	err = __tcf_qdisc_cl_find(q, parent, &cl, t->tcm_ifindex, extack);
	if (err)
		goto errout;

	block = __tcf_block_find(net, q, cl, t->tcm_ifindex, t->tcm_block_index,
				 extack);
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
		NL_SET_ERR_MSG(extack, "Cannot find specified filter chain");
		err = -EINVAL;
		goto errout;
	}

	mutex_lock(&chain->filter_chain_lock);
	tp = tcf_chain_tp_find(chain, &chain_info, protocol,
			       prio, false);
	mutex_unlock(&chain->filter_chain_lock);
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
		NL_SET_ERR_MSG(extack, "Specified filter handle not found");
		err = -ENOENT;
	} else {
		err = tfilter_notify(net, skb, n, tp, block, q, parent,
				     fh, RTM_NEWTFILTER, true, rtnl_held);
		if (err < 0)
			NL_SET_ERR_MSG(extack, "Failed to send filter notify message");
	}

	tfilter_put(tp, fh);
errout:
	if (chain) {
		if (tp && !IS_ERR(tp))
			tcf_proto_put(tp, rtnl_held, NULL);
		tcf_chain_put(chain);
	}
	tcf_block_release(q, block, rtnl_held);

	if (rtnl_held)
		rtnl_unlock();

	return err;
}