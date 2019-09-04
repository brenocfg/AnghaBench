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
struct usbnet {int /*<<< orphan*/  net; } ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct TYPE_2__ {int /*<<< orphan*/  h_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_HLEN ; 
 TYPE_1__* eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_is_nonlinear (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static int check_ethip_packet(struct sk_buff *skb, struct usbnet *dev)
{
	skb_reset_mac_header(skb); /* ethernet header */

	if (skb_is_nonlinear(skb)) {
		netdev_err(dev->net, "Non linear buffer-dropping\n");
		return 0;
	}

	if (!pskb_may_pull(skb, ETH_HLEN))
		return 0;
	skb->protocol = eth_hdr(skb)->h_proto;

	return 1;
}