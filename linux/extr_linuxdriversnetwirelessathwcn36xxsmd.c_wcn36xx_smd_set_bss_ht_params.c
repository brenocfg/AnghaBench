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
struct wcn36xx_hal_config_bss_params {int ht_oper_mode; int lln_non_gf_coexist; scalar_t__ ht20_coexist; scalar_t__ dual_cts_protection; void* lsig_tx_op_protection_full_support; void* tx_channel_width_set; scalar_t__ ht; } ;
struct TYPE_3__ {int ht_operation_mode; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; } ;
struct TYPE_4__ {unsigned long cap; scalar_t__ ht_supported; } ;
struct ieee80211_sta {TYPE_2__ ht_cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_HT_CAP_LSIG_TXOP_PROT ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_SUP_WIDTH_20_40 ; 
 int IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT ; 
 void* is_cap_supported (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wcn36xx_smd_set_bss_ht_params(struct ieee80211_vif *vif,
		struct ieee80211_sta *sta,
		struct wcn36xx_hal_config_bss_params *bss_params)
{
	if (sta && sta->ht_cap.ht_supported) {
		unsigned long caps = sta->ht_cap.cap;
		bss_params->ht = sta->ht_cap.ht_supported;
		bss_params->tx_channel_width_set = is_cap_supported(caps,
			IEEE80211_HT_CAP_SUP_WIDTH_20_40);
		bss_params->lsig_tx_op_protection_full_support =
			is_cap_supported(caps,
					 IEEE80211_HT_CAP_LSIG_TXOP_PROT);

		bss_params->ht_oper_mode = vif->bss_conf.ht_operation_mode;
		bss_params->lln_non_gf_coexist =
			!!(vif->bss_conf.ht_operation_mode &
			   IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT);
		/* IEEE80211_HT_STBC_PARAM_DUAL_CTS_PROT */
		bss_params->dual_cts_protection = 0;
		/* IEEE80211_HT_OP_MODE_PROTECTION_20MHZ */
		bss_params->ht20_coexist = 0;
	}
}