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
typedef  int /*<<< orphan*/  u8 ;
struct wireless_dev {int dummy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct ieee80211_mgmt {int /*<<< orphan*/  frame_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_WDEV_LOCK (struct wireless_dev*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cfg80211_process_auth (struct wireless_dev*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  cfg80211_process_deauth (struct wireless_dev*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  cfg80211_process_disassoc (struct wireless_dev*,int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ ieee80211_is_auth (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_deauth (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_disassoc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_cfg80211_rx_mlme_mgmt (struct net_device*,int /*<<< orphan*/  const*,size_t) ; 

void cfg80211_rx_mlme_mgmt(struct net_device *dev, const u8 *buf, size_t len)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct ieee80211_mgmt *mgmt = (void *)buf;

	ASSERT_WDEV_LOCK(wdev);

	trace_cfg80211_rx_mlme_mgmt(dev, buf, len);

	if (WARN_ON(len < 2))
		return;

	if (ieee80211_is_auth(mgmt->frame_control))
		cfg80211_process_auth(wdev, buf, len);
	else if (ieee80211_is_deauth(mgmt->frame_control))
		cfg80211_process_deauth(wdev, buf, len);
	else if (ieee80211_is_disassoc(mgmt->frame_control))
		cfg80211_process_disassoc(wdev, buf, len);
}