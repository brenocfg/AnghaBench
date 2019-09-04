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
struct usbnet {TYPE_1__* net; } ;
struct sk_buff {scalar_t__ len; int* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  h_dest; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 scalar_t__ ETH_HLEN ; 
 TYPE_2__* eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static int usbnet_cdc_zte_rx_fixup(struct usbnet *dev, struct sk_buff *skb)
{
	if (skb->len < ETH_HLEN || !(skb->data[0] & 0x02))
		return 1;

	skb_reset_mac_header(skb);
	ether_addr_copy(eth_hdr(skb)->h_dest, dev->net->dev_addr);

	return 1;
}