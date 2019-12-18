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
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_fill_args {int add_ref; void* nsid; void* ref_nsid; int /*<<< orphan*/  cmd; int /*<<< orphan*/  seq; int /*<<< orphan*/  portid; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  portid; int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int ENOMEM ; 
 struct net* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct net*) ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 size_t NETNSA_FD ; 
 int /*<<< orphan*/  NETNSA_MAX ; 
 size_t NETNSA_NSID ; 
 size_t NETNSA_PID ; 
 size_t NETNSA_TARGET_NSID ; 
 int /*<<< orphan*/  NL_SET_BAD_ATTR (struct netlink_ext_ack*,struct nlattr*) ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int PTR_ERR (struct net*) ; 
 int /*<<< orphan*/  RTM_NEWNSID ; 
 struct net* get_net_ns_by_fd (int /*<<< orphan*/ ) ; 
 struct net* get_net_ns_by_id (struct net*,int) ; 
 struct net* get_net_ns_by_pid (int /*<<< orphan*/ ) ; 
 int nla_get_s32 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* peernet2id (struct net*,struct net*) ; 
 int /*<<< orphan*/  put_net (struct net*) ; 
 struct net* rtnl_get_net_ns_capable (int /*<<< orphan*/ ,int) ; 
 int rtnl_net_fill (struct sk_buff*,struct net_fill_args*) ; 
 int /*<<< orphan*/  rtnl_net_get_size () ; 
 int rtnl_net_valid_getid_req (struct sk_buff*,struct nlmsghdr*,struct nlattr**,struct netlink_ext_ack*) ; 
 int rtnl_unicast (struct sk_buff*,struct net*,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtnl_net_getid(struct sk_buff *skb, struct nlmsghdr *nlh,
			  struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(skb->sk);
	struct nlattr *tb[NETNSA_MAX + 1];
	struct net_fill_args fillargs = {
		.portid = NETLINK_CB(skb).portid,
		.seq = nlh->nlmsg_seq,
		.cmd = RTM_NEWNSID,
	};
	struct net *peer, *target = net;
	struct nlattr *nla;
	struct sk_buff *msg;
	int err;

	err = rtnl_net_valid_getid_req(skb, nlh, tb, extack);
	if (err < 0)
		return err;
	if (tb[NETNSA_PID]) {
		peer = get_net_ns_by_pid(nla_get_u32(tb[NETNSA_PID]));
		nla = tb[NETNSA_PID];
	} else if (tb[NETNSA_FD]) {
		peer = get_net_ns_by_fd(nla_get_u32(tb[NETNSA_FD]));
		nla = tb[NETNSA_FD];
	} else if (tb[NETNSA_NSID]) {
		peer = get_net_ns_by_id(net, nla_get_s32(tb[NETNSA_NSID]));
		if (!peer)
			peer = ERR_PTR(-ENOENT);
		nla = tb[NETNSA_NSID];
	} else {
		NL_SET_ERR_MSG(extack, "Peer netns reference is missing");
		return -EINVAL;
	}

	if (IS_ERR(peer)) {
		NL_SET_BAD_ATTR(extack, nla);
		NL_SET_ERR_MSG(extack, "Peer netns reference is invalid");
		return PTR_ERR(peer);
	}

	if (tb[NETNSA_TARGET_NSID]) {
		int id = nla_get_s32(tb[NETNSA_TARGET_NSID]);

		target = rtnl_get_net_ns_capable(NETLINK_CB(skb).sk, id);
		if (IS_ERR(target)) {
			NL_SET_BAD_ATTR(extack, tb[NETNSA_TARGET_NSID]);
			NL_SET_ERR_MSG(extack,
				       "Target netns reference is invalid");
			err = PTR_ERR(target);
			goto out;
		}
		fillargs.add_ref = true;
		fillargs.ref_nsid = peernet2id(net, peer);
	}

	msg = nlmsg_new(rtnl_net_get_size(), GFP_KERNEL);
	if (!msg) {
		err = -ENOMEM;
		goto out;
	}

	fillargs.nsid = peernet2id(target, peer);
	err = rtnl_net_fill(msg, &fillargs);
	if (err < 0)
		goto err_out;

	err = rtnl_unicast(msg, net, NETLINK_CB(skb).portid);
	goto out;

err_out:
	nlmsg_free(msg);
out:
	if (fillargs.add_ref)
		put_net(target);
	put_net(peer);
	return err;
}