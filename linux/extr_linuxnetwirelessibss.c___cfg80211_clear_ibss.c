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
struct wireless_dev {int /*<<< orphan*/  chandef; scalar_t__ ssid_len; TYPE_2__* current_bss; int /*<<< orphan*/  wiphy; int /*<<< orphan*/ * connect_keys; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct cfg80211_registered_device {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  pub; } ;
struct TYPE_3__ {scalar_t__ del_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_WDEV_LOCK (struct wireless_dev*) ; 
 int /*<<< orphan*/  cfg80211_put_bss (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfg80211_sched_dfs_chan_update (struct cfg80211_registered_device*) ; 
 int /*<<< orphan*/  cfg80211_unhold_bss (TYPE_2__*) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdev_del_key (struct cfg80211_registered_device*,struct net_device*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdev_set_qos_map (struct cfg80211_registered_device*,struct net_device*,int /*<<< orphan*/ *) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __cfg80211_clear_ibss(struct net_device *dev, bool nowext)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wdev->wiphy);
	int i;

	ASSERT_WDEV_LOCK(wdev);

	kzfree(wdev->connect_keys);
	wdev->connect_keys = NULL;

	rdev_set_qos_map(rdev, dev, NULL);

	/*
	 * Delete all the keys ... pairwise keys can't really
	 * exist any more anyway, but default keys might.
	 */
	if (rdev->ops->del_key)
		for (i = 0; i < 6; i++)
			rdev_del_key(rdev, dev, i, false, NULL);

	if (wdev->current_bss) {
		cfg80211_unhold_bss(wdev->current_bss);
		cfg80211_put_bss(wdev->wiphy, &wdev->current_bss->pub);
	}

	wdev->current_bss = NULL;
	wdev->ssid_len = 0;
	memset(&wdev->chandef, 0, sizeof(wdev->chandef));
#ifdef CONFIG_CFG80211_WEXT
	if (!nowext)
		wdev->wext.ibss.ssid_len = 0;
#endif
	cfg80211_sched_dfs_chan_update(rdev);
}