#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct tcmsg {int /*<<< orphan*/  tcm_block_index; int /*<<< orphan*/  tcm_ifindex; int /*<<< orphan*/  tcm_parent; scalar_t__ tcm_handle; scalar_t__ tcm__pad2; scalar_t__ tcm__pad1; int /*<<< orphan*/  tcm_family; } ;
struct tcf_proto_ops {scalar_t__ (* tmplt_dump ) (struct sk_buff*,struct net*,void*) ;int /*<<< orphan*/  kind; } ;
struct tcf_block {int /*<<< orphan*/  index; TYPE_2__* q; } ;
struct sk_buff {int len; } ;
struct nlmsghdr {int nlmsg_len; } ;
struct net {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  handle; } ;
struct TYPE_3__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  TCA_CHAIN ; 
 int /*<<< orphan*/  TCA_KIND ; 
 int /*<<< orphan*/  TCM_IFINDEX_MAGIC_BLOCK ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tcmsg* nlmsg_data (struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 TYPE_1__* qdisc_dev (TYPE_2__*) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 
 scalar_t__ stub1 (struct sk_buff*,struct net*,void*) ; 

__attribute__((used)) static int tc_chain_fill_node(const struct tcf_proto_ops *tmplt_ops,
			      void *tmplt_priv, u32 chain_index,
			      struct net *net, struct sk_buff *skb,
			      struct tcf_block *block,
			      u32 portid, u32 seq, u16 flags, int event)
{
	unsigned char *b = skb_tail_pointer(skb);
	const struct tcf_proto_ops *ops;
	struct nlmsghdr *nlh;
	struct tcmsg *tcm;
	void *priv;

	ops = tmplt_ops;
	priv = tmplt_priv;

	nlh = nlmsg_put(skb, portid, seq, event, sizeof(*tcm), flags);
	if (!nlh)
		goto out_nlmsg_trim;
	tcm = nlmsg_data(nlh);
	tcm->tcm_family = AF_UNSPEC;
	tcm->tcm__pad1 = 0;
	tcm->tcm__pad2 = 0;
	tcm->tcm_handle = 0;
	if (block->q) {
		tcm->tcm_ifindex = qdisc_dev(block->q)->ifindex;
		tcm->tcm_parent = block->q->handle;
	} else {
		tcm->tcm_ifindex = TCM_IFINDEX_MAGIC_BLOCK;
		tcm->tcm_block_index = block->index;
	}

	if (nla_put_u32(skb, TCA_CHAIN, chain_index))
		goto nla_put_failure;

	if (ops) {
		if (nla_put_string(skb, TCA_KIND, ops->kind))
			goto nla_put_failure;
		if (ops->tmplt_dump(skb, net, priv) < 0)
			goto nla_put_failure;
	}

	nlh->nlmsg_len = skb_tail_pointer(skb) - b;
	return skb->len;

out_nlmsg_trim:
nla_put_failure:
	nlmsg_trim(skb, b);
	return -EMSGSIZE;
}