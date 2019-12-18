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
struct tcmsg {scalar_t__ tcm_ifindex; scalar_t__ tcm_parent; int /*<<< orphan*/  tcm_block_index; } ;
struct tcf_chain {scalar_t__ index; } ;
struct tcf_block {int dummy; } ;
struct sk_buff {int len; int /*<<< orphan*/  sk; } ;
struct nlattr {int dummy; } ;
struct netlink_callback {long* args; int /*<<< orphan*/  extack; int /*<<< orphan*/  nlh; } ;
struct net_device {struct Qdisc* qdisc; } ;
struct net {int dummy; } ;
struct Qdisc_class_ops {unsigned long (* find ) (struct Qdisc*,scalar_t__) ;struct tcf_block* (* tcf_block ) (struct Qdisc*,unsigned long,int /*<<< orphan*/ *) ;} ;
struct Qdisc {TYPE_1__* ops; scalar_t__ handle; } ;
struct TYPE_2__ {struct Qdisc_class_ops* cl_ops; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 size_t TCA_CHAIN ; 
 int /*<<< orphan*/  TCA_MAX ; 
 scalar_t__ TCM_IFINDEX_MAGIC_BLOCK ; 
 int /*<<< orphan*/  TC_H_MAJ (scalar_t__) ; 
 scalar_t__ TC_H_MIN (scalar_t__) ; 
 struct net_device* __dev_get_by_index (struct net*,scalar_t__) ; 
 struct tcf_chain* __tcf_get_next_chain (struct tcf_block*,struct tcf_chain*) ; 
 scalar_t__ nla_get_u32 (struct nlattr*) ; 
 struct tcmsg* nlmsg_data (int /*<<< orphan*/ ) ; 
 int nlmsg_len (int /*<<< orphan*/ ) ; 
 int nlmsg_parse_deprecated (int /*<<< orphan*/ ,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct Qdisc* qdisc_lookup (struct net_device*,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 unsigned long stub1 (struct Qdisc*,scalar_t__) ; 
 struct tcf_block* stub2 (struct Qdisc*,unsigned long,int /*<<< orphan*/ *) ; 
 struct tcf_block* tcf_block_refcnt_get (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_block_refcnt_put (struct tcf_block*,int) ; 
 scalar_t__ tcf_block_shared (struct tcf_block*) ; 
 int /*<<< orphan*/  tcf_chain_dump (struct tcf_chain*,struct Qdisc*,scalar_t__,struct sk_buff*,struct netlink_callback*,long,long*) ; 
 int /*<<< orphan*/  tcf_chain_put (struct tcf_chain*) ; 

__attribute__((used)) static int tc_dump_tfilter(struct sk_buff *skb, struct netlink_callback *cb)
{
	struct tcf_chain *chain, *chain_prev;
	struct net *net = sock_net(skb->sk);
	struct nlattr *tca[TCA_MAX + 1];
	struct Qdisc *q = NULL;
	struct tcf_block *block;
	struct tcmsg *tcm = nlmsg_data(cb->nlh);
	long index_start;
	long index;
	u32 parent;
	int err;

	if (nlmsg_len(cb->nlh) < sizeof(*tcm))
		return skb->len;

	err = nlmsg_parse_deprecated(cb->nlh, sizeof(*tcm), tca, TCA_MAX,
				     NULL, cb->extack);
	if (err)
		return err;

	if (tcm->tcm_ifindex == TCM_IFINDEX_MAGIC_BLOCK) {
		block = tcf_block_refcnt_get(net, tcm->tcm_block_index);
		if (!block)
			goto out;
		/* If we work with block index, q is NULL and parent value
		 * will never be used in the following code. The check
		 * in tcf_fill_node prevents it. However, compiler does not
		 * see that far, so set parent to zero to silence the warning
		 * about parent being uninitialized.
		 */
		parent = 0;
	} else {
		const struct Qdisc_class_ops *cops;
		struct net_device *dev;
		unsigned long cl = 0;

		dev = __dev_get_by_index(net, tcm->tcm_ifindex);
		if (!dev)
			return skb->len;

		parent = tcm->tcm_parent;
		if (!parent) {
			q = dev->qdisc;
			parent = q->handle;
		} else {
			q = qdisc_lookup(dev, TC_H_MAJ(tcm->tcm_parent));
		}
		if (!q)
			goto out;
		cops = q->ops->cl_ops;
		if (!cops)
			goto out;
		if (!cops->tcf_block)
			goto out;
		if (TC_H_MIN(tcm->tcm_parent)) {
			cl = cops->find(q, tcm->tcm_parent);
			if (cl == 0)
				goto out;
		}
		block = cops->tcf_block(q, cl, NULL);
		if (!block)
			goto out;
		if (tcf_block_shared(block))
			q = NULL;
	}

	index_start = cb->args[0];
	index = 0;

	for (chain = __tcf_get_next_chain(block, NULL);
	     chain;
	     chain_prev = chain,
		     chain = __tcf_get_next_chain(block, chain),
		     tcf_chain_put(chain_prev)) {
		if (tca[TCA_CHAIN] &&
		    nla_get_u32(tca[TCA_CHAIN]) != chain->index)
			continue;
		if (!tcf_chain_dump(chain, q, parent, skb, cb,
				    index_start, &index)) {
			tcf_chain_put(chain);
			err = -EMSGSIZE;
			break;
		}
	}

	if (tcm->tcm_ifindex == TCM_IFINDEX_MAGIC_BLOCK)
		tcf_block_refcnt_put(block, true);
	cb->args[0] = index;

out:
	/* If we did no progress, the error (EMSGSIZE) is real */
	if (skb->len == 0 && err)
		return err;
	return skb->len;
}