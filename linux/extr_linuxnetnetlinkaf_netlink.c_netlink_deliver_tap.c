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
struct sk_buff {int dummy; } ;
struct netlink_tap_net {int /*<<< orphan*/  netlink_tap_all; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __netlink_deliver_tap (struct sk_buff*,struct netlink_tap_net*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct netlink_tap_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netlink_tap_net_id ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void netlink_deliver_tap(struct net *net, struct sk_buff *skb)
{
	struct netlink_tap_net *nn = net_generic(net, netlink_tap_net_id);

	rcu_read_lock();

	if (unlikely(!list_empty(&nn->netlink_tap_all)))
		__netlink_deliver_tap(skb, nn);

	rcu_read_unlock();
}