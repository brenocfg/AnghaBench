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
struct net {int dummy; } ;
struct fib_table {int dummy; } ;
struct fib_config {int /*<<< orphan*/  fc_table; scalar_t__ fc_nh_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 struct fib_table* fib_get_table (struct net*,int /*<<< orphan*/ ) ; 
 int fib_table_delete (struct net*,struct fib_table*,struct fib_config*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  nexthop_find_by_id (struct net*,scalar_t__) ; 
 int rtm_to_fib_config (struct net*,struct sk_buff*,struct nlmsghdr*,struct fib_config*,struct netlink_ext_ack*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int inet_rtm_delroute(struct sk_buff *skb, struct nlmsghdr *nlh,
			     struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(skb->sk);
	struct fib_config cfg;
	struct fib_table *tb;
	int err;

	err = rtm_to_fib_config(net, skb, nlh, &cfg, extack);
	if (err < 0)
		goto errout;

	if (cfg.fc_nh_id && !nexthop_find_by_id(net, cfg.fc_nh_id)) {
		NL_SET_ERR_MSG(extack, "Nexthop id does not exist");
		err = -EINVAL;
		goto errout;
	}

	tb = fib_get_table(net, cfg.fc_table);
	if (!tb) {
		NL_SET_ERR_MSG(extack, "FIB table does not exist");
		err = -ESRCH;
		goto errout;
	}

	err = fib_table_delete(net, tb, &cfg, extack);
errout:
	return err;
}