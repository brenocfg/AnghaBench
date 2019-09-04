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
struct sk_buff {scalar_t__ len; TYPE_2__* dev; int /*<<< orphan*/  protocol; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int netif_rx (struct sk_buff*) ; 

__attribute__((used)) static int lowpan_give_skb_to_device(struct sk_buff *skb)
{
	skb->protocol = htons(ETH_P_IPV6);
	skb->dev->stats.rx_packets++;
	skb->dev->stats.rx_bytes += skb->len;

	return netif_rx(skb);
}