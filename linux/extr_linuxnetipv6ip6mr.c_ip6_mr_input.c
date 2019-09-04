#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {TYPE_2__* dev; int /*<<< orphan*/  mark; } ;
struct net {int dummy; } ;
struct mr_table {int dummy; } ;
struct mfc6_cache {int dummy; } ;
struct flowi6 {int /*<<< orphan*/  flowi6_mark; int /*<<< orphan*/  flowi6_iif; } ;
struct TYPE_5__ {int /*<<< orphan*/  ifindex; } ;
struct TYPE_4__ {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int ENODEV ; 
 struct net* dev_net (TYPE_2__*) ; 
 int /*<<< orphan*/  ip6_mr_forward (struct net*,struct mr_table*,struct sk_buff*,struct mfc6_cache*) ; 
 struct mfc6_cache* ip6mr_cache_find (struct mr_table*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mfc6_cache* ip6mr_cache_find_any (struct mr_table*,int /*<<< orphan*/ *,int) ; 
 int ip6mr_cache_unresolved (struct mr_table*,int,struct sk_buff*) ; 
 int ip6mr_fib_lookup (struct net*,struct flowi6*,struct mr_table**) ; 
 int ip6mr_find_vif (struct mr_table*,TYPE_2__*) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mrt_lock ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

int ip6_mr_input(struct sk_buff *skb)
{
	struct mfc6_cache *cache;
	struct net *net = dev_net(skb->dev);
	struct mr_table *mrt;
	struct flowi6 fl6 = {
		.flowi6_iif	= skb->dev->ifindex,
		.flowi6_mark	= skb->mark,
	};
	int err;

	err = ip6mr_fib_lookup(net, &fl6, &mrt);
	if (err < 0) {
		kfree_skb(skb);
		return err;
	}

	read_lock(&mrt_lock);
	cache = ip6mr_cache_find(mrt,
				 &ipv6_hdr(skb)->saddr, &ipv6_hdr(skb)->daddr);
	if (!cache) {
		int vif = ip6mr_find_vif(mrt, skb->dev);

		if (vif >= 0)
			cache = ip6mr_cache_find_any(mrt,
						     &ipv6_hdr(skb)->daddr,
						     vif);
	}

	/*
	 *	No usable cache entry
	 */
	if (!cache) {
		int vif;

		vif = ip6mr_find_vif(mrt, skb->dev);
		if (vif >= 0) {
			int err = ip6mr_cache_unresolved(mrt, vif, skb);
			read_unlock(&mrt_lock);

			return err;
		}
		read_unlock(&mrt_lock);
		kfree_skb(skb);
		return -ENODEV;
	}

	ip6_mr_forward(net, mrt, skb, cache);

	read_unlock(&mrt_lock);

	return 0;
}