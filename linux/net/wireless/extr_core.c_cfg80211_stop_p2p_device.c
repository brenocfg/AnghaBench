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
struct wireless_dev {scalar_t__ iftype; int is_running; } ;
struct cfg80211_registered_device {TYPE_2__* scan_req; int /*<<< orphan*/  opencount; } ;
struct TYPE_3__ {int aborted; } ;
struct TYPE_4__ {TYPE_1__ info; int /*<<< orphan*/  notified; struct wireless_dev* wdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 scalar_t__ NL80211_IFTYPE_P2P_DEVICE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ___cfg80211_scan_done (struct cfg80211_registered_device*,int) ; 
 int /*<<< orphan*/  rdev_stop_p2p_device (struct cfg80211_registered_device*,struct wireless_dev*) ; 
 int /*<<< orphan*/  wdev_running (struct wireless_dev*) ; 

void cfg80211_stop_p2p_device(struct cfg80211_registered_device *rdev,
			      struct wireless_dev *wdev)
{
	ASSERT_RTNL();

	if (WARN_ON(wdev->iftype != NL80211_IFTYPE_P2P_DEVICE))
		return;

	if (!wdev_running(wdev))
		return;

	rdev_stop_p2p_device(rdev, wdev);
	wdev->is_running = false;

	rdev->opencount--;

	if (rdev->scan_req && rdev->scan_req->wdev == wdev) {
		if (WARN_ON(!rdev->scan_req->notified))
			rdev->scan_req->info.aborted = true;
		___cfg80211_scan_done(rdev, false);
	}
}