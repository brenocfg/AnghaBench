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
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct napi_struct {int dummy; } ;
struct mt76_dev {int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  hw; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_rx_napi (int /*<<< orphan*/ ,struct ieee80211_sta*,struct sk_buff*,struct napi_struct*) ; 
 scalar_t__ mt76_check_ccmp_pn (struct sk_buff*) ; 
 struct ieee80211_sta* mt76_rx_convert (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void mt76_rx_complete(struct mt76_dev *dev, struct sk_buff_head *frames,
		      struct napi_struct *napi)
{
	struct ieee80211_sta *sta;
	struct sk_buff *skb;

	spin_lock(&dev->rx_lock);
	while ((skb = __skb_dequeue(frames)) != NULL) {
		if (mt76_check_ccmp_pn(skb)) {
			dev_kfree_skb(skb);
			continue;
		}

		sta = mt76_rx_convert(skb);
		ieee80211_rx_napi(dev->hw, sta, skb, napi);
	}
	spin_unlock(&dev->rx_lock);
}