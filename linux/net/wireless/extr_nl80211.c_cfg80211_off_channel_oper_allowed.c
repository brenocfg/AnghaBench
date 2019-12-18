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
struct TYPE_4__ {TYPE_1__* chan; } ;
struct wireless_dev {int /*<<< orphan*/  wiphy; TYPE_2__ chandef; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_WDEV_LOCK (struct wireless_dev*) ; 
 int IEEE80211_CHAN_RADAR ; 
 int /*<<< orphan*/  cfg80211_beaconing_iface_active (struct wireless_dev*) ; 
 int regulatory_pre_cac_allowed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool cfg80211_off_channel_oper_allowed(struct wireless_dev *wdev)
{
	ASSERT_WDEV_LOCK(wdev);

	if (!cfg80211_beaconing_iface_active(wdev))
		return true;

	if (!(wdev->chandef.chan->flags & IEEE80211_CHAN_RADAR))
		return true;

	return regulatory_pre_cac_allowed(wdev->wiphy);
}