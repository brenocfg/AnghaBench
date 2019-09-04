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
typedef  void* u8 ;
typedef  void* u32 ;
struct wireless_dev {scalar_t__ iftype; } ;
struct wiphy {int dummy; } ;
struct wil6210_vif {void* pbss; void* hidden_ssid; void* channel; void* privacy; int /*<<< orphan*/  mid; } ;
struct wil6210_priv {int /*<<< orphan*/  mutex; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct cfg80211_beacon_data {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 scalar_t__ NL80211_IFTYPE_P2P_GO ; 
 int /*<<< orphan*/  WIL_DEFAULT_BUS_REQUEST_KBPS ; 
 int /*<<< orphan*/  WIL_MAX_BUS_REQUEST_KBPS ; 
 void* WMI_NETTYPE_P2P ; 
 int /*<<< orphan*/  __wil_down (struct wil6210_priv*) ; 
 int __wil_up (struct wil6210_priv*) ; 
 int _wil_cfg80211_set_ies (struct wil6210_vif*,struct cfg80211_beacon_data*) ; 
 int /*<<< orphan*/  fw_recovery_idle ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct wil6210_vif* ndev_to_vif (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  wil6210_bus_request (struct wil6210_priv*,int /*<<< orphan*/ ) ; 
 int wil_bcast_init (struct wil6210_vif*) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*) ; 
 int /*<<< orphan*/  wil_has_other_active_ifaces (struct wil6210_priv*,struct net_device*,int,int) ; 
 void* wil_iftype_nl2wmi (scalar_t__) ; 
 int /*<<< orphan*/  wil_set_recovery_state (struct wil6210_priv*,int /*<<< orphan*/ ) ; 
 struct wil6210_priv* wiphy_to_wil (struct wiphy*) ; 
 int wmi_pcp_start (struct wil6210_vif*,int,void*,void*,void*,void*) ; 
 int /*<<< orphan*/  wmi_pcp_stop (struct wil6210_vif*) ; 
 int wmi_set_ssid (struct wil6210_vif*,size_t,void* const*) ; 

__attribute__((used)) static int _wil_cfg80211_start_ap(struct wiphy *wiphy,
				  struct net_device *ndev,
				  const u8 *ssid, size_t ssid_len, u32 privacy,
				  int bi, u8 chan,
				  struct cfg80211_beacon_data *bcon,
				  u8 hidden_ssid, u32 pbss)
{
	struct wil6210_priv *wil = wiphy_to_wil(wiphy);
	struct wil6210_vif *vif = ndev_to_vif(ndev);
	int rc;
	struct wireless_dev *wdev = ndev->ieee80211_ptr;
	u8 wmi_nettype = wil_iftype_nl2wmi(wdev->iftype);
	u8 is_go = (wdev->iftype == NL80211_IFTYPE_P2P_GO);

	if (pbss)
		wmi_nettype = WMI_NETTYPE_P2P;

	wil_dbg_misc(wil, "start_ap: mid=%d, is_go=%d\n", vif->mid, is_go);
	if (is_go && !pbss) {
		wil_err(wil, "P2P GO must be in PBSS\n");
		return -ENOTSUPP;
	}

	wil_set_recovery_state(wil, fw_recovery_idle);

	mutex_lock(&wil->mutex);

	if (!wil_has_other_active_ifaces(wil, ndev, true, false)) {
		__wil_down(wil);
		rc = __wil_up(wil);
		if (rc)
			goto out;
	}

	rc = wmi_set_ssid(vif, ssid_len, ssid);
	if (rc)
		goto out;

	rc = _wil_cfg80211_set_ies(vif, bcon);
	if (rc)
		goto out;

	vif->privacy = privacy;
	vif->channel = chan;
	vif->hidden_ssid = hidden_ssid;
	vif->pbss = pbss;

	netif_carrier_on(ndev);
	if (!wil_has_other_active_ifaces(wil, ndev, false, true))
		wil6210_bus_request(wil, WIL_MAX_BUS_REQUEST_KBPS);

	rc = wmi_pcp_start(vif, bi, wmi_nettype, chan, hidden_ssid, is_go);
	if (rc)
		goto err_pcp_start;

	rc = wil_bcast_init(vif);
	if (rc)
		goto err_bcast;

	goto out; /* success */

err_bcast:
	wmi_pcp_stop(vif);
err_pcp_start:
	netif_carrier_off(ndev);
	if (!wil_has_other_active_ifaces(wil, ndev, false, true))
		wil6210_bus_request(wil, WIL_DEFAULT_BUS_REQUEST_KBPS);
out:
	mutex_unlock(&wil->mutex);
	return rc;
}