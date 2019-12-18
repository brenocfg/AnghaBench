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
struct nlmsghdr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_2__ {int fib_has_custom_local_routes; } ;
struct net {TYPE_1__ ipv4; } ;
struct fib_table {int dummy; } ;
struct fib_config {scalar_t__ fc_type; int /*<<< orphan*/  fc_table; } ;

/* Variables and functions */
 int ENOBUFS ; 
 scalar_t__ RTN_LOCAL ; 
 struct fib_table* fib_new_table (struct net*,int /*<<< orphan*/ ) ; 
 int fib_table_insert (struct net*,struct fib_table*,struct fib_config*,struct netlink_ext_ack*) ; 
 int rtm_to_fib_config (struct net*,struct sk_buff*,struct nlmsghdr*,struct fib_config*,struct netlink_ext_ack*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int inet_rtm_newroute(struct sk_buff *skb, struct nlmsghdr *nlh,
			     struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(skb->sk);
	struct fib_config cfg;
	struct fib_table *tb;
	int err;

	err = rtm_to_fib_config(net, skb, nlh, &cfg, extack);
	if (err < 0)
		goto errout;

	tb = fib_new_table(net, cfg.fc_table);
	if (!tb) {
		err = -ENOBUFS;
		goto errout;
	}

	err = fib_table_insert(net, tb, &cfg, extack);
	if (!err && cfg.fc_type == RTN_LOCAL)
		net->ipv4.fib_has_custom_local_routes = true;
errout:
	return err;
}