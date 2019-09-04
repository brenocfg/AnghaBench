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
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct wiphy {int dummy; } ;
struct wilc_vif {int dummy; } ;
struct wilc_priv {int cfg_scanning; int /*<<< orphan*/  dev; scalar_t__ rcvd_ch_cnt; struct cfg80211_scan_request* scan_req; } ;
struct hidden_network {int dummy; } ;
struct cfg80211_scan_request {int n_channels; int n_ssids; int /*<<< orphan*/  ie_len; scalar_t__ ie; TYPE_1__** channels; } ;
struct TYPE_2__ {int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTIVE_SCAN ; 
 int EBUSY ; 
 int ENOMEM ; 
 int MAX_NUM_SCANNED_NETWORKS ; 
 int /*<<< orphan*/  USER_SCAN ; 
 int /*<<< orphan*/  cfg_scan_result ; 
 int /*<<< orphan*/  ieee80211_frequency_to_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct wilc_vif* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_shadow_found () ; 
 int wilc_scan (struct wilc_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,struct hidden_network*) ; 
 scalar_t__ wilc_wfi_cfg_alloc_fill_ssid (struct cfg80211_scan_request*,struct hidden_network*) ; 
 struct wilc_priv* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int scan(struct wiphy *wiphy, struct cfg80211_scan_request *request)
{
	struct wilc_priv *priv = wiphy_priv(wiphy);
	struct wilc_vif *vif = netdev_priv(priv->dev);
	u32 i;
	int ret = 0;
	u8 scan_ch_list[MAX_NUM_SCANNED_NETWORKS];
	struct hidden_network hidden_ntwk;

	priv->scan_req = request;

	priv->rcvd_ch_cnt = 0;

	reset_shadow_found();

	priv->cfg_scanning = true;
	if (request->n_channels <= MAX_NUM_SCANNED_NETWORKS) {
		for (i = 0; i < request->n_channels; i++) {
			u16 freq = request->channels[i]->center_freq;

			scan_ch_list[i] = ieee80211_frequency_to_channel(freq);
		}

		if (request->n_ssids >= 1) {
			if (wilc_wfi_cfg_alloc_fill_ssid(request,
							 &hidden_ntwk))
				return -ENOMEM;

			ret = wilc_scan(vif, USER_SCAN, ACTIVE_SCAN,
					scan_ch_list,
					request->n_channels,
					(const u8 *)request->ie,
					request->ie_len, cfg_scan_result,
					(void *)priv, &hidden_ntwk);
		} else {
			ret = wilc_scan(vif, USER_SCAN, ACTIVE_SCAN,
					scan_ch_list,
					request->n_channels,
					(const u8 *)request->ie,
					request->ie_len, cfg_scan_result,
					(void *)priv, NULL);
		}
	} else {
		netdev_err(priv->dev, "Requested scanned channels over\n");
	}

	if (ret != 0)
		ret = -EBUSY;

	return ret;
}