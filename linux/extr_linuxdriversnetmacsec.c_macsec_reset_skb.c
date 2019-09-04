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
struct sk_buff {int /*<<< orphan*/  protocol; int /*<<< orphan*/  pkt_type; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PACKET_HOST ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  skb_reset_mac_len (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_transport_header_was_set (struct sk_buff*) ; 

__attribute__((used)) static void macsec_reset_skb(struct sk_buff *skb, struct net_device *dev)
{
	skb->pkt_type = PACKET_HOST;
	skb->protocol = eth_type_trans(skb, dev);

	skb_reset_network_header(skb);
	if (!skb_transport_header_was_set(skb))
		skb_reset_transport_header(skb);
	skb_reset_mac_len(skb);
}