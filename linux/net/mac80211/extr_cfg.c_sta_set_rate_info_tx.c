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
typedef  int /*<<< orphan*/  u16 ;
struct sta_info {TYPE_2__* sdata; } ;
struct rate_info {size_t mcs; int /*<<< orphan*/  flags; int /*<<< orphan*/  bw; int /*<<< orphan*/  legacy; int /*<<< orphan*/  nss; } ;
struct ieee80211_tx_rate {int flags; size_t idx; } ;
struct ieee80211_supported_band {TYPE_1__* bitrates; } ;
struct TYPE_4__ {int /*<<< orphan*/  vif; } ;
struct TYPE_3__ {int /*<<< orphan*/  bitrate; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int IEEE80211_TX_RC_160_MHZ_WIDTH ; 
 int IEEE80211_TX_RC_40_MHZ_WIDTH ; 
 int IEEE80211_TX_RC_80_MHZ_WIDTH ; 
 int IEEE80211_TX_RC_MCS ; 
 int IEEE80211_TX_RC_SHORT_GI ; 
 int IEEE80211_TX_RC_VHT_MCS ; 
 int /*<<< orphan*/  RATE_INFO_BW_160 ; 
 int /*<<< orphan*/  RATE_INFO_BW_20 ; 
 int /*<<< orphan*/  RATE_INFO_BW_40 ; 
 int /*<<< orphan*/  RATE_INFO_BW_80 ; 
 int /*<<< orphan*/  RATE_INFO_FLAGS_MCS ; 
 int /*<<< orphan*/  RATE_INFO_FLAGS_SHORT_GI ; 
 int /*<<< orphan*/  RATE_INFO_FLAGS_VHT_MCS ; 
 struct ieee80211_supported_band* ieee80211_get_sband (TYPE_2__*) ; 
 size_t ieee80211_rate_get_vht_mcs (struct ieee80211_tx_rate const*) ; 
 int /*<<< orphan*/  ieee80211_rate_get_vht_nss (struct ieee80211_tx_rate const*) ; 
 int ieee80211_vif_get_shift (int /*<<< orphan*/ *) ; 

void sta_set_rate_info_tx(struct sta_info *sta,
			  const struct ieee80211_tx_rate *rate,
			  struct rate_info *rinfo)
{
	rinfo->flags = 0;
	if (rate->flags & IEEE80211_TX_RC_MCS) {
		rinfo->flags |= RATE_INFO_FLAGS_MCS;
		rinfo->mcs = rate->idx;
	} else if (rate->flags & IEEE80211_TX_RC_VHT_MCS) {
		rinfo->flags |= RATE_INFO_FLAGS_VHT_MCS;
		rinfo->mcs = ieee80211_rate_get_vht_mcs(rate);
		rinfo->nss = ieee80211_rate_get_vht_nss(rate);
	} else {
		struct ieee80211_supported_band *sband;
		int shift = ieee80211_vif_get_shift(&sta->sdata->vif);
		u16 brate;

		sband = ieee80211_get_sband(sta->sdata);
		if (sband) {
			brate = sband->bitrates[rate->idx].bitrate;
			rinfo->legacy = DIV_ROUND_UP(brate, 1 << shift);
		}
	}
	if (rate->flags & IEEE80211_TX_RC_40_MHZ_WIDTH)
		rinfo->bw = RATE_INFO_BW_40;
	else if (rate->flags & IEEE80211_TX_RC_80_MHZ_WIDTH)
		rinfo->bw = RATE_INFO_BW_80;
	else if (rate->flags & IEEE80211_TX_RC_160_MHZ_WIDTH)
		rinfo->bw = RATE_INFO_BW_160;
	else
		rinfo->bw = RATE_INFO_BW_20;
	if (rate->flags & IEEE80211_TX_RC_SHORT_GI)
		rinfo->flags |= RATE_INFO_FLAGS_SHORT_GI;
}