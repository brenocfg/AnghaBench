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
struct TYPE_4__ {int chains; scalar_t__* chain_signal; scalar_t__ last_rssi; } ;
struct iwl_lq_sta {TYPE_2__ pers; } ;
struct TYPE_3__ {struct iwl_lq_sta rs_drv; } ;
struct iwl_mvm_sta {TYPE_1__ lq_sta; } ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_rx_status {int chains; scalar_t__* chain_signal; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int BIT (int) ; 
 scalar_t__ S8_MIN ; 

void rs_update_last_rssi(struct iwl_mvm *mvm,
			 struct iwl_mvm_sta *mvmsta,
			 struct ieee80211_rx_status *rx_status)
{
	struct iwl_lq_sta *lq_sta = &mvmsta->lq_sta.rs_drv;
	int i;

	lq_sta->pers.chains = rx_status->chains;
	lq_sta->pers.chain_signal[0] = rx_status->chain_signal[0];
	lq_sta->pers.chain_signal[1] = rx_status->chain_signal[1];
	lq_sta->pers.chain_signal[2] = rx_status->chain_signal[2];
	lq_sta->pers.last_rssi = S8_MIN;

	for (i = 0; i < ARRAY_SIZE(lq_sta->pers.chain_signal); i++) {
		if (!(lq_sta->pers.chains & BIT(i)))
			continue;

		if (lq_sta->pers.chain_signal[i] > lq_sta->pers.last_rssi)
			lq_sta->pers.last_rssi = lq_sta->pers.chain_signal[i];
	}
}