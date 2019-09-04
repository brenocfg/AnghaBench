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
struct ath6kl_vif {int /*<<< orphan*/  fw_vif_idx; TYPE_1__* ar; struct ath6kl_htcap* htcap; } ;
struct ath6kl_htcap {int ht_enable; int /*<<< orphan*/  ampdu_factor; int /*<<< orphan*/  cap_info; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_2__ {int /*<<< orphan*/  wmi; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_HT_MAX_AMPDU_16K ; 
 int NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  ath6kl_a_htcap ; 
 int /*<<< orphan*/  ath6kl_g_htcap ; 
 int ath6kl_wmi_set_htcap_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct ath6kl_htcap*) ; 
 int /*<<< orphan*/  memset (struct ath6kl_htcap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ath6kl_set_htcap(struct ath6kl_vif *vif, enum nl80211_band band,
			    bool ht_enable)
{
	struct ath6kl_htcap *htcap = &vif->htcap[band];

	if (htcap->ht_enable == ht_enable)
		return 0;

	if (ht_enable) {
		/* Set default ht capabilities */
		htcap->ht_enable = true;
		htcap->cap_info = (band == NL80211_BAND_2GHZ) ?
				   ath6kl_g_htcap : ath6kl_a_htcap;
		htcap->ampdu_factor = IEEE80211_HT_MAX_AMPDU_16K;
	} else /* Disable ht */
		memset(htcap, 0, sizeof(*htcap));

	return ath6kl_wmi_set_htcap_cmd(vif->ar->wmi, vif->fw_vif_idx,
					band, htcap);
}