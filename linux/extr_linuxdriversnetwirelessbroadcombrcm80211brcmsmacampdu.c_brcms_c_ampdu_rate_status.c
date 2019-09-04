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
typedef  int /*<<< orphan*/  u8 ;
struct tx_status {int dummy; } ;
struct ieee80211_tx_rate {int idx; scalar_t__ count; } ;
struct TYPE_2__ {struct ieee80211_tx_rate* rates; } ;
struct ieee80211_tx_info {TYPE_1__ status; } ;
struct brcms_c_info {int dummy; } ;

/* Variables and functions */
 int IEEE80211_TX_MAX_RATES ; 

__attribute__((used)) static void
brcms_c_ampdu_rate_status(struct brcms_c_info *wlc,
			  struct ieee80211_tx_info *tx_info,
			  struct tx_status *txs, u8 mcs)
{
	struct ieee80211_tx_rate *txrate = tx_info->status.rates;
	int i;

	/* clear the rest of the rates */
	for (i = 2; i < IEEE80211_TX_MAX_RATES; i++) {
		txrate[i].idx = -1;
		txrate[i].count = 0;
	}
}