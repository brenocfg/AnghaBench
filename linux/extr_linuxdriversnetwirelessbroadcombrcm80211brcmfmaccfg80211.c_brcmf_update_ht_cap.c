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
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  tx_params; int /*<<< orphan*/  rx_mask; } ;
struct TYPE_4__ {int ht_supported; TYPE_1__ mcs; int /*<<< orphan*/  ampdu_density; int /*<<< orphan*/  ampdu_factor; int /*<<< orphan*/  cap; } ;
struct ieee80211_supported_band {size_t band; TYPE_2__ ht_cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_HT_CAP_DSSSCCK40 ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_SGI_20 ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_SGI_40 ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_SUP_WIDTH_20_40 ; 
 int /*<<< orphan*/  IEEE80211_HT_MAX_AMPDU_64K ; 
 int /*<<< orphan*/  IEEE80211_HT_MCS_TX_DEFINED ; 
 int /*<<< orphan*/  IEEE80211_HT_MPDU_DENSITY_16 ; 
 int WLC_BW_40MHZ_BIT ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void brcmf_update_ht_cap(struct ieee80211_supported_band *band,
				u32 bw_cap[2], u32 nchain)
{
	band->ht_cap.ht_supported = true;
	if (bw_cap[band->band] & WLC_BW_40MHZ_BIT) {
		band->ht_cap.cap |= IEEE80211_HT_CAP_SGI_40;
		band->ht_cap.cap |= IEEE80211_HT_CAP_SUP_WIDTH_20_40;
	}
	band->ht_cap.cap |= IEEE80211_HT_CAP_SGI_20;
	band->ht_cap.cap |= IEEE80211_HT_CAP_DSSSCCK40;
	band->ht_cap.ampdu_factor = IEEE80211_HT_MAX_AMPDU_64K;
	band->ht_cap.ampdu_density = IEEE80211_HT_MPDU_DENSITY_16;
	memset(band->ht_cap.mcs.rx_mask, 0xff, nchain);
	band->ht_cap.mcs.tx_params = IEEE80211_HT_MCS_TX_DEFINED;
}