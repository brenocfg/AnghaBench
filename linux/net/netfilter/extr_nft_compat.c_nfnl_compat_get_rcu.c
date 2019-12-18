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
typedef  void* u32 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_type; int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct nfgenmsg {int nfgen_family; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
#define  AF_INET 131 
#define  AF_INET6 130 
 int EAGAIN ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NFNL_MSG_COMPAT_GET ; 
 int /*<<< orphan*/  NFNL_MSG_TYPE (int /*<<< orphan*/ ) ; 
#define  NFPROTO_ARP 129 
#define  NFPROTO_BRIDGE 128 
 size_t NFTA_COMPAT_NAME ; 
 size_t NFTA_COMPAT_REV ; 
 size_t NFTA_COMPAT_TYPE ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int netlink_unicast (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nfnl_compat_fill_info (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const*,int,int) ; 
 char* nla_data (struct nlattr const* const) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 struct nfgenmsg* nlmsg_data (struct nlmsghdr const*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_then_request_module (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  xt_find_revision (int,char const*,void*,int,int*) ; 

__attribute__((used)) static int nfnl_compat_get_rcu(struct net *net, struct sock *nfnl,
			       struct sk_buff *skb, const struct nlmsghdr *nlh,
			       const struct nlattr * const tb[],
			       struct netlink_ext_ack *extack)
{
	int ret = 0, target;
	struct nfgenmsg *nfmsg;
	const char *fmt;
	const char *name;
	u32 rev;
	struct sk_buff *skb2;

	if (tb[NFTA_COMPAT_NAME] == NULL ||
	    tb[NFTA_COMPAT_REV] == NULL ||
	    tb[NFTA_COMPAT_TYPE] == NULL)
		return -EINVAL;

	name = nla_data(tb[NFTA_COMPAT_NAME]);
	rev = ntohl(nla_get_be32(tb[NFTA_COMPAT_REV]));
	target = ntohl(nla_get_be32(tb[NFTA_COMPAT_TYPE]));

	nfmsg = nlmsg_data(nlh);

	switch(nfmsg->nfgen_family) {
	case AF_INET:
		fmt = "ipt_%s";
		break;
	case AF_INET6:
		fmt = "ip6t_%s";
		break;
	case NFPROTO_BRIDGE:
		fmt = "ebt_%s";
		break;
	case NFPROTO_ARP:
		fmt = "arpt_%s";
		break;
	default:
		pr_err("nft_compat: unsupported protocol %d\n",
			nfmsg->nfgen_family);
		return -EINVAL;
	}

	if (!try_module_get(THIS_MODULE))
		return -EINVAL;

	rcu_read_unlock();
	try_then_request_module(xt_find_revision(nfmsg->nfgen_family, name,
						 rev, target, &ret),
						 fmt, name);
	if (ret < 0)
		goto out_put;

	skb2 = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (skb2 == NULL) {
		ret = -ENOMEM;
		goto out_put;
	}

	/* include the best revision for this extension in the message */
	if (nfnl_compat_fill_info(skb2, NETLINK_CB(skb).portid,
				  nlh->nlmsg_seq,
				  NFNL_MSG_TYPE(nlh->nlmsg_type),
				  NFNL_MSG_COMPAT_GET,
				  nfmsg->nfgen_family,
				  name, ret, target) <= 0) {
		kfree_skb(skb2);
		goto out_put;
	}

	ret = netlink_unicast(nfnl, skb2, NETLINK_CB(skb).portid,
				MSG_DONTWAIT);
	if (ret > 0)
		ret = 0;
out_put:
	rcu_read_lock();
	module_put(THIS_MODULE);
	return ret == -EAGAIN ? -ENOBUFS : ret;
}