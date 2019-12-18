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
struct wiphy {int dummy; } ;
struct TYPE_3__ {int registered; scalar_t__ wowlan_config; int /*<<< orphan*/  dev; int /*<<< orphan*/  debugfsdir; int /*<<< orphan*/  wdev_list; } ;
struct cfg80211_registered_device {int opencount; TYPE_2__* ops; TYPE_1__ wiphy; int /*<<< orphan*/  propagate_cac_done_wk; int /*<<< orphan*/  propagate_radar_detect_wk; int /*<<< orphan*/  mlme_unreg_wk; int /*<<< orphan*/  sched_scan_stop_wk; int /*<<< orphan*/  destroy_work; int /*<<< orphan*/  dfs_update_channels_wk; int /*<<< orphan*/  event_work; int /*<<< orphan*/  conn_work; int /*<<< orphan*/  scan_done_wk; int /*<<< orphan*/  list; scalar_t__ rfkill; int /*<<< orphan*/  dev_wait; } ;
struct TYPE_4__ {scalar_t__ set_wakeup; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_CMD_DEL_WIPHY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfg80211_rdev_free_coalesce (struct cfg80211_registered_device*) ; 
 int /*<<< orphan*/  cfg80211_rdev_free_wowlan (struct cfg80211_registered_device*) ; 
 int /*<<< orphan*/  cfg80211_rdev_list_generation ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nl80211_notify_wiphy (struct cfg80211_registered_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdev_set_wakeup (struct cfg80211_registered_device*,int) ; 
 int /*<<< orphan*/  rfkill_unregister (scalar_t__) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_regulatory_deregister (struct wiphy*) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (struct wiphy*) ; 

void wiphy_unregister(struct wiphy *wiphy)
{
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wiphy);

	wait_event(rdev->dev_wait, ({
		int __count;
		rtnl_lock();
		__count = rdev->opencount;
		rtnl_unlock();
		__count == 0; }));

	if (rdev->rfkill)
		rfkill_unregister(rdev->rfkill);

	rtnl_lock();
	nl80211_notify_wiphy(rdev, NL80211_CMD_DEL_WIPHY);
	rdev->wiphy.registered = false;

	WARN_ON(!list_empty(&rdev->wiphy.wdev_list));

	/*
	 * First remove the hardware from everywhere, this makes
	 * it impossible to find from userspace.
	 */
	debugfs_remove_recursive(rdev->wiphy.debugfsdir);
	list_del_rcu(&rdev->list);
	synchronize_rcu();

	/*
	 * If this device got a regulatory hint tell core its
	 * free to listen now to a new shiny device regulatory hint
	 */
	wiphy_regulatory_deregister(wiphy);

	cfg80211_rdev_list_generation++;
	device_del(&rdev->wiphy.dev);

	rtnl_unlock();

	flush_work(&rdev->scan_done_wk);
	cancel_work_sync(&rdev->conn_work);
	flush_work(&rdev->event_work);
	cancel_delayed_work_sync(&rdev->dfs_update_channels_wk);
	flush_work(&rdev->destroy_work);
	flush_work(&rdev->sched_scan_stop_wk);
	flush_work(&rdev->mlme_unreg_wk);
	flush_work(&rdev->propagate_radar_detect_wk);
	flush_work(&rdev->propagate_cac_done_wk);

#ifdef CONFIG_PM
	if (rdev->wiphy.wowlan_config && rdev->ops->set_wakeup)
		rdev_set_wakeup(rdev, false);
#endif
	cfg80211_rdev_free_wowlan(rdev);
	cfg80211_rdev_free_coalesce(rdev);
}