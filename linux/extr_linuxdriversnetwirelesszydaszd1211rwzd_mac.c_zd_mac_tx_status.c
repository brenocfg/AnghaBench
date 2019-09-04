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
struct tx_status {int retry; int /*<<< orphan*/  failure; } ;
struct tx_retry_rate {int count; int* rate; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ack_signal; TYPE_1__* rates; } ;
struct ieee80211_tx_info {TYPE_2__ status; int /*<<< orphan*/  flags; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_3__ {int idx; int count; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct tx_retry_rate*) ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_MAX_RATES ; 
 int /*<<< orphan*/  IEEE80211_TX_STAT_ACK ; 
 int /*<<< orphan*/  ZD_ASSERT (int) ; 
 int /*<<< orphan*/  ieee80211_tx_info_clear_status (struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  ieee80211_tx_status_irqsafe (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  zd_check_signal (struct ieee80211_hw*,int) ; 
 struct tx_retry_rate* zd_retry_rates ; 

__attribute__((used)) static void zd_mac_tx_status(struct ieee80211_hw *hw, struct sk_buff *skb,
		      int ackssi, struct tx_status *tx_status)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	int i;
	int success = 1, retry = 1;
	int first_idx;
	const struct tx_retry_rate *retries;

	ieee80211_tx_info_clear_status(info);

	if (tx_status) {
		success = !tx_status->failure;
		retry = tx_status->retry + success;
	}

	if (success) {
		/* success */
		info->flags |= IEEE80211_TX_STAT_ACK;
	} else {
		/* failure */
		info->flags &= ~IEEE80211_TX_STAT_ACK;
	}

	first_idx = info->status.rates[0].idx;
	ZD_ASSERT(0<=first_idx && first_idx<ARRAY_SIZE(zd_retry_rates));
	retries = &zd_retry_rates[first_idx];
	ZD_ASSERT(1 <= retry && retry <= retries->count);

	info->status.rates[0].idx = retries->rate[0];
	info->status.rates[0].count = 1; // (retry > 1 ? 2 : 1);

	for (i=1; i<IEEE80211_TX_MAX_RATES-1 && i<retry; i++) {
		info->status.rates[i].idx = retries->rate[i];
		info->status.rates[i].count = 1; // ((i==retry-1) && success ? 1:2);
	}
	for (; i<IEEE80211_TX_MAX_RATES && i<retry; i++) {
		info->status.rates[i].idx = retries->rate[retry - 1];
		info->status.rates[i].count = 1; // (success ? 1:2);
	}
	if (i<IEEE80211_TX_MAX_RATES)
		info->status.rates[i].idx = -1; /* terminate */

	info->status.ack_signal = zd_check_signal(hw, ackssi);
	ieee80211_tx_status_irqsafe(hw, skb);
}