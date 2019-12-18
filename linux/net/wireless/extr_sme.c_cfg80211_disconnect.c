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
typedef  int /*<<< orphan*/  u16 ;
struct wireless_dev {scalar_t__ ssid_len; int /*<<< orphan*/  current_bss; scalar_t__ conn; scalar_t__ conn_owner_nlportid; int /*<<< orphan*/ * connect_keys; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct cfg80211_registered_device {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  disconnect; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_WDEV_LOCK (struct wireless_dev*) ; 
 int /*<<< orphan*/  cfg80211_mlme_down (struct cfg80211_registered_device*,struct net_device*) ; 
 int cfg80211_sme_disconnect (struct wireless_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ *) ; 
 int rdev_disconnect (struct cfg80211_registered_device*,struct net_device*,int /*<<< orphan*/ ) ; 

int cfg80211_disconnect(struct cfg80211_registered_device *rdev,
			struct net_device *dev, u16 reason, bool wextev)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	int err = 0;

	ASSERT_WDEV_LOCK(wdev);

	kzfree(wdev->connect_keys);
	wdev->connect_keys = NULL;

	wdev->conn_owner_nlportid = 0;

	if (wdev->conn)
		err = cfg80211_sme_disconnect(wdev, reason);
	else if (!rdev->ops->disconnect)
		cfg80211_mlme_down(rdev, dev);
	else if (wdev->ssid_len)
		err = rdev_disconnect(rdev, dev, reason);

	/*
	 * Clear ssid_len unless we actually were fully connected,
	 * in which case cfg80211_disconnected() will take care of
	 * this later.
	 */
	if (!wdev->current_bss)
		wdev->ssid_len = 0;

	return err;
}