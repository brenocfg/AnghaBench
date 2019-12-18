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
typedef  int u8 ;
struct sk_buff {int len; scalar_t__ head; } ;
struct net_device {int dummy; } ;
struct dsa_port {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ NET_IP_ALIGN ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 
 int /*<<< orphan*/  skb_copy_and_csum_dev (struct sk_buff*,int*) ; 
 scalar_t__ skb_network_header (struct sk_buff*) ; 
 int* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_zero (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_transport_header (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *trailer_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct dsa_port *dp = dsa_slave_to_port(dev);
	struct sk_buff *nskb;
	int padlen;
	u8 *trailer;

	/*
	 * We have to make sure that the trailer ends up as the very
	 * last 4 bytes of the packet.  This means that we have to pad
	 * the packet to the minimum ethernet frame size, if necessary,
	 * before adding the trailer.
	 */
	padlen = 0;
	if (skb->len < 60)
		padlen = 60 - skb->len;

	nskb = alloc_skb(NET_IP_ALIGN + skb->len + padlen + 4, GFP_ATOMIC);
	if (!nskb)
		return NULL;
	skb_reserve(nskb, NET_IP_ALIGN);

	skb_reset_mac_header(nskb);
	skb_set_network_header(nskb, skb_network_header(skb) - skb->head);
	skb_set_transport_header(nskb, skb_transport_header(skb) - skb->head);
	skb_copy_and_csum_dev(skb, skb_put(nskb, skb->len));
	consume_skb(skb);

	if (padlen) {
		skb_put_zero(nskb, padlen);
	}

	trailer = skb_put(nskb, 4);
	trailer[0] = 0x80;
	trailer[1] = 1 << dp->index;
	trailer[2] = 0x10;
	trailer[3] = 0x00;

	return nskb;
}