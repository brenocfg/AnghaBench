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
struct sk_buff {int dummy; } ;
struct net_device {scalar_t__ type; } ;
struct TYPE_2__ {scalar_t__ h_proto; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 TYPE_1__* eth_hdr (struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int likely (int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool packet_extra_vlan_len_allowed(const struct net_device *dev,
					  struct sk_buff *skb)
{
	/* Earlier code assumed this would be a VLAN pkt, double-check
	 * this now that we have the actual packet in hand. We can only
	 * do this check on Ethernet devices.
	 */
	if (unlikely(dev->type != ARPHRD_ETHER))
		return false;

	skb_reset_mac_header(skb);
	return likely(eth_hdr(skb)->h_proto == htons(ETH_P_8021Q));
}