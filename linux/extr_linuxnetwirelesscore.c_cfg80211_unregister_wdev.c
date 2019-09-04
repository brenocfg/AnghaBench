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
struct wireless_dev {int iftype; int /*<<< orphan*/  list; int /*<<< orphan*/  netdev; int /*<<< orphan*/  wiphy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  devlist_generation; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  NL80211_CMD_DEL_INTERFACE ; 
#define  NL80211_IFTYPE_NAN 129 
#define  NL80211_IFTYPE_P2P_DEVICE 128 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cfg80211_cqm_config_free (struct wireless_dev*) ; 
 int /*<<< orphan*/  cfg80211_mlme_purge_registrations (struct wireless_dev*) ; 
 int /*<<< orphan*/  cfg80211_stop_nan (struct cfg80211_registered_device*,struct wireless_dev*) ; 
 int /*<<< orphan*/  cfg80211_stop_p2p_device (struct cfg80211_registered_device*,struct wireless_dev*) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nl80211_notify_iface (struct cfg80211_registered_device*,struct wireless_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 struct cfg80211_registered_device* wiphy_to_rdev (int /*<<< orphan*/ ) ; 

void cfg80211_unregister_wdev(struct wireless_dev *wdev)
{
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wdev->wiphy);

	ASSERT_RTNL();

	if (WARN_ON(wdev->netdev))
		return;

	nl80211_notify_iface(rdev, wdev, NL80211_CMD_DEL_INTERFACE);

	list_del_rcu(&wdev->list);
	synchronize_rcu();
	rdev->devlist_generation++;

	switch (wdev->iftype) {
	case NL80211_IFTYPE_P2P_DEVICE:
		cfg80211_mlme_purge_registrations(wdev);
		cfg80211_stop_p2p_device(rdev, wdev);
		break;
	case NL80211_IFTYPE_NAN:
		cfg80211_stop_nan(rdev, wdev);
		break;
	default:
		WARN_ON_ONCE(1);
		break;
	}

	cfg80211_cqm_config_free(wdev);
}