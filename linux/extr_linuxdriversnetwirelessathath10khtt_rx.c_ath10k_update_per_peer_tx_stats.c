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
typedef  int u8 ;
struct rate_info {scalar_t__ flags; int nss; int mcs; int /*<<< orphan*/  bw; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct TYPE_2__ {int legacy; int mcs; int nss; int /*<<< orphan*/  bw; int /*<<< orphan*/  flags; } ;
struct ath10k_sta {TYPE_1__ txrate; } ;
struct ath10k_per_peer_tx_stats {int /*<<< orphan*/  ratecode; int /*<<< orphan*/  flags; } ;
struct ath10k {int /*<<< orphan*/  data_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_HW_BW (int /*<<< orphan*/ ) ; 
 int ATH10K_HW_GI (int /*<<< orphan*/ ) ; 
 int ATH10K_HW_LEGACY_RATE (int /*<<< orphan*/ ) ; 
 int ATH10K_HW_MCS_RATE (int /*<<< orphan*/ ) ; 
 int ATH10K_HW_NSS (int /*<<< orphan*/ ) ; 
 scalar_t__ ATH10K_HW_PREAMBLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RATE_INFO_FLAGS_MCS ; 
 int /*<<< orphan*/  RATE_INFO_FLAGS_SHORT_GI ; 
 int /*<<< orphan*/  RATE_INFO_FLAGS_VHT_MCS ; 
 scalar_t__ WMI_RATE_PREAMBLE_CCK ; 
 scalar_t__ WMI_RATE_PREAMBLE_HT ; 
 scalar_t__ WMI_RATE_PREAMBLE_OFDM ; 
 scalar_t__ WMI_RATE_PREAMBLE_VHT ; 
 int /*<<< orphan*/  ath10k_bw_to_mac80211_bw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int,...) ; 
 int /*<<< orphan*/  is_valid_legacy_rate (int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ath10k_update_per_peer_tx_stats(struct ath10k *ar,
				struct ieee80211_sta *sta,
				struct ath10k_per_peer_tx_stats *peer_stats)
{
	struct ath10k_sta *arsta = (struct ath10k_sta *)sta->drv_priv;
	u8 rate = 0, sgi;
	struct rate_info txrate;

	lockdep_assert_held(&ar->data_lock);

	txrate.flags = ATH10K_HW_PREAMBLE(peer_stats->ratecode);
	txrate.bw = ATH10K_HW_BW(peer_stats->flags);
	txrate.nss = ATH10K_HW_NSS(peer_stats->ratecode);
	txrate.mcs = ATH10K_HW_MCS_RATE(peer_stats->ratecode);
	sgi = ATH10K_HW_GI(peer_stats->flags);

	if (txrate.flags == WMI_RATE_PREAMBLE_VHT && txrate.mcs > 9) {
		ath10k_warn(ar, "Invalid VHT mcs %hhd peer stats",  txrate.mcs);
		return;
	}

	if (txrate.flags == WMI_RATE_PREAMBLE_HT &&
	    (txrate.mcs > 7 || txrate.nss < 1)) {
		ath10k_warn(ar, "Invalid HT mcs %hhd nss %hhd peer stats",
			    txrate.mcs, txrate.nss);
		return;
	}

	memset(&arsta->txrate, 0, sizeof(arsta->txrate));

	if (txrate.flags == WMI_RATE_PREAMBLE_CCK ||
	    txrate.flags == WMI_RATE_PREAMBLE_OFDM) {
		rate = ATH10K_HW_LEGACY_RATE(peer_stats->ratecode);

		if (!is_valid_legacy_rate(rate)) {
			ath10k_warn(ar, "Invalid legacy rate %hhd peer stats",
				    rate);
			return;
		}

		/* This is hacky, FW sends CCK rate 5.5Mbps as 6 */
		rate *= 10;
		if (rate == 60 && txrate.flags == WMI_RATE_PREAMBLE_CCK)
			rate = rate - 5;
		arsta->txrate.legacy = rate;
	} else if (txrate.flags == WMI_RATE_PREAMBLE_HT) {
		arsta->txrate.flags = RATE_INFO_FLAGS_MCS;
		arsta->txrate.mcs = txrate.mcs + 8 * (txrate.nss - 1);
	} else {
		arsta->txrate.flags = RATE_INFO_FLAGS_VHT_MCS;
		arsta->txrate.mcs = txrate.mcs;
	}

	if (sgi)
		arsta->txrate.flags |= RATE_INFO_FLAGS_SHORT_GI;

	arsta->txrate.nss = txrate.nss;
	arsta->txrate.bw = ath10k_bw_to_mac80211_bw(txrate.bw);
}