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
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct fib6_config {int fc_delete_all_nh; scalar_t__ fc_mp; scalar_t__ fc_nh_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int ip6_route_del (struct fib6_config*,struct netlink_ext_ack*) ; 
 int ip6_route_multipath_del (struct fib6_config*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  nexthop_find_by_id (int /*<<< orphan*/ ,scalar_t__) ; 
 int rtm_to_fib6_config (struct sk_buff*,struct nlmsghdr*,struct fib6_config*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int inet6_rtm_delroute(struct sk_buff *skb, struct nlmsghdr *nlh,
			      struct netlink_ext_ack *extack)
{
	struct fib6_config cfg;
	int err;

	err = rtm_to_fib6_config(skb, nlh, &cfg, extack);
	if (err < 0)
		return err;

	if (cfg.fc_nh_id &&
	    !nexthop_find_by_id(sock_net(skb->sk), cfg.fc_nh_id)) {
		NL_SET_ERR_MSG(extack, "Nexthop id does not exist");
		return -EINVAL;
	}

	if (cfg.fc_mp)
		return ip6_route_multipath_del(&cfg, extack);
	else {
		cfg.fc_delete_all_nh = 1;
		return ip6_route_del(&cfg, extack);
	}
}