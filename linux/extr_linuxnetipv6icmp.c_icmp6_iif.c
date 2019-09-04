#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {TYPE_3__* dev; } ;
struct rt6_info {TYPE_2__* rt6i_idev; } ;
struct TYPE_6__ {int ifindex; } ;
struct TYPE_5__ {TYPE_1__* dev; } ;
struct TYPE_4__ {int ifindex; } ;

/* Variables and functions */
 int LOOPBACK_IFINDEX ; 
 scalar_t__ netif_is_l3_master (TYPE_3__*) ; 
 struct rt6_info* skb_rt6_info (struct sk_buff const*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int icmp6_iif(const struct sk_buff *skb)
{
	int iif = skb->dev->ifindex;

	/* for local traffic to local address, skb dev is the loopback
	 * device. Check if there is a dst attached to the skb and if so
	 * get the real device index. Same is needed for replies to a link
	 * local address on a device enslaved to an L3 master device
	 */
	if (unlikely(iif == LOOPBACK_IFINDEX || netif_is_l3_master(skb->dev))) {
		const struct rt6_info *rt6 = skb_rt6_info(skb);

		if (rt6)
			iif = rt6->rt6i_idev->dev->ifindex;
	}

	return iif;
}