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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 

__attribute__((used)) static netdev_tx_t brcmf_net_p2p_start_xmit(struct sk_buff *skb,
					    struct net_device *ndev)
{
	if (skb)
		dev_kfree_skb_any(skb);

	return NETDEV_TX_OK;
}