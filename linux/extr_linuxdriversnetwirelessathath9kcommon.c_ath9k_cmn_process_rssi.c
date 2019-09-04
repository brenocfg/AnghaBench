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
struct ieee80211_rx_status {int chains; int* chain_signal; int signal; int /*<<< orphan*/  flag; } ;
struct ieee80211_hw {int dummy; } ;
struct ath_rx_status {int rs_rssi; int* rs_rssi_ctl; scalar_t__ is_mybeacon; scalar_t__ rs_moreaggr; } ;
struct TYPE_2__ {int avgbrssi; } ;
struct ath_hw {int rxchainmask; int noise; scalar_t__ opmode; TYPE_1__ stats; } ;
struct ath_common {int last_rssi; struct ath_hw* ah; } ;
typedef  int s8 ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int ATH9K_RSSI_BAD ; 
 int ATH_EP_RND (int,int /*<<< orphan*/ ) ; 
 int ATH_RSSI_DUMMY_MARKER ; 
 int /*<<< orphan*/  ATH_RSSI_EP_MULTIPLIER ; 
 int /*<<< orphan*/  ATH_RSSI_LPF (int,int) ; 
 int BIT (int) ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  RX_FLAG_NO_SIGNAL_VAL ; 
 scalar_t__ likely (int) ; 

void ath9k_cmn_process_rssi(struct ath_common *common,
			    struct ieee80211_hw *hw,
			    struct ath_rx_status *rx_stats,
			    struct ieee80211_rx_status *rxs)
{
	struct ath_hw *ah = common->ah;
	int last_rssi;
	int rssi = rx_stats->rs_rssi;
	int i, j;

	/*
	 * RSSI is not available for subframes in an A-MPDU.
	 */
	if (rx_stats->rs_moreaggr) {
		rxs->flag |= RX_FLAG_NO_SIGNAL_VAL;
		return;
	}

	/*
	 * Check if the RSSI for the last subframe in an A-MPDU
	 * or an unaggregated frame is valid.
	 */
	if (rx_stats->rs_rssi == ATH9K_RSSI_BAD) {
		rxs->flag |= RX_FLAG_NO_SIGNAL_VAL;
		return;
	}

	for (i = 0, j = 0; i < ARRAY_SIZE(rx_stats->rs_rssi_ctl); i++) {
		s8 rssi;

		if (!(ah->rxchainmask & BIT(i)))
			continue;

		rssi = rx_stats->rs_rssi_ctl[i];
		if (rssi != ATH9K_RSSI_BAD) {
		    rxs->chains |= BIT(j);
		    rxs->chain_signal[j] = ah->noise + rssi;
		}
		j++;
	}

	/*
	 * Update Beacon RSSI, this is used by ANI.
	 */
	if (rx_stats->is_mybeacon &&
	    ((ah->opmode == NL80211_IFTYPE_STATION) ||
	     (ah->opmode == NL80211_IFTYPE_ADHOC))) {
		ATH_RSSI_LPF(common->last_rssi, rx_stats->rs_rssi);
		last_rssi = common->last_rssi;

		if (likely(last_rssi != ATH_RSSI_DUMMY_MARKER))
			rssi = ATH_EP_RND(last_rssi, ATH_RSSI_EP_MULTIPLIER);
		if (rssi < 0)
			rssi = 0;

		ah->stats.avgbrssi = rssi;
	}

	rxs->signal = ah->noise + rx_stats->rs_rssi;
}