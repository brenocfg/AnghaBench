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
struct nlmsghdr {int dummy; } ;
struct nl_info {int /*<<< orphan*/  portid; struct net* nl_net; struct nlmsghdr* nlh; } ;
struct nexthop {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int ENOENT ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 struct nexthop* nexthop_find_by_id (struct net*,int /*<<< orphan*/ ) ; 
 int nh_valid_get_del_req (struct nlmsghdr*,int /*<<< orphan*/ *,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  remove_nexthop (struct net*,struct nexthop*,struct nl_info*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtm_del_nexthop(struct sk_buff *skb, struct nlmsghdr *nlh,
			   struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(skb->sk);
	struct nl_info nlinfo = {
		.nlh = nlh,
		.nl_net = net,
		.portid = NETLINK_CB(skb).portid,
	};
	struct nexthop *nh;
	int err;
	u32 id;

	err = nh_valid_get_del_req(nlh, &id, extack);
	if (err)
		return err;

	nh = nexthop_find_by_id(net, id);
	if (!nh)
		return -ENOENT;

	remove_nexthop(net, nh, &nlinfo);

	return 0;
}