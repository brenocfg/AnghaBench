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
struct sk_buff {int dummy; } ;
struct ieee80211_rx_status {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_msdus_q; } ;
struct ath10k {TYPE_1__ htt; } ;

/* Variables and functions */
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static void ath10k_htt_rx_h_queue_msdu(struct ath10k *ar,
				       struct ieee80211_rx_status *rx_status,
				       struct sk_buff *skb)
{
	struct ieee80211_rx_status *status;

	status = IEEE80211_SKB_RXCB(skb);
	*status = *rx_status;

	skb_queue_tail(&ar->htt.rx_msdus_q, skb);
}