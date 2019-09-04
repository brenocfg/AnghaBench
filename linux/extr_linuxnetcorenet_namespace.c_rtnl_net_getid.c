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
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct rtgenmsg {int dummy; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct net*) ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 size_t NETNSA_FD ; 
 int /*<<< orphan*/  NETNSA_MAX ; 
 size_t NETNSA_PID ; 
 int /*<<< orphan*/  NL_SET_BAD_ATTR (struct netlink_ext_ack*,struct nlattr*) ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int PTR_ERR (struct net*) ; 
 int /*<<< orphan*/  RTM_NEWNSID ; 
 struct net* get_net_ns_by_fd (int /*<<< orphan*/ ) ; 
 struct net* get_net_ns_by_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nlmsg_parse (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int peernet2id (struct net*,struct net*) ; 
 int /*<<< orphan*/  put_net (struct net*) ; 
 int rtnl_net_fill (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net*,int) ; 
 int /*<<< orphan*/  rtnl_net_get_size () ; 
 int /*<<< orphan*/  rtnl_net_policy ; 
 int rtnl_unicast (struct sk_buff*,struct net*,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtnl_net_getid(struct sk_buff *skb, struct nlmsghdr *nlh,
			  struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(skb->sk);
	struct nlattr *tb[NETNSA_MAX + 1];
	struct nlattr *nla;
	struct sk_buff *msg;
	struct net *peer;
	int err, id;

	err = nlmsg_parse(nlh, sizeof(struct rtgenmsg), tb, NETNSA_MAX,
			  rtnl_net_policy, extack);
	if (err < 0)
		return err;
	if (tb[NETNSA_PID]) {
		peer = get_net_ns_by_pid(nla_get_u32(tb[NETNSA_PID]));
		nla = tb[NETNSA_PID];
	} else if (tb[NETNSA_FD]) {
		peer = get_net_ns_by_fd(nla_get_u32(tb[NETNSA_FD]));
		nla = tb[NETNSA_FD];
	} else {
		NL_SET_ERR_MSG(extack, "Peer netns reference is missing");
		return -EINVAL;
	}

	if (IS_ERR(peer)) {
		NL_SET_BAD_ATTR(extack, nla);
		NL_SET_ERR_MSG(extack, "Peer netns reference is invalid");
		return PTR_ERR(peer);
	}

	msg = nlmsg_new(rtnl_net_get_size(), GFP_KERNEL);
	if (!msg) {
		err = -ENOMEM;
		goto out;
	}

	id = peernet2id(net, peer);
	err = rtnl_net_fill(msg, NETLINK_CB(skb).portid, nlh->nlmsg_seq, 0,
			    RTM_NEWNSID, net, id);
	if (err < 0)
		goto err_out;

	err = rtnl_unicast(msg, net, NETLINK_CB(skb).portid);
	goto out;

err_out:
	nlmsg_free(msg);
out:
	put_net(peer);
	return err;
}