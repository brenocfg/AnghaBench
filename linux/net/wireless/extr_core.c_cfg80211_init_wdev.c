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
struct wireless_dev {int /*<<< orphan*/  list; scalar_t__ identifier; int /*<<< orphan*/  pmsr_free_wk; int /*<<< orphan*/  pmsr_lock; int /*<<< orphan*/  pmsr_list; int /*<<< orphan*/  mgmt_registrations_lock; int /*<<< orphan*/  mgmt_registrations; int /*<<< orphan*/  event_lock; int /*<<< orphan*/  event_list; int /*<<< orphan*/  mtx; } ;
struct TYPE_2__ {int /*<<< orphan*/  wdev_list; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  devlist_generation; TYPE_1__ wiphy; scalar_t__ wdev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NL80211_CMD_NEW_INTERFACE ; 
 int /*<<< orphan*/  cfg80211_pmsr_free_wk ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nl80211_notify_iface (struct cfg80211_registered_device*,struct wireless_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void cfg80211_init_wdev(struct cfg80211_registered_device *rdev,
			struct wireless_dev *wdev)
{
	mutex_init(&wdev->mtx);
	INIT_LIST_HEAD(&wdev->event_list);
	spin_lock_init(&wdev->event_lock);
	INIT_LIST_HEAD(&wdev->mgmt_registrations);
	spin_lock_init(&wdev->mgmt_registrations_lock);
	INIT_LIST_HEAD(&wdev->pmsr_list);
	spin_lock_init(&wdev->pmsr_lock);
	INIT_WORK(&wdev->pmsr_free_wk, cfg80211_pmsr_free_wk);

	/*
	 * We get here also when the interface changes network namespaces,
	 * as it's registered into the new one, but we don't want it to
	 * change ID in that case. Checking if the ID is already assigned
	 * works, because 0 isn't considered a valid ID and the memory is
	 * 0-initialized.
	 */
	if (!wdev->identifier)
		wdev->identifier = ++rdev->wdev_id;
	list_add_rcu(&wdev->list, &rdev->wiphy.wdev_list);
	rdev->devlist_generation++;

	nl80211_notify_iface(rdev, wdev, NL80211_CMD_NEW_INTERFACE);
}