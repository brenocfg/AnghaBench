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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct ieee80211_supported_band {scalar_t__ band; } ;
struct ieee80211_bss_conf {int use_cts_prot; int use_short_preamble; int use_short_slot; } ;
struct TYPE_2__ {struct ieee80211_bss_conf bss_conf; } ;
struct ieee80211_sub_if_data {TYPE_1__ vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSS_CHANGED_ERP_CTS_PROT ; 
 int /*<<< orphan*/  BSS_CHANGED_ERP_PREAMBLE ; 
 int /*<<< orphan*/  BSS_CHANGED_ERP_SLOT ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 int WLAN_CAPABILITY_SHORT_PREAMBLE ; 
 int WLAN_CAPABILITY_SHORT_SLOT_TIME ; 
 int WLAN_ERP_BARKER_PREAMBLE ; 
 int WLAN_ERP_USE_PROTECTION ; 
 struct ieee80211_supported_band* ieee80211_get_sband (struct ieee80211_sub_if_data*) ; 

__attribute__((used)) static u32 ieee80211_handle_bss_capability(struct ieee80211_sub_if_data *sdata,
					   u16 capab, bool erp_valid, u8 erp)
{
	struct ieee80211_bss_conf *bss_conf = &sdata->vif.bss_conf;
	struct ieee80211_supported_band *sband;
	u32 changed = 0;
	bool use_protection;
	bool use_short_preamble;
	bool use_short_slot;

	sband = ieee80211_get_sband(sdata);
	if (!sband)
		return changed;

	if (erp_valid) {
		use_protection = (erp & WLAN_ERP_USE_PROTECTION) != 0;
		use_short_preamble = (erp & WLAN_ERP_BARKER_PREAMBLE) == 0;
	} else {
		use_protection = false;
		use_short_preamble = !!(capab & WLAN_CAPABILITY_SHORT_PREAMBLE);
	}

	use_short_slot = !!(capab & WLAN_CAPABILITY_SHORT_SLOT_TIME);
	if (sband->band == NL80211_BAND_5GHZ)
		use_short_slot = true;

	if (use_protection != bss_conf->use_cts_prot) {
		bss_conf->use_cts_prot = use_protection;
		changed |= BSS_CHANGED_ERP_CTS_PROT;
	}

	if (use_short_preamble != bss_conf->use_short_preamble) {
		bss_conf->use_short_preamble = use_short_preamble;
		changed |= BSS_CHANGED_ERP_PREAMBLE;
	}

	if (use_short_slot != bss_conf->use_short_slot) {
		bss_conf->use_short_slot = use_short_slot;
		changed |= BSS_CHANGED_ERP_SLOT;
	}

	return changed;
}