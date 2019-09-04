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
typedef  scalar_t__ u8 ;
struct TYPE_5__ {scalar_t__ const* ssid; scalar_t__ ssid_len; } ;
struct TYPE_6__ {TYPE_2__ connect; } ;
struct wireless_dev {scalar_t__ iftype; TYPE_3__ wext; TYPE_1__* current_bss; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int flags; scalar_t__ length; } ;
struct TYPE_4__ {int /*<<< orphan*/  pub; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WLAN_EID_SSID ; 
 scalar_t__* ieee80211_bss_get_ie (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__ const*,scalar_t__) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  wdev_lock (struct wireless_dev*) ; 
 int /*<<< orphan*/  wdev_unlock (struct wireless_dev*) ; 

int cfg80211_mgd_wext_giwessid(struct net_device *dev,
			       struct iw_request_info *info,
			       struct iw_point *data, char *ssid)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;

	/* call only for station! */
	if (WARN_ON(wdev->iftype != NL80211_IFTYPE_STATION))
		return -EINVAL;

	data->flags = 0;

	wdev_lock(wdev);
	if (wdev->current_bss) {
		const u8 *ie;

		rcu_read_lock();
		ie = ieee80211_bss_get_ie(&wdev->current_bss->pub,
					  WLAN_EID_SSID);
		if (ie) {
			data->flags = 1;
			data->length = ie[1];
			memcpy(ssid, ie + 2, data->length);
		}
		rcu_read_unlock();
	} else if (wdev->wext.connect.ssid && wdev->wext.connect.ssid_len) {
		data->flags = 1;
		data->length = wdev->wext.connect.ssid_len;
		memcpy(ssid, wdev->wext.connect.ssid, data->length);
	}
	wdev_unlock(wdev);

	return 0;
}