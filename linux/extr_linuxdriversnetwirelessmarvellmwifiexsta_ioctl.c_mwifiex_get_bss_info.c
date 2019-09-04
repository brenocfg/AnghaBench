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
struct TYPE_4__ {scalar_t__ wep_enabled; } ;
struct mwifiex_bssdescriptor {int /*<<< orphan*/  channel; int /*<<< orphan*/  mac_address; int /*<<< orphan*/  ssid; } ;
struct TYPE_3__ {struct mwifiex_bssdescriptor bss_descriptor; } ;
struct mwifiex_private {TYPE_2__ sec_info; int /*<<< orphan*/  bcn_nf_last; int /*<<< orphan*/  adhoc_state; int /*<<< orphan*/  min_tx_power_level; int /*<<< orphan*/  max_tx_power_level; int /*<<< orphan*/  media_connected; int /*<<< orphan*/  bss_mode; TYPE_1__ curr_bss_params; struct mwifiex_adapter* adapter; } ;
struct mwifiex_bss_info {int wep_status; int /*<<< orphan*/  is_deep_sleep; int /*<<< orphan*/  is_hs_configured; int /*<<< orphan*/  bcn_nf_last; int /*<<< orphan*/  adhoc_state; int /*<<< orphan*/  min_power_level; int /*<<< orphan*/  max_power_level; int /*<<< orphan*/  media_connected; int /*<<< orphan*/ * country_code; int /*<<< orphan*/  bss_chan; int /*<<< orphan*/  bssid; int /*<<< orphan*/  ssid; int /*<<< orphan*/  bss_mode; } ;
struct mwifiex_adapter {int /*<<< orphan*/  is_deep_sleep; int /*<<< orphan*/  work_flags; int /*<<< orphan*/ * country_code; } ;
struct cfg80211_ssid {int dummy; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int IEEE80211_COUNTRY_STRING_LEN ; 
 int /*<<< orphan*/  MWIFIEX_IS_HS_CONFIGURED ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int mwifiex_get_bss_info(struct mwifiex_private *priv,
			 struct mwifiex_bss_info *info)
{
	struct mwifiex_adapter *adapter = priv->adapter;
	struct mwifiex_bssdescriptor *bss_desc;

	if (!info)
		return -1;

	bss_desc = &priv->curr_bss_params.bss_descriptor;

	info->bss_mode = priv->bss_mode;

	memcpy(&info->ssid, &bss_desc->ssid, sizeof(struct cfg80211_ssid));

	memcpy(&info->bssid, &bss_desc->mac_address, ETH_ALEN);

	info->bss_chan = bss_desc->channel;

	memcpy(info->country_code, adapter->country_code,
	       IEEE80211_COUNTRY_STRING_LEN);

	info->media_connected = priv->media_connected;

	info->max_power_level = priv->max_tx_power_level;
	info->min_power_level = priv->min_tx_power_level;

	info->adhoc_state = priv->adhoc_state;

	info->bcn_nf_last = priv->bcn_nf_last;

	if (priv->sec_info.wep_enabled)
		info->wep_status = true;
	else
		info->wep_status = false;

	info->is_hs_configured = test_bit(MWIFIEX_IS_HS_CONFIGURED,
					  &adapter->work_flags);
	info->is_deep_sleep = adapter->is_deep_sleep;

	return 0;
}