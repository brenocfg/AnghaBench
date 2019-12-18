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
struct wireless_dev {TYPE_2__* conn; int /*<<< orphan*/  conn_bss_type; int /*<<< orphan*/  wiphy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  conn_work; } ;
struct cfg80211_bss {int /*<<< orphan*/  channel; int /*<<< orphan*/  bssid; } ;
struct TYPE_3__ {int /*<<< orphan*/  channel; int /*<<< orphan*/  bssid; int /*<<< orphan*/  privacy; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; TYPE_1__ params; int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_WDEV_LOCK (struct wireless_dev*) ; 
 int /*<<< orphan*/  CFG80211_CONN_AUTHENTICATE_NEXT ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IEEE80211_PRIVACY (int /*<<< orphan*/ ) ; 
 struct cfg80211_bss* cfg80211_get_bss (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cfg80211_bss *cfg80211_get_conn_bss(struct wireless_dev *wdev)
{
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wdev->wiphy);
	struct cfg80211_bss *bss;

	ASSERT_WDEV_LOCK(wdev);

	bss = cfg80211_get_bss(wdev->wiphy, wdev->conn->params.channel,
			       wdev->conn->params.bssid,
			       wdev->conn->params.ssid,
			       wdev->conn->params.ssid_len,
			       wdev->conn_bss_type,
			       IEEE80211_PRIVACY(wdev->conn->params.privacy));
	if (!bss)
		return NULL;

	memcpy(wdev->conn->bssid, bss->bssid, ETH_ALEN);
	wdev->conn->params.bssid = wdev->conn->bssid;
	wdev->conn->params.channel = bss->channel;
	wdev->conn->state = CFG80211_CONN_AUTHENTICATE_NEXT;
	schedule_work(&rdev->conn_work);

	return bss;
}