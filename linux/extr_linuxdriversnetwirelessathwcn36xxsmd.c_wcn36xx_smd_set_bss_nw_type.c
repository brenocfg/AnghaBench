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
struct wcn36xx_hal_config_bss_params {int /*<<< orphan*/  nw_type; } ;
struct wcn36xx {int dummy; } ;
struct TYPE_2__ {scalar_t__ ht_supported; } ;
struct ieee80211_sta {int* supp_rates; TYPE_1__ ht_cap; } ;

/* Variables and functions */
 size_t NL80211_BAND_2GHZ ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 scalar_t__ WCN36XX_BAND (struct wcn36xx*) ; 
 int /*<<< orphan*/  WCN36XX_HAL_11A_NW_TYPE ; 
 int /*<<< orphan*/  WCN36XX_HAL_11B_NW_TYPE ; 
 int /*<<< orphan*/  WCN36XX_HAL_11G_NW_TYPE ; 
 int /*<<< orphan*/  WCN36XX_HAL_11N_NW_TYPE ; 

__attribute__((used)) static void wcn36xx_smd_set_bss_nw_type(struct wcn36xx *wcn,
		struct ieee80211_sta *sta,
		struct wcn36xx_hal_config_bss_params *bss_params)
{
	if (NL80211_BAND_5GHZ == WCN36XX_BAND(wcn))
		bss_params->nw_type = WCN36XX_HAL_11A_NW_TYPE;
	else if (sta && sta->ht_cap.ht_supported)
		bss_params->nw_type = WCN36XX_HAL_11N_NW_TYPE;
	else if (sta && (sta->supp_rates[NL80211_BAND_2GHZ] & 0x7f))
		bss_params->nw_type = WCN36XX_HAL_11G_NW_TYPE;
	else
		bss_params->nw_type = WCN36XX_HAL_11B_NW_TYPE;
}