#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_supported_band {struct ieee80211_rate* bitrates; } ;
struct ieee80211_rx_status {size_t band; size_t rate_idx; int /*<<< orphan*/  encoding; } ;
struct ieee80211_rx_data {TYPE_7__* sdata; int /*<<< orphan*/  skb; TYPE_5__* sta; TYPE_3__* local; } ;
struct ieee80211_rate {int dummy; } ;
typedef  int ieee80211_rx_result ;
struct TYPE_14__ {TYPE_6__* local; } ;
struct TYPE_13__ {int /*<<< orphan*/  rx_handlers_queued; int /*<<< orphan*/  rx_handlers_drop; } ;
struct TYPE_11__ {int /*<<< orphan*/  dropped; } ;
struct TYPE_12__ {TYPE_4__ rx_stats; } ;
struct TYPE_9__ {TYPE_1__* wiphy; } ;
struct TYPE_10__ {TYPE_2__ hw; } ;
struct TYPE_8__ {struct ieee80211_supported_band** bands; } ;

/* Variables and functions */
 int /*<<< orphan*/  I802_DEBUG_INC (int /*<<< orphan*/ ) ; 
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (int /*<<< orphan*/ ) ; 
#define  RX_CONTINUE 131 
#define  RX_DROP_MONITOR 130 
#define  RX_DROP_UNUSABLE 129 
 int /*<<< orphan*/  RX_ENC_LEGACY ; 
#define  RX_QUEUED 128 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_rx_cooked_monitor (struct ieee80211_rx_data*,struct ieee80211_rate*) ; 

__attribute__((used)) static void ieee80211_rx_handlers_result(struct ieee80211_rx_data *rx,
					 ieee80211_rx_result res)
{
	switch (res) {
	case RX_DROP_MONITOR:
		I802_DEBUG_INC(rx->sdata->local->rx_handlers_drop);
		if (rx->sta)
			rx->sta->rx_stats.dropped++;
		/* fall through */
	case RX_CONTINUE: {
		struct ieee80211_rate *rate = NULL;
		struct ieee80211_supported_band *sband;
		struct ieee80211_rx_status *status;

		status = IEEE80211_SKB_RXCB((rx->skb));

		sband = rx->local->hw.wiphy->bands[status->band];
		if (status->encoding == RX_ENC_LEGACY)
			rate = &sband->bitrates[status->rate_idx];

		ieee80211_rx_cooked_monitor(rx, rate);
		break;
		}
	case RX_DROP_UNUSABLE:
		I802_DEBUG_INC(rx->sdata->local->rx_handlers_drop);
		if (rx->sta)
			rx->sta->rx_stats.dropped++;
		dev_kfree_skb(rx->skb);
		break;
	case RX_QUEUED:
		I802_DEBUG_INC(rx->sdata->local->rx_handlers_queued);
		break;
	}
}