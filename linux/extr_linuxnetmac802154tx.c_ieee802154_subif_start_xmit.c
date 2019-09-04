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
struct ieee802154_sub_if_data {int /*<<< orphan*/  local; int /*<<< orphan*/  sec; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 struct ieee802154_sub_if_data* IEEE802154_DEV_TO_SUB_IF (struct net_device*) ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  ieee802154_tx (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int mac802154_llsec_encrypt (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int) ; 

netdev_tx_t
ieee802154_subif_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	int rc;

	/* TODO we should move it to wpan_dev_hard_header and dev_hard_header
	 * functions. The reason is wireshark will show a mac header which is
	 * with security fields but the payload is not encrypted.
	 */
	rc = mac802154_llsec_encrypt(&sdata->sec, skb);
	if (rc) {
		netdev_warn(dev, "encryption failed: %i\n", rc);
		kfree_skb(skb);
		return NETDEV_TX_OK;
	}

	skb->skb_iif = dev->ifindex;

	return ieee802154_tx(sdata->local, skb);
}