#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wireless_dev {TYPE_1__* wiphy; int /*<<< orphan*/  iftype; } ;
struct wilc_priv {struct net_device* dev; struct wireless_dev* wdev; } ;
struct net_device {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int max_scan_ie_len; int max_remain_on_channel_duration; int interface_modes; int /*<<< orphan*/  flags; int /*<<< orphan*/  mgmt_stypes; int /*<<< orphan*/  n_cipher_suites; int /*<<< orphan*/  cipher_suites; int /*<<< orphan*/  signal_type; int /*<<< orphan*/  max_num_pmkids; int /*<<< orphan*/  max_scan_ssids; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFG80211_SIGNAL_TYPE_MBM ; 
 int /*<<< orphan*/  MAX_NUM_PROBED_SSID ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  NL80211_IFTYPE_MONITOR ; 
 int /*<<< orphan*/  NL80211_IFTYPE_P2P_CLIENT ; 
 int /*<<< orphan*/  NL80211_IFTYPE_P2P_GO ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  WILC_MAX_NUM_PMKIDS ; 
 int /*<<< orphan*/  WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL ; 
 int /*<<< orphan*/  cipher_suites ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  set_wiphy_dev (TYPE_1__*,struct device*) ; 
 struct wilc_priv* wdev_priv (struct wireless_dev*) ; 
 int /*<<< orphan*/  wilc_wfi_cfg80211_mgmt_types ; 
 struct wireless_dev* wilc_wfi_cfg_alloc () ; 
 int wiphy_register (TYPE_1__*) ; 

struct wireless_dev *wilc_create_wiphy(struct net_device *net,
				       struct device *dev)
{
	struct wilc_priv *priv;
	struct wireless_dev *wdev;
	int ret;

	wdev = wilc_wfi_cfg_alloc();
	if (!wdev) {
		netdev_err(net, "wiphy new allocate failed\n");
		return NULL;
	}

	priv = wdev_priv(wdev);
	priv->wdev = wdev;
	wdev->wiphy->max_scan_ssids = MAX_NUM_PROBED_SSID;
#ifdef CONFIG_PM
	wdev->wiphy->wowlan = &wowlan_support;
#endif
	wdev->wiphy->max_num_pmkids = WILC_MAX_NUM_PMKIDS;
	wdev->wiphy->max_scan_ie_len = 1000;
	wdev->wiphy->signal_type = CFG80211_SIGNAL_TYPE_MBM;
	wdev->wiphy->cipher_suites = cipher_suites;
	wdev->wiphy->n_cipher_suites = ARRAY_SIZE(cipher_suites);
	wdev->wiphy->mgmt_stypes = wilc_wfi_cfg80211_mgmt_types;

	wdev->wiphy->max_remain_on_channel_duration = 500;
	wdev->wiphy->interface_modes = BIT(NL80211_IFTYPE_STATION) |
					BIT(NL80211_IFTYPE_AP) |
					BIT(NL80211_IFTYPE_MONITOR) |
					BIT(NL80211_IFTYPE_P2P_GO) |
					BIT(NL80211_IFTYPE_P2P_CLIENT);
	wdev->wiphy->flags |= WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL;
	wdev->iftype = NL80211_IFTYPE_STATION;

	set_wiphy_dev(wdev->wiphy, dev);

	ret = wiphy_register(wdev->wiphy);
	if (ret)
		netdev_err(net, "Cannot register wiphy device\n");

	priv->dev = net;
	return wdev;
}