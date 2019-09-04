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
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_vif {scalar_t__ type; scalar_t__ drv_priv; } ;
struct ath10k_vif {TYPE_1__* ar; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ ath10k_mac_tdls_vif_stations_count (int /*<<< orphan*/ ,struct ieee80211_vif*) ; 

__attribute__((used)) static void ath10k_mac_tdls_vifs_count_iter(void *data, u8 *mac,
					    struct ieee80211_vif *vif)
{
	struct ath10k_vif *arvif = (void *)vif->drv_priv;
	int *num_tdls_vifs = data;

	if (vif->type != NL80211_IFTYPE_STATION)
		return;

	if (ath10k_mac_tdls_vif_stations_count(arvif->ar->hw, vif) > 0)
		(*num_tdls_vifs)++;
}