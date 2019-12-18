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
struct TYPE_2__ {int /*<<< orphan*/  keys; } ;
struct wireless_dev {int iftype; int /*<<< orphan*/  disconnect_wk; scalar_t__ netdev; TYPE_1__ wext; int /*<<< orphan*/  list; int /*<<< orphan*/  pmsr_free_wk; int /*<<< orphan*/  wiphy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  devlist_generation; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  NL80211_CMD_DEL_INTERFACE ; 
#define  NL80211_IFTYPE_NAN 129 
#define  NL80211_IFTYPE_P2P_DEVICE 128 
 int /*<<< orphan*/  cfg80211_cqm_config_free (struct wireless_dev*) ; 
 int /*<<< orphan*/  cfg80211_mlme_purge_registrations (struct wireless_dev*) ; 
 int /*<<< orphan*/  cfg80211_stop_nan (struct cfg80211_registered_device*,struct wireless_dev*) ; 
 int /*<<< orphan*/  cfg80211_stop_p2p_device (struct cfg80211_registered_device*,struct wireless_dev*) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nl80211_notify_iface (struct cfg80211_registered_device*,struct wireless_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 struct cfg80211_registered_device* wiphy_to_rdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __cfg80211_unregister_wdev(struct wireless_dev *wdev, bool sync)
{
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wdev->wiphy);

	ASSERT_RTNL();

	flush_work(&wdev->pmsr_free_wk);

	nl80211_notify_iface(rdev, wdev, NL80211_CMD_DEL_INTERFACE);

	list_del_rcu(&wdev->list);
	if (sync)
		synchronize_rcu();
	rdev->devlist_generation++;

	cfg80211_mlme_purge_registrations(wdev);

	switch (wdev->iftype) {
	case NL80211_IFTYPE_P2P_DEVICE:
		cfg80211_stop_p2p_device(rdev, wdev);
		break;
	case NL80211_IFTYPE_NAN:
		cfg80211_stop_nan(rdev, wdev);
		break;
	default:
		break;
	}

#ifdef CONFIG_CFG80211_WEXT
	kzfree(wdev->wext.keys);
#endif
	/* only initialized if we have a netdev */
	if (wdev->netdev)
		flush_work(&wdev->disconnect_wk);

	cfg80211_cqm_config_free(wdev);
}