#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_6__ {int /*<<< orphan*/  rx_highest; scalar_t__* rx_mask; } ;
struct TYPE_7__ {TYPE_1__ mcs; } ;
struct ieee80211_supported_band {TYPE_2__ ht_cap; } ;
struct ieee80211_hw {TYPE_5__* wiphy; struct brcms_info* priv; } ;
struct brcms_info {TYPE_3__* pub; struct brcms_c_info* wlc; } ;
struct brcms_c_info {TYPE_4__** bandstate; } ;
struct TYPE_10__ {struct ieee80211_supported_band** bands; } ;
struct TYPE_9__ {struct ieee80211_supported_band band; } ;
struct TYPE_8__ {int _nbands; } ;

/* Variables and functions */
 size_t BAND_2G_INDEX ; 
 size_t BAND_5G_INDEX ; 
 int EPERM ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 scalar_t__ PHY_TYPE_LCN ; 
 scalar_t__ PHY_TYPE_N ; 
 struct ieee80211_supported_band brcms_band_2GHz_nphy_template ; 
 struct ieee80211_supported_band brcms_band_5GHz_nphy_template ; 
 scalar_t__ brcms_c_get_phy_type (struct brcms_c_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 

__attribute__((used)) static int ieee_hw_rate_init(struct ieee80211_hw *hw)
{
	struct brcms_info *wl = hw->priv;
	struct brcms_c_info *wlc = wl->wlc;
	struct ieee80211_supported_band *band;
	int has_5g = 0;
	u16 phy_type;

	hw->wiphy->bands[NL80211_BAND_2GHZ] = NULL;
	hw->wiphy->bands[NL80211_BAND_5GHZ] = NULL;

	phy_type = brcms_c_get_phy_type(wl->wlc, 0);
	if (phy_type == PHY_TYPE_N || phy_type == PHY_TYPE_LCN) {
		band = &wlc->bandstate[BAND_2G_INDEX]->band;
		*band = brcms_band_2GHz_nphy_template;
		if (phy_type == PHY_TYPE_LCN) {
			/* Single stream */
			band->ht_cap.mcs.rx_mask[1] = 0;
			band->ht_cap.mcs.rx_highest = cpu_to_le16(72);
		}
		hw->wiphy->bands[NL80211_BAND_2GHZ] = band;
	} else {
		return -EPERM;
	}

	/* Assume all bands use the same phy.  True for 11n devices. */
	if (wl->pub->_nbands > 1) {
		has_5g++;
		if (phy_type == PHY_TYPE_N || phy_type == PHY_TYPE_LCN) {
			band = &wlc->bandstate[BAND_5G_INDEX]->band;
			*band = brcms_band_5GHz_nphy_template;
			hw->wiphy->bands[NL80211_BAND_5GHZ] = band;
		} else {
			return -EPERM;
		}
	}
	return 0;
}