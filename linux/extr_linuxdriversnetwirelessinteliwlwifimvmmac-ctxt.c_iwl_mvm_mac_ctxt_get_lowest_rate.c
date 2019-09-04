#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_vif {scalar_t__ p2p; } ;
struct ieee80211_tx_info {scalar_t__ band; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_FIRST_CCK_RATE ; 
 int /*<<< orphan*/  IWL_FIRST_OFDM_RATE ; 
 scalar_t__ NL80211_BAND_5GHZ ; 

__attribute__((used)) static u8 iwl_mvm_mac_ctxt_get_lowest_rate(struct ieee80211_tx_info *info,
					   struct ieee80211_vif *vif)
{
	u8 rate;

	if (info->band == NL80211_BAND_5GHZ || vif->p2p)
		rate = IWL_FIRST_OFDM_RATE;
	else
		rate = IWL_FIRST_CCK_RATE;

	return rate;
}