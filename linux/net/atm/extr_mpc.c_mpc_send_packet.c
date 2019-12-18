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
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct mpoa_client {int number_of_mps_macs; int /*<<< orphan*/  old_ops; scalar_t__ mps_macs; } ;
struct iphdr {int dummy; } ;
struct ethhdr {scalar_t__ h_proto; int /*<<< orphan*/  h_dest; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_2__ {int ihl; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  __netdev_start_xmit (int /*<<< orphan*/ ,struct sk_buff*,struct net_device*,int) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,scalar_t__) ; 
 struct mpoa_client* find_mpc_by_lec (struct net_device*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ send_via_shortcut (struct sk_buff*,struct mpoa_client*) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static netdev_tx_t mpc_send_packet(struct sk_buff *skb,
					 struct net_device *dev)
{
	struct mpoa_client *mpc;
	struct ethhdr *eth;
	int i = 0;

	mpc = find_mpc_by_lec(dev); /* this should NEVER fail */
	if (mpc == NULL) {
		pr_info("(%s) no MPC found\n", dev->name);
		goto non_ip;
	}

	eth = (struct ethhdr *)skb->data;
	if (eth->h_proto != htons(ETH_P_IP))
		goto non_ip; /* Multi-Protocol Over ATM :-) */

	/* Weed out funny packets (e.g., AF_PACKET or raw). */
	if (skb->len < ETH_HLEN + sizeof(struct iphdr))
		goto non_ip;
	skb_set_network_header(skb, ETH_HLEN);
	if (skb->len < ETH_HLEN + ip_hdr(skb)->ihl * 4 || ip_hdr(skb)->ihl < 5)
		goto non_ip;

	while (i < mpc->number_of_mps_macs) {
		if (ether_addr_equal(eth->h_dest, mpc->mps_macs + i * ETH_ALEN))
			if (send_via_shortcut(skb, mpc) == 0) /* try shortcut */
				return NETDEV_TX_OK;
		i++;
	}

non_ip:
	return __netdev_start_xmit(mpc->old_ops, skb, dev, false);
}