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
struct sk_buff {scalar_t__ len; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct nic {TYPE_1__ stats; } ;

/* Variables and functions */
 scalar_t__ ETH_HLEN ; 
 int NET_RX_DROP ; 
 int netif_rx_ni (struct sk_buff*) ; 

__attribute__((used)) static int gdm_lte_rx(struct sk_buff *skb, struct nic *nic, int nic_type)
{
	int ret;

	ret = netif_rx_ni(skb);
	if (ret == NET_RX_DROP) {
		nic->stats.rx_dropped++;
	} else {
		nic->stats.rx_packets++;
		nic->stats.rx_bytes += skb->len + ETH_HLEN;
	}

	return 0;
}