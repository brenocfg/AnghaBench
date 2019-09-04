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
struct wl1251 {int /*<<< orphan*/  mutex; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  hw; int /*<<< orphan*/  bss_type; struct ieee80211_vif* vif; } ;
struct ieee80211_vif {int driver_flags; int type; int /*<<< orphan*/  addr; } ;
struct ieee80211_hw {struct wl1251* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSS_TYPE_IBSS ; 
 int /*<<< orphan*/  BSS_TYPE_STA_BSS ; 
 int /*<<< orphan*/  DEBUG_MAC80211 ; 
 int EBUSY ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int IEEE80211_VIF_BEACON_FILTER ; 
 int IEEE80211_VIF_SUPPORTS_CQM_RSSI ; 
 int IEEE80211_VIF_SUPPORTS_UAPSD ; 
#define  NL80211_IFTYPE_ADHOC 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  SET_IEEE80211_PERM_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_equal_unaligned (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int wl1251_acx_station_id (struct wl1251*) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wl1251_op_add_interface(struct ieee80211_hw *hw,
				   struct ieee80211_vif *vif)
{
	struct wl1251 *wl = hw->priv;
	int ret = 0;

	vif->driver_flags |= IEEE80211_VIF_BEACON_FILTER |
			     IEEE80211_VIF_SUPPORTS_UAPSD |
			     IEEE80211_VIF_SUPPORTS_CQM_RSSI;

	wl1251_debug(DEBUG_MAC80211, "mac80211 add interface type %d mac %pM",
		     vif->type, vif->addr);

	mutex_lock(&wl->mutex);
	if (wl->vif) {
		ret = -EBUSY;
		goto out;
	}

	wl->vif = vif;

	switch (vif->type) {
	case NL80211_IFTYPE_STATION:
		wl->bss_type = BSS_TYPE_STA_BSS;
		break;
	case NL80211_IFTYPE_ADHOC:
		wl->bss_type = BSS_TYPE_IBSS;
		break;
	default:
		ret = -EOPNOTSUPP;
		goto out;
	}

	if (!ether_addr_equal_unaligned(wl->mac_addr, vif->addr)) {
		memcpy(wl->mac_addr, vif->addr, ETH_ALEN);
		SET_IEEE80211_PERM_ADDR(wl->hw, wl->mac_addr);
		ret = wl1251_acx_station_id(wl);
		if (ret < 0)
			goto out;
	}

out:
	mutex_unlock(&wl->mutex);
	return ret;
}