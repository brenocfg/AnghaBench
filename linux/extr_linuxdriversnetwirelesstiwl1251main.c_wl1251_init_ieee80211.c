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
typedef  int u8 ;
struct wl1251 {scalar_t__ mac_addr; scalar_t__ use_eeprom; int /*<<< orphan*/ * nvs; TYPE_2__* hw; } ;
struct tx_double_buffer_desc {int dummy; } ;
struct TYPE_4__ {int queues; TYPE_1__* wiphy; scalar_t__ extra_tx_headroom; } ;
struct TYPE_3__ {int interface_modes; int max_scan_ssids; int /*<<< orphan*/ ** bands; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 size_t NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  SIGNAL_DBM ; 
 int /*<<< orphan*/  SUPPORTS_PS ; 
 scalar_t__ WL1251_TKIP_IV_SPACE ; 
 int /*<<< orphan*/  get_random_bytes (scalar_t__,int) ; 
 int /*<<< orphan*/  ieee80211_hw_set (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int const*,int) ; 
 int /*<<< orphan*/  wl1251_band_2ghz ; 
 int /*<<< orphan*/  wl1251_debugfs_init (struct wl1251*) ; 
 int wl1251_fetch_nvs (struct wl1251*) ; 
 int /*<<< orphan*/  wl1251_notice (char*) ; 
 int wl1251_read_eeprom_mac (struct wl1251*) ; 
 int wl1251_read_nvs_mac (struct wl1251*) ; 
 int wl1251_register_hw (struct wl1251*) ; 
 int /*<<< orphan*/  wl1251_warning (char*,...) ; 
 int /*<<< orphan*/  wl1251_write_nvs_mac (struct wl1251*) ; 

int wl1251_init_ieee80211(struct wl1251 *wl)
{
	int ret;

	/* The tx descriptor buffer and the TKIP space */
	wl->hw->extra_tx_headroom = sizeof(struct tx_double_buffer_desc)
		+ WL1251_TKIP_IV_SPACE;

	/* unit us */
	/* FIXME: find a proper value */

	ieee80211_hw_set(wl->hw, SIGNAL_DBM);
	ieee80211_hw_set(wl->hw, SUPPORTS_PS);

	wl->hw->wiphy->interface_modes = BIT(NL80211_IFTYPE_STATION) |
					 BIT(NL80211_IFTYPE_ADHOC);
	wl->hw->wiphy->max_scan_ssids = 1;
	wl->hw->wiphy->bands[NL80211_BAND_2GHZ] = &wl1251_band_2ghz;

	wl->hw->queues = 4;

	if (wl->nvs == NULL && !wl->use_eeprom) {
		ret = wl1251_fetch_nvs(wl);
		if (ret < 0)
			goto out;
	}

	if (wl->use_eeprom)
		ret = wl1251_read_eeprom_mac(wl);
	else
		ret = wl1251_read_nvs_mac(wl);

	if (ret == 0 && !is_valid_ether_addr(wl->mac_addr))
		ret = -EINVAL;

	if (ret < 0) {
		/*
		 * In case our MAC address is not correctly set,
		 * we use a random but Nokia MAC.
		 */
		static const u8 nokia_oui[3] = {0x00, 0x1f, 0xdf};
		memcpy(wl->mac_addr, nokia_oui, 3);
		get_random_bytes(wl->mac_addr + 3, 3);
		if (!wl->use_eeprom)
			wl1251_write_nvs_mac(wl);
		wl1251_warning("MAC address in eeprom or nvs data is not valid");
		wl1251_warning("Setting random MAC address: %pM", wl->mac_addr);
	}

	ret = wl1251_register_hw(wl);
	if (ret)
		goto out;

	wl1251_debugfs_init(wl);
	wl1251_notice("initialized");

	ret = 0;

out:
	return ret;
}