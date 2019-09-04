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
struct mwifiex_uap_bss_param {int /*<<< orphan*/  vht_cap; } ;
struct mwifiex_private {int ap_11ac_enabled; } ;
struct ieee80211_vht_cap {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tail_len; int /*<<< orphan*/  tail; } ;
struct cfg80211_ap_settings {TYPE_1__ beacon; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_VHT_CAPABILITY ; 
 int /*<<< orphan*/ * cfg80211_find_ie (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

void mwifiex_set_vht_params(struct mwifiex_private *priv,
			    struct mwifiex_uap_bss_param *bss_cfg,
			    struct cfg80211_ap_settings *params)
{
	const u8 *vht_ie;

	vht_ie = cfg80211_find_ie(WLAN_EID_VHT_CAPABILITY, params->beacon.tail,
				  params->beacon.tail_len);
	if (vht_ie) {
		memcpy(&bss_cfg->vht_cap, vht_ie + 2,
		       sizeof(struct ieee80211_vht_cap));
		priv->ap_11ac_enabled = 1;
	} else {
		priv->ap_11ac_enabled = 0;
	}

	return;
}