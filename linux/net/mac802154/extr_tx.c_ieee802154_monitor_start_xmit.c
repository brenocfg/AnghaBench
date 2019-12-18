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
struct sk_buff {int /*<<< orphan*/  skb_iif; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct ieee802154_sub_if_data {int /*<<< orphan*/  local; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 struct ieee802154_sub_if_data* IEEE802154_DEV_TO_SUB_IF (struct net_device*) ; 
 int /*<<< orphan*/  ieee802154_tx (int /*<<< orphan*/ ,struct sk_buff*) ; 

netdev_tx_t
ieee802154_monitor_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);

	skb->skb_iif = dev->ifindex;

	return ieee802154_tx(sdata->local, skb);
}