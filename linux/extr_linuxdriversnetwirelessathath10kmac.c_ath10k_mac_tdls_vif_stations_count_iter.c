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
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {scalar_t__ tdls; scalar_t__ drv_priv; } ;
struct ath10k_sta {TYPE_1__* arvif; } ;
struct ath10k_mac_tdls_iter_data {int /*<<< orphan*/  num_tdls_stations; struct ieee80211_vif* curr_vif; } ;
struct TYPE_2__ {struct ieee80211_vif* vif; } ;

/* Variables and functions */

__attribute__((used)) static void ath10k_mac_tdls_vif_stations_count_iter(void *data,
						    struct ieee80211_sta *sta)
{
	struct ath10k_mac_tdls_iter_data *iter_data = data;
	struct ath10k_sta *arsta = (struct ath10k_sta *)sta->drv_priv;
	struct ieee80211_vif *sta_vif = arsta->arvif->vif;

	if (sta->tdls && sta_vif == iter_data->curr_vif)
		iter_data->num_tdls_stations++;
}