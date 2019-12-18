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
struct sk_buff {struct net_device* dev; } ;
struct rt6_info {TYPE_1__* rt6i_idev; } ;
struct net_device {scalar_t__ ifindex; } ;
struct TYPE_2__ {struct net_device* dev; } ;

/* Variables and functions */
 scalar_t__ LOOPBACK_IFINDEX ; 
 scalar_t__ netif_is_l3_master (struct net_device*) ; 
 struct rt6_info* skb_rt6_info (struct sk_buff const*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct net_device *icmp6_dev(const struct sk_buff *skb)
{
	struct net_device *dev = skb->dev;

	/* for local traffic to local address, skb dev is the loopback
	 * device. Check if there is a dst attached to the skb and if so
	 * get the real device index. Same is needed for replies to a link
	 * local address on a device enslaved to an L3 master device
	 */
	if (unlikely(dev->ifindex == LOOPBACK_IFINDEX || netif_is_l3_master(skb->dev))) {
		const struct rt6_info *rt6 = skb_rt6_info(skb);

		if (rt6)
			dev = rt6->rt6i_idev->dev;
	}

	return dev;
}