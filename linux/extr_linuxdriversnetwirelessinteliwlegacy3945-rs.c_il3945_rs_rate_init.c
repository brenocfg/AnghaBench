#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_11__ {int sta_supp_rates; } ;
struct TYPE_7__ {size_t bcast_id; } ;
struct il_priv {TYPE_6__* stations; TYPE_5__ _3945; TYPE_1__ hw_params; struct ieee80211_hw* hw; } ;
struct il3945_rs_sta {int last_txrate_idx; int /*<<< orphan*/ * win; scalar_t__ last_tx_packets; int /*<<< orphan*/  flush_time; void* last_flush; void* last_partial_flush; int /*<<< orphan*/  expected_tpt; int /*<<< orphan*/  start_rate; struct il_priv* il; } ;
struct il3945_sta_priv {struct il3945_rs_sta rs_sta; } ;
struct ieee80211_supported_band {int n_bitrates; size_t band; } ;
struct ieee80211_sta {int* supp_rates; scalar_t__ drv_priv; } ;
struct TYPE_10__ {TYPE_3__* chan; } ;
struct ieee80211_conf {TYPE_4__ chandef; } ;
struct ieee80211_hw {TYPE_2__* wiphy; struct ieee80211_conf conf; } ;
struct TYPE_12__ {int /*<<< orphan*/  used; } ;
struct TYPE_9__ {size_t band; } ;
struct TYPE_8__ {struct ieee80211_supported_band** bands; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_INFO (char*) ; 
 int IL_FIRST_OFDM_RATE ; 
 int /*<<< orphan*/  IL_STA_UCODE_INPROGRESS ; 
 size_t NL80211_BAND_5GHZ ; 
 int RATE_COUNT_3945 ; 
 int /*<<< orphan*/  RATE_FLUSH ; 
 int /*<<< orphan*/  RATE_INVALID ; 
 int /*<<< orphan*/  il3945_clear_win (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  il3945_expected_tpt_b ; 
 void* jiffies ; 

void
il3945_rs_rate_init(struct il_priv *il, struct ieee80211_sta *sta, u8 sta_id)
{
	struct ieee80211_hw *hw = il->hw;
	struct ieee80211_conf *conf = &il->hw->conf;
	struct il3945_sta_priv *psta;
	struct il3945_rs_sta *rs_sta;
	struct ieee80211_supported_band *sband;
	int i;

	D_INFO("enter\n");
	if (sta_id == il->hw_params.bcast_id)
		goto out;

	psta = (struct il3945_sta_priv *)sta->drv_priv;
	rs_sta = &psta->rs_sta;
	sband = hw->wiphy->bands[conf->chandef.chan->band];

	rs_sta->il = il;

	rs_sta->start_rate = RATE_INVALID;

	/* default to just 802.11b */
	rs_sta->expected_tpt = il3945_expected_tpt_b;

	rs_sta->last_partial_flush = jiffies;
	rs_sta->last_flush = jiffies;
	rs_sta->flush_time = RATE_FLUSH;
	rs_sta->last_tx_packets = 0;

	for (i = 0; i < RATE_COUNT_3945; i++)
		il3945_clear_win(&rs_sta->win[i]);

	/* TODO: what is a good starting rate for STA? About middle? Maybe not
	 * the lowest or the highest rate.. Could consider using RSSI from
	 * previous packets? Need to have IEEE 802.1X auth succeed immediately
	 * after assoc.. */

	for (i = sband->n_bitrates - 1; i >= 0; i--) {
		if (sta->supp_rates[sband->band] & (1 << i)) {
			rs_sta->last_txrate_idx = i;
			break;
		}
	}

	il->_3945.sta_supp_rates = sta->supp_rates[sband->band];
	/* For 5 GHz band it start at IL_FIRST_OFDM_RATE */
	if (sband->band == NL80211_BAND_5GHZ) {
		rs_sta->last_txrate_idx += IL_FIRST_OFDM_RATE;
		il->_3945.sta_supp_rates <<= IL_FIRST_OFDM_RATE;
	}

out:
	il->stations[sta_id].used &= ~IL_STA_UCODE_INPROGRESS;

	D_INFO("leave\n");
}