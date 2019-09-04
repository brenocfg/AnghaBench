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
struct dst_entry {int dummy; } ;
struct rtable {struct dst_entry dst; } ;
struct net_vrf {int /*<<< orphan*/  rth; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dst_hold (struct dst_entry*) ; 
 scalar_t__ likely (struct rtable*) ; 
 struct net_vrf* netdev_priv (struct net_device*) ; 
 struct rtable* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,struct dst_entry*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vrf_tx_error (struct net_device*,struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *vrf_ip_out_redirect(struct net_device *vrf_dev,
					   struct sk_buff *skb)
{
	struct net_vrf *vrf = netdev_priv(vrf_dev);
	struct dst_entry *dst = NULL;
	struct rtable *rth;

	rcu_read_lock();

	rth = rcu_dereference(vrf->rth);
	if (likely(rth)) {
		dst = &rth->dst;
		dst_hold(dst);
	}

	rcu_read_unlock();

	if (unlikely(!dst)) {
		vrf_tx_error(vrf_dev, skb);
		return NULL;
	}

	skb_dst_drop(skb);
	skb_dst_set(skb, dst);

	return skb;
}