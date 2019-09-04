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
struct wireless_dev {int /*<<< orphan*/  address; int /*<<< orphan*/  iftype; } ;
struct wiphy {int dummy; } ;
struct wil6210_vif {scalar_t__ mid; } ;
struct wil6210_priv {struct wireless_dev* p2p_wdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NL80211_IFTYPE_P2P_DEVICE ; 
 struct wil6210_vif* wdev_to_vif (struct wil6210_priv*,struct wireless_dev*) ; 
 int /*<<< orphan*/  wil_cfg80211_stop_p2p_device (struct wiphy*,struct wireless_dev*) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*,...) ; 
 int /*<<< orphan*/  wil_info (struct wil6210_priv*,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_p2p_wdev_free (struct wil6210_priv*) ; 
 int wil_vif_prepare_stop (struct wil6210_vif*) ; 
 int /*<<< orphan*/  wil_vif_remove (struct wil6210_priv*,scalar_t__) ; 
 struct wil6210_priv* wiphy_to_wil (struct wiphy*) ; 

__attribute__((used)) static int wil_cfg80211_del_iface(struct wiphy *wiphy,
				  struct wireless_dev *wdev)
{
	struct wil6210_priv *wil = wiphy_to_wil(wiphy);
	struct wil6210_vif *vif = wdev_to_vif(wil, wdev);
	int rc;

	wil_dbg_misc(wil, "del_iface\n");

	if (wdev->iftype == NL80211_IFTYPE_P2P_DEVICE) {
		if (wdev != wil->p2p_wdev) {
			wil_err(wil, "delete of incorrect interface 0x%p\n",
				wdev);
			return -EINVAL;
		}

		wil_cfg80211_stop_p2p_device(wiphy, wdev);
		wil_p2p_wdev_free(wil);
		return 0;
	}

	if (vif->mid == 0) {
		wil_err(wil, "cannot remove the main interface\n");
		return -EINVAL;
	}

	rc = wil_vif_prepare_stop(vif);
	if (rc)
		goto out;

	wil_info(wil, "deleted VIF, mid %d iftype %d MAC %pM\n",
		 vif->mid, wdev->iftype, wdev->address);

	wil_vif_remove(wil, vif->mid);
out:
	return rc;
}