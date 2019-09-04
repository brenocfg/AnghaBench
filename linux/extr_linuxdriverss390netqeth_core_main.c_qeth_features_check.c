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
struct sk_buff {unsigned int data; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;
struct TYPE_2__ {unsigned int gso_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETIF_F_SG ; 
 scalar_t__ SKB_DATA_ALIGN (unsigned int) ; 
 scalar_t__ SKB_MAX_HEAD (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_needs_gso (struct sk_buff*,int /*<<< orphan*/ ) ; 
 unsigned int skb_headroom (struct sk_buff*) ; 
 unsigned int skb_mac_header (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  vlan_features_check (struct sk_buff*,int /*<<< orphan*/ ) ; 

netdev_features_t qeth_features_check(struct sk_buff *skb,
				      struct net_device *dev,
				      netdev_features_t features)
{
	/* GSO segmentation builds skbs with
	 *	a (small) linear part for the headers, and
	 *	page frags for the data.
	 * Compared to a linear skb, the header-only part consumes an
	 * additional buffer element. This reduces buffer utilization, and
	 * hurts throughput. So compress small segments into one element.
	 */
	if (netif_needs_gso(skb, features)) {
		/* match skb_segment(): */
		unsigned int doffset = skb->data - skb_mac_header(skb);
		unsigned int hsize = skb_shinfo(skb)->gso_size;
		unsigned int hroom = skb_headroom(skb);

		/* linearize only if resulting skb allocations are order-0: */
		if (SKB_DATA_ALIGN(hroom + doffset + hsize) <= SKB_MAX_HEAD(0))
			features &= ~NETIF_F_SG;
	}

	return vlan_features_check(skb, features);
}