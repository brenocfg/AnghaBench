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
struct wl1251 {struct sk_buff** tx_frames; int /*<<< orphan*/  hw; int /*<<< orphan*/  tx_queue; } ;
struct sk_buff {int dummy; } ;
struct ieee80211_tx_info {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_TX ; 
 int FW_TX_CMPLT_BLOCK_SIZE ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_REQ_TX_STATUS ; 
 int /*<<< orphan*/  ieee80211_tx_status (int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*,struct sk_buff*) ; 

void wl1251_tx_flush(struct wl1251 *wl)
{
	int i;
	struct sk_buff *skb;
	struct ieee80211_tx_info *info;

	/* TX failure */
/* 	control->flags = 0; FIXME */

	while ((skb = skb_dequeue(&wl->tx_queue))) {
		info = IEEE80211_SKB_CB(skb);

		wl1251_debug(DEBUG_TX, "flushing skb 0x%p", skb);

		if (!(info->flags & IEEE80211_TX_CTL_REQ_TX_STATUS))
				continue;

		ieee80211_tx_status(wl->hw, skb);
	}

	for (i = 0; i < FW_TX_CMPLT_BLOCK_SIZE; i++)
		if (wl->tx_frames[i] != NULL) {
			skb = wl->tx_frames[i];
			info = IEEE80211_SKB_CB(skb);

			if (!(info->flags & IEEE80211_TX_CTL_REQ_TX_STATUS))
				continue;

			ieee80211_tx_status(wl->hw, skb);
			wl->tx_frames[i] = NULL;
		}
}