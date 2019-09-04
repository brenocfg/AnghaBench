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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct ieee80211_tx_info {int flags; } ;
struct ath10k_vif {int /*<<< orphan*/  vdev_id; } ;
struct ath10k_skb_cb {TYPE_2__* vif; } ;
struct TYPE_3__ {int /*<<< orphan*/  vdev_id; } ;
struct ath10k {int /*<<< orphan*/  monitor_vdev_id; scalar_t__ monitor_started; TYPE_1__ scan; } ;
struct TYPE_4__ {scalar_t__ drv_priv; } ;

/* Variables and functions */
 struct ath10k_skb_cb* ATH10K_SKB_CB (struct sk_buff*) ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_TX_OFFCHAN ; 

__attribute__((used)) static u8 ath10k_htt_tx_get_vdev_id(struct ath10k *ar, struct sk_buff *skb)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct ath10k_skb_cb *cb = ATH10K_SKB_CB(skb);
	struct ath10k_vif *arvif;

	if (info->flags & IEEE80211_TX_CTL_TX_OFFCHAN) {
		return ar->scan.vdev_id;
	} else if (cb->vif) {
		arvif = (void *)cb->vif->drv_priv;
		return arvif->vdev_id;
	} else if (ar->monitor_started) {
		return ar->monitor_vdev_id;
	} else {
		return 0;
	}
}