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
typedef  int /*<<< orphan*/  u8 ;
struct wireless_dev {TYPE_3__* current_bss; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct cfg80211_registered_device {TYPE_1__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  bssid; } ;
struct TYPE_6__ {TYPE_2__ pub; } ;
struct TYPE_4__ {int /*<<< orphan*/  deauth; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_WDEV_LOCK (struct wireless_dev*) ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  WLAN_REASON_DEAUTH_LEAVING ; 
 int /*<<< orphan*/  cfg80211_mlme_deauth (struct cfg80211_registered_device*,struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void cfg80211_mlme_down(struct cfg80211_registered_device *rdev,
			struct net_device *dev)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	u8 bssid[ETH_ALEN];

	ASSERT_WDEV_LOCK(wdev);

	if (!rdev->ops->deauth)
		return;

	if (!wdev->current_bss)
		return;

	memcpy(bssid, wdev->current_bss->pub.bssid, ETH_ALEN);
	cfg80211_mlme_deauth(rdev, dev, bssid, NULL, 0,
			     WLAN_REASON_DEAUTH_LEAVING, false);
}