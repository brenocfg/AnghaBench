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
struct sk_buff {int len; int /*<<< orphan*/  protocol; } ;
struct net_device {int hard_header_len; } ;

/* Variables and functions */
 scalar_t__ VLAN_HLEN ; 
 scalar_t__ eth_type_vlan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_vlan_tag_present (struct sk_buff const*) ; 

__attribute__((used)) static int packet_length(const struct sk_buff *skb,
			 struct net_device *dev)
{
	int length = skb->len - dev->hard_header_len;

	if (!skb_vlan_tag_present(skb) &&
	    eth_type_vlan(skb->protocol))
		length -= VLAN_HLEN;

	/* Don't subtract for multiple VLAN tags. Most (all?) drivers allow
	 * (ETH_LEN + VLAN_HLEN) in addition to the mtu value, but almost none
	 * account for 802.1ad. e.g. is_skb_forwardable().
	 */

	return length > 0 ? length : 0;
}