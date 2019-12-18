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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct tipc_bearer {TYPE_1__ pt; int /*<<< orphan*/  up; } ;
struct sk_buff {scalar_t__ pkt_type; } ;
struct packet_type {int dummy; } ;
struct net_device {int /*<<< orphan*/  tipc_ptr; } ;

/* Variables and functions */
 int NET_RX_DROP ; 
 int NET_RX_SUCCESS ; 
 scalar_t__ PACKET_MULTICAST ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 struct tipc_bearer* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  skb_mark_not_on_list (struct sk_buff*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_rcv (int /*<<< orphan*/ ,struct sk_buff*,struct tipc_bearer*) ; 

__attribute__((used)) static int tipc_l2_rcv_msg(struct sk_buff *skb, struct net_device *dev,
			   struct packet_type *pt, struct net_device *orig_dev)
{
	struct tipc_bearer *b;

	rcu_read_lock();
	b = rcu_dereference(dev->tipc_ptr) ?:
		rcu_dereference(orig_dev->tipc_ptr);
	if (likely(b && test_bit(0, &b->up) &&
		   (skb->pkt_type <= PACKET_MULTICAST))) {
		skb_mark_not_on_list(skb);
		tipc_rcv(dev_net(b->pt.dev), skb, b);
		rcu_read_unlock();
		return NET_RX_SUCCESS;
	}
	rcu_read_unlock();
	kfree_skb(skb);
	return NET_RX_DROP;
}