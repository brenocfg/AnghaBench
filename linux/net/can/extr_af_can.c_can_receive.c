#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {struct can_dev_rcv_lists* rx_alldev_list; struct can_pkg_stats* pkg_stats; } ;
struct net {TYPE_1__ can; } ;
struct can_pkg_stats {int /*<<< orphan*/  matches_delta; int /*<<< orphan*/  matches; int /*<<< orphan*/  rx_frames_delta; int /*<<< orphan*/  rx_frames; } ;
struct can_dev_rcv_lists {int dummy; } ;
struct TYPE_4__ {scalar_t__ skbcnt; } ;

/* Variables and functions */
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 struct can_dev_rcv_lists* can_dev_rcv_lists_find (struct net*,struct net_device*) ; 
 int can_rcv_filter (struct can_dev_rcv_lists*,struct sk_buff*) ; 
 TYPE_2__* can_skb_prv (struct sk_buff*) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  skbcounter ; 

__attribute__((used)) static void can_receive(struct sk_buff *skb, struct net_device *dev)
{
	struct can_dev_rcv_lists *dev_rcv_lists;
	struct net *net = dev_net(dev);
	struct can_pkg_stats *pkg_stats = net->can.pkg_stats;
	int matches;

	/* update statistics */
	pkg_stats->rx_frames++;
	pkg_stats->rx_frames_delta++;

	/* create non-zero unique skb identifier together with *skb */
	while (!(can_skb_prv(skb)->skbcnt))
		can_skb_prv(skb)->skbcnt = atomic_inc_return(&skbcounter);

	rcu_read_lock();

	/* deliver the packet to sockets listening on all devices */
	matches = can_rcv_filter(net->can.rx_alldev_list, skb);

	/* find receive list for this device */
	dev_rcv_lists = can_dev_rcv_lists_find(net, dev);
	matches += can_rcv_filter(dev_rcv_lists, skb);

	rcu_read_unlock();

	/* consume the skbuff allocated by the netdevice driver */
	consume_skb(skb);

	if (matches > 0) {
		pkg_stats->matches++;
		pkg_stats->matches_delta++;
	}
}