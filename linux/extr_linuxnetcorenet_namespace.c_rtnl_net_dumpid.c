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
struct sk_buff {int len; int /*<<< orphan*/  sk; } ;
struct rtnl_net_dump_cb {int /*<<< orphan*/  idx; int /*<<< orphan*/  s_idx; struct netlink_callback* cb; struct sk_buff* skb; struct net* net; } ;
struct netlink_callback {int /*<<< orphan*/ * args; } ;
struct net {int /*<<< orphan*/  nsid_lock; int /*<<< orphan*/  netns_ids; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_for_each (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rtnl_net_dump_cb*) ; 
 int /*<<< orphan*/  rtnl_net_dumpid_one ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rtnl_net_dumpid(struct sk_buff *skb, struct netlink_callback *cb)
{
	struct net *net = sock_net(skb->sk);
	struct rtnl_net_dump_cb net_cb = {
		.net = net,
		.skb = skb,
		.cb = cb,
		.idx = 0,
		.s_idx = cb->args[0],
	};

	spin_lock_bh(&net->nsid_lock);
	idr_for_each(&net->netns_ids, rtnl_net_dumpid_one, &net_cb);
	spin_unlock_bh(&net->nsid_lock);

	cb->args[0] = net_cb.idx;
	return skb->len;
}