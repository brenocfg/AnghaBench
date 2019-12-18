#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_5__ {int /*<<< orphan*/  tx_mcs_map; } ;
struct TYPE_6__ {TYPE_1__ vht_mcs; scalar_t__ vht_supported; } ;
struct TYPE_8__ {int tx_params; scalar_t__* rx_mask; } ;
struct ieee80211_sta_ht_cap {TYPE_4__ mcs; int /*<<< orphan*/  ht_supported; } ;
struct TYPE_7__ {TYPE_2__ vht_cap; struct ieee80211_sta_ht_cap ht_cap; } ;
struct sta_info {TYPE_3__ sta; } ;

/* Variables and functions */
 int IEEE80211_HT_MCS_TX_MAX_STREAMS_MASK ; 
 int IEEE80211_HT_MCS_TX_MAX_STREAMS_SHIFT ; 
 int IEEE80211_HT_MCS_TX_RX_DIFF ; 
 int IEEE80211_VHT_MCS_NOT_SUPPORTED ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

u8 sta_info_tx_streams(struct sta_info *sta)
{
	struct ieee80211_sta_ht_cap *ht_cap = &sta->sta.ht_cap;
	u8 rx_streams;

	if (!sta->sta.ht_cap.ht_supported)
		return 1;

	if (sta->sta.vht_cap.vht_supported) {
		int i;
		u16 tx_mcs_map =
			le16_to_cpu(sta->sta.vht_cap.vht_mcs.tx_mcs_map);

		for (i = 7; i >= 0; i--)
			if ((tx_mcs_map & (0x3 << (i * 2))) !=
			    IEEE80211_VHT_MCS_NOT_SUPPORTED)
				return i + 1;
	}

	if (ht_cap->mcs.rx_mask[3])
		rx_streams = 4;
	else if (ht_cap->mcs.rx_mask[2])
		rx_streams = 3;
	else if (ht_cap->mcs.rx_mask[1])
		rx_streams = 2;
	else
		rx_streams = 1;

	if (!(ht_cap->mcs.tx_params & IEEE80211_HT_MCS_TX_RX_DIFF))
		return rx_streams;

	return ((ht_cap->mcs.tx_params & IEEE80211_HT_MCS_TX_MAX_STREAMS_MASK)
			>> IEEE80211_HT_MCS_TX_MAX_STREAMS_SHIFT) + 1;
}