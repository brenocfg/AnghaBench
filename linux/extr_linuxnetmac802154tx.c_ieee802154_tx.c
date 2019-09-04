#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; struct net_device* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_2__ stats; } ;
struct TYPE_7__ {int flags; } ;
struct ieee802154_local {int /*<<< orphan*/  tx_work; int /*<<< orphan*/  workqueue; struct sk_buff* tx_skb; TYPE_3__ hw; TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_5__ {scalar_t__ xmit_async; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IEEE802154_FCS_LEN ; 
 int IEEE802154_HW_TX_OMIT_CKSUM ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  crc_ccitt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int drv_xmit_async (struct ieee802154_local*,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee802154_stop_queue (TYPE_3__*) ; 
 int /*<<< orphan*/  ieee802154_wake_queue (TYPE_3__*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (struct sk_buff*) ; 
 int /*<<< orphan*/  put_unaligned_le16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_copy_expand (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 scalar_t__ skb_tailroom (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static netdev_tx_t
ieee802154_tx(struct ieee802154_local *local, struct sk_buff *skb)
{
	struct net_device *dev = skb->dev;
	int ret;

	if (!(local->hw.flags & IEEE802154_HW_TX_OMIT_CKSUM)) {
		struct sk_buff *nskb;
		u16 crc;

		if (unlikely(skb_tailroom(skb) < IEEE802154_FCS_LEN)) {
			nskb = skb_copy_expand(skb, 0, IEEE802154_FCS_LEN,
					       GFP_ATOMIC);
			if (likely(nskb)) {
				consume_skb(skb);
				skb = nskb;
			} else {
				goto err_tx;
			}
		}

		crc = crc_ccitt(0, skb->data, skb->len);
		put_unaligned_le16(crc, skb_put(skb, 2));
	}

	/* Stop the netif queue on each sub_if_data object. */
	ieee802154_stop_queue(&local->hw);

	/* async is priority, otherwise sync is fallback */
	if (local->ops->xmit_async) {
		ret = drv_xmit_async(local, skb);
		if (ret) {
			ieee802154_wake_queue(&local->hw);
			goto err_tx;
		}

		dev->stats.tx_packets++;
		dev->stats.tx_bytes += skb->len;
	} else {
		local->tx_skb = skb;
		queue_work(local->workqueue, &local->tx_work);
	}

	return NETDEV_TX_OK;

err_tx:
	kfree_skb(skb);
	return NETDEV_TX_OK;
}