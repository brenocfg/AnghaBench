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
struct wireless_dev {TYPE_1__* wiphy; } ;
struct lbs_private {int wiphy_registered; int /*<<< orphan*/  scan_work; int /*<<< orphan*/  dev; struct wireless_dev* wdev; } ;
struct TYPE_2__ {int max_scan_ssids; int interface_modes; int /*<<< orphan*/  reg_notifier; int /*<<< orphan*/  n_cipher_suites; int /*<<< orphan*/  cipher_suites; int /*<<< orphan*/ ** bands; int /*<<< orphan*/  signal_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFG80211_SIGNAL_TYPE_MBM ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_MESH_POINT ; 
 int /*<<< orphan*/  NL80211_IFTYPE_MONITOR ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  cipher_suites ; 
 int /*<<< orphan*/  lbs_band_2ghz ; 
 int /*<<< orphan*/  lbs_cfg_set_regulatory_hint (struct lbs_private*) ; 
 scalar_t__ lbs_mesh_activated (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_reg_notifier ; 
 scalar_t__ lbs_rtap_supported (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_scan_worker ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int register_netdev (int /*<<< orphan*/ ) ; 
 int wiphy_register (TYPE_1__*) ; 

int lbs_cfg_register(struct lbs_private *priv)
{
	struct wireless_dev *wdev = priv->wdev;
	int ret;

	wdev->wiphy->max_scan_ssids = 1;
	wdev->wiphy->signal_type = CFG80211_SIGNAL_TYPE_MBM;

	wdev->wiphy->interface_modes =
			BIT(NL80211_IFTYPE_STATION) |
			BIT(NL80211_IFTYPE_ADHOC);
	if (lbs_rtap_supported(priv))
		wdev->wiphy->interface_modes |= BIT(NL80211_IFTYPE_MONITOR);
	if (lbs_mesh_activated(priv))
		wdev->wiphy->interface_modes |= BIT(NL80211_IFTYPE_MESH_POINT);

	wdev->wiphy->bands[NL80211_BAND_2GHZ] = &lbs_band_2ghz;

	/*
	 * We could check priv->fwcapinfo && FW_CAPINFO_WPA, but I have
	 * never seen a firmware without WPA
	 */
	wdev->wiphy->cipher_suites = cipher_suites;
	wdev->wiphy->n_cipher_suites = ARRAY_SIZE(cipher_suites);
	wdev->wiphy->reg_notifier = lbs_reg_notifier;

	ret = wiphy_register(wdev->wiphy);
	if (ret < 0)
		pr_err("cannot register wiphy device\n");

	priv->wiphy_registered = true;

	ret = register_netdev(priv->dev);
	if (ret)
		pr_err("cannot register network device\n");

	INIT_DELAYED_WORK(&priv->scan_work, lbs_scan_worker);

	lbs_cfg_set_regulatory_hint(priv);

	return ret;
}