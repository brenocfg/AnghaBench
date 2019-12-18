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
struct wireless_dev {int /*<<< orphan*/  mgmt_registrations_lock; int /*<<< orphan*/  mgmt_registrations; int /*<<< orphan*/  wiphy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  mlme_unreg_lock; int /*<<< orphan*/  mlme_unreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfg80211_process_mlme_unregistrations (struct cfg80211_registered_device*) ; 
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (int /*<<< orphan*/ ) ; 

void cfg80211_mlme_purge_registrations(struct wireless_dev *wdev)
{
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wdev->wiphy);

	spin_lock_bh(&wdev->mgmt_registrations_lock);
	spin_lock(&rdev->mlme_unreg_lock);
	list_splice_tail_init(&wdev->mgmt_registrations, &rdev->mlme_unreg);
	spin_unlock(&rdev->mlme_unreg_lock);
	spin_unlock_bh(&wdev->mgmt_registrations_lock);

	cfg80211_process_mlme_unregistrations(rdev);
}