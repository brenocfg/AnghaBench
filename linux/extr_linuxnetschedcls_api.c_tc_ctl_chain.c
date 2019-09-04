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
struct tcmsg {int /*<<< orphan*/  tcm_block_index; int /*<<< orphan*/  tcm_ifindex; int /*<<< orphan*/  tcm_parent; } ;
struct tcf_chain {int explicitly_created; } ;
struct tcf_block {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int nlmsg_type; int nlmsg_flags; int nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int /*<<< orphan*/  user_ns; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EAGAIN ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 scalar_t__ IS_ERR (struct tcf_block*) ; 
 int NLM_F_CREATE ; 
 int NLM_F_EXCL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int PTR_ERR (struct tcf_block*) ; 
#define  RTM_DELCHAIN 130 
 int /*<<< orphan*/  RTM_DELTFILTER ; 
#define  RTM_GETCHAIN 129 
#define  RTM_NEWCHAIN 128 
 size_t TCA_CHAIN ; 
 int /*<<< orphan*/  TCA_MAX ; 
 int /*<<< orphan*/  TC_ACT_EXT_VAL_MASK ; 
 int /*<<< orphan*/  netlink_ns_capable (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 struct tcmsg* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_parse (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  rtm_tca_policy ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int tc_chain_notify (struct tcf_chain*,struct sk_buff*,int,int,int const,int) ; 
 int tc_chain_tmplt_add (struct tcf_chain*,struct net*,struct nlattr**,struct netlink_ext_ack*) ; 
 struct tcf_block* tcf_block_find (struct net*,struct Qdisc**,int /*<<< orphan*/ *,unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 struct tcf_chain* tcf_chain_create (struct tcf_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_chain_flush (struct tcf_chain*) ; 
 scalar_t__ tcf_chain_held_by_acts_only (struct tcf_chain*) ; 
 int /*<<< orphan*/  tcf_chain_hold (struct tcf_chain*) ; 
 struct tcf_chain* tcf_chain_lookup (struct tcf_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_chain_put (struct tcf_chain*) ; 
 int /*<<< orphan*/  tcf_chain_put_explicitly_created (struct tcf_chain*) ; 
 int /*<<< orphan*/  tfilter_notify_chain (struct net*,struct sk_buff*,struct tcf_block*,struct Qdisc*,int /*<<< orphan*/ ,struct nlmsghdr*,struct tcf_chain*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tc_ctl_chain(struct sk_buff *skb, struct nlmsghdr *n,
			struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(skb->sk);
	struct nlattr *tca[TCA_MAX + 1];
	struct tcmsg *t;
	u32 parent;
	u32 chain_index;
	struct Qdisc *q = NULL;
	struct tcf_chain *chain = NULL;
	struct tcf_block *block;
	unsigned long cl;
	int err;

	if (n->nlmsg_type != RTM_GETCHAIN &&
	    !netlink_ns_capable(skb, net->user_ns, CAP_NET_ADMIN))
		return -EPERM;

replay:
	err = nlmsg_parse(n, sizeof(*t), tca, TCA_MAX, rtm_tca_policy, extack);
	if (err < 0)
		return err;

	t = nlmsg_data(n);
	parent = t->tcm_parent;
	cl = 0;

	block = tcf_block_find(net, &q, &parent, &cl,
			       t->tcm_ifindex, t->tcm_block_index, extack);
	if (IS_ERR(block))
		return PTR_ERR(block);

	chain_index = tca[TCA_CHAIN] ? nla_get_u32(tca[TCA_CHAIN]) : 0;
	if (chain_index > TC_ACT_EXT_VAL_MASK) {
		NL_SET_ERR_MSG(extack, "Specified chain index exceeds upper limit");
		return -EINVAL;
	}
	chain = tcf_chain_lookup(block, chain_index);
	if (n->nlmsg_type == RTM_NEWCHAIN) {
		if (chain) {
			if (tcf_chain_held_by_acts_only(chain)) {
				/* The chain exists only because there is
				 * some action referencing it.
				 */
				tcf_chain_hold(chain);
			} else {
				NL_SET_ERR_MSG(extack, "Filter chain already exists");
				return -EEXIST;
			}
		} else {
			if (!(n->nlmsg_flags & NLM_F_CREATE)) {
				NL_SET_ERR_MSG(extack, "Need both RTM_NEWCHAIN and NLM_F_CREATE to create a new chain");
				return -ENOENT;
			}
			chain = tcf_chain_create(block, chain_index);
			if (!chain) {
				NL_SET_ERR_MSG(extack, "Failed to create filter chain");
				return -ENOMEM;
			}
		}
	} else {
		if (!chain || tcf_chain_held_by_acts_only(chain)) {
			NL_SET_ERR_MSG(extack, "Cannot find specified filter chain");
			return -EINVAL;
		}
		tcf_chain_hold(chain);
	}

	switch (n->nlmsg_type) {
	case RTM_NEWCHAIN:
		err = tc_chain_tmplt_add(chain, net, tca, extack);
		if (err)
			goto errout;
		/* In case the chain was successfully added, take a reference
		 * to the chain. This ensures that an empty chain
		 * does not disappear at the end of this function.
		 */
		tcf_chain_hold(chain);
		chain->explicitly_created = true;
		tc_chain_notify(chain, NULL, 0, NLM_F_CREATE | NLM_F_EXCL,
				RTM_NEWCHAIN, false);
		break;
	case RTM_DELCHAIN:
		tfilter_notify_chain(net, skb, block, q, parent, n,
				     chain, RTM_DELTFILTER);
		/* Flush the chain first as the user requested chain removal. */
		tcf_chain_flush(chain);
		/* In case the chain was successfully deleted, put a reference
		 * to the chain previously taken during addition.
		 */
		tcf_chain_put_explicitly_created(chain);
		chain->explicitly_created = false;
		break;
	case RTM_GETCHAIN:
		err = tc_chain_notify(chain, skb, n->nlmsg_seq,
				      n->nlmsg_seq, n->nlmsg_type, true);
		if (err < 0)
			NL_SET_ERR_MSG(extack, "Failed to send chain notify message");
		break;
	default:
		err = -EOPNOTSUPP;
		NL_SET_ERR_MSG(extack, "Unsupported message type");
		goto errout;
	}

errout:
	tcf_chain_put(chain);
	if (err == -EAGAIN)
		/* Replay the request. */
		goto replay;
	return err;
}