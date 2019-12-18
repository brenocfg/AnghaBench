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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; } ;
struct nexthop {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int ENOENT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NLMSG_GOODSIZE ; 
 int /*<<< orphan*/  RTM_NEWNEXTHOP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct nexthop* nexthop_find_by_id (struct net*,int /*<<< orphan*/ ) ; 
 int nh_fill_node (struct sk_buff*,struct nexthop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nh_valid_get_del_req (struct nlmsghdr*,int /*<<< orphan*/ *,struct netlink_ext_ack*) ; 
 int rtnl_unicast (struct sk_buff*,struct net*,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtm_get_nexthop(struct sk_buff *in_skb, struct nlmsghdr *nlh,
			   struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(in_skb->sk);
	struct sk_buff *skb = NULL;
	struct nexthop *nh;
	int err;
	u32 id;

	err = nh_valid_get_del_req(nlh, &id, extack);
	if (err)
		return err;

	err = -ENOBUFS;
	skb = alloc_skb(NLMSG_GOODSIZE, GFP_KERNEL);
	if (!skb)
		goto out;

	err = -ENOENT;
	nh = nexthop_find_by_id(net, id);
	if (!nh)
		goto errout_free;

	err = nh_fill_node(skb, nh, RTM_NEWNEXTHOP, NETLINK_CB(in_skb).portid,
			   nlh->nlmsg_seq, 0);
	if (err < 0) {
		WARN_ON(err == -EMSGSIZE);
		goto errout_free;
	}

	err = rtnl_unicast(skb, net, NETLINK_CB(in_skb).portid);
out:
	return err;
errout_free:
	kfree_skb(skb);
	goto out;
}