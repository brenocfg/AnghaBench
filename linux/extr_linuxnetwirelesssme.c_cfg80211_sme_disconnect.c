#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct wireless_dev {TYPE_2__* conn; int /*<<< orphan*/  netdev; int /*<<< orphan*/  wiphy; } ;
struct cfg80211_registered_device {TYPE_3__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  deauth; } ;
struct TYPE_4__ {int /*<<< orphan*/  bssid; } ;
struct TYPE_5__ {scalar_t__ state; TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ CFG80211_CONN_SCANNING ; 
 scalar_t__ CFG80211_CONN_SCAN_AGAIN ; 
 int EOPNOTSUPP ; 
 int cfg80211_mlme_deauth (struct cfg80211_registered_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cfg80211_sme_free (struct wireless_dev*) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cfg80211_sme_disconnect(struct wireless_dev *wdev, u16 reason)
{
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wdev->wiphy);
	int err;

	if (!wdev->conn)
		return 0;

	if (!rdev->ops->deauth)
		return -EOPNOTSUPP;

	if (wdev->conn->state == CFG80211_CONN_SCANNING ||
	    wdev->conn->state == CFG80211_CONN_SCAN_AGAIN) {
		err = 0;
		goto out;
	}

	/* wdev->conn->params.bssid must be set if > SCANNING */
	err = cfg80211_mlme_deauth(rdev, wdev->netdev,
				   wdev->conn->params.bssid,
				   NULL, 0, reason, false);
 out:
	cfg80211_sme_free(wdev);
	return err;
}