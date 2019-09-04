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
struct sk_buff {scalar_t__ cb; } ;
struct phy_device {struct dp83640_private* priv; } ;
struct dp83640_skb_info {scalar_t__ tmo; } ;
struct dp83640_private {int hwts_tx_en; int /*<<< orphan*/  tx_queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_flags; } ;

/* Variables and functions */
#define  HWTSTAMP_TX_OFF 130 
#define  HWTSTAMP_TX_ON 129 
#define  HWTSTAMP_TX_ONESTEP_SYNC 128 
 int /*<<< orphan*/  SKBTX_IN_PROGRESS ; 
 scalar_t__ SKB_TIMESTAMP_TIMEOUT ; 
 int /*<<< orphan*/  is_sync (struct sk_buff*,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void dp83640_txtstamp(struct phy_device *phydev,
			     struct sk_buff *skb, int type)
{
	struct dp83640_skb_info *skb_info = (struct dp83640_skb_info *)skb->cb;
	struct dp83640_private *dp83640 = phydev->priv;

	switch (dp83640->hwts_tx_en) {

	case HWTSTAMP_TX_ONESTEP_SYNC:
		if (is_sync(skb, type)) {
			kfree_skb(skb);
			return;
		}
		/* fall through */
	case HWTSTAMP_TX_ON:
		skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
		skb_info->tmo = jiffies + SKB_TIMESTAMP_TIMEOUT;
		skb_queue_tail(&dp83640->tx_queue, skb);
		break;

	case HWTSTAMP_TX_OFF:
	default:
		kfree_skb(skb);
		break;
	}
}