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
typedef  scalar_t__ u16 ;
struct wireless_dev {TYPE_1__* conn; int /*<<< orphan*/  wiphy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  conn_work; } ;
struct TYPE_2__ {int prev_bssid_valid; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG80211_CONN_ASSOCIATE_NEXT ; 
 int /*<<< orphan*/  CFG80211_CONN_ASSOC_FAILED ; 
 int /*<<< orphan*/  CFG80211_CONN_CONNECTED ; 
 scalar_t__ WLAN_STATUS_SUCCESS ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (int /*<<< orphan*/ ) ; 

bool cfg80211_sme_rx_assoc_resp(struct wireless_dev *wdev, u16 status)
{
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wdev->wiphy);

	if (!wdev->conn)
		return false;

	if (status == WLAN_STATUS_SUCCESS) {
		wdev->conn->state = CFG80211_CONN_CONNECTED;
		return false;
	}

	if (wdev->conn->prev_bssid_valid) {
		/*
		 * Some stupid APs don't accept reassoc, so we
		 * need to fall back to trying regular assoc;
		 * return true so no event is sent to userspace.
		 */
		wdev->conn->prev_bssid_valid = false;
		wdev->conn->state = CFG80211_CONN_ASSOCIATE_NEXT;
		schedule_work(&rdev->conn_work);
		return true;
	}

	wdev->conn->state = CFG80211_CONN_ASSOC_FAILED;
	schedule_work(&rdev->conn_work);
	return false;
}