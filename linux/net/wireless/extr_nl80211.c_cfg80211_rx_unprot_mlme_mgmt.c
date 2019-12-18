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
typedef  int /*<<< orphan*/  u32 ;
struct wireless_dev {struct wiphy* wiphy; } ;
struct wiphy {int dummy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct ieee80211_mgmt {int /*<<< orphan*/  frame_control; } ;
struct cfg80211_registered_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NL80211_CMD_UNPROT_DEAUTHENTICATE ; 
 int /*<<< orphan*/  NL80211_CMD_UNPROT_DISASSOCIATE ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ ieee80211_is_deauth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl80211_send_mlme_event (struct cfg80211_registered_device*,struct net_device*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_cfg80211_rx_unprot_mlme_mgmt (struct net_device*,int /*<<< orphan*/  const*,size_t) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (struct wiphy*) ; 

void cfg80211_rx_unprot_mlme_mgmt(struct net_device *dev, const u8 *buf,
				  size_t len)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct wiphy *wiphy = wdev->wiphy;
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wiphy);
	const struct ieee80211_mgmt *mgmt = (void *)buf;
	u32 cmd;

	if (WARN_ON(len < 2))
		return;

	if (ieee80211_is_deauth(mgmt->frame_control))
		cmd = NL80211_CMD_UNPROT_DEAUTHENTICATE;
	else
		cmd = NL80211_CMD_UNPROT_DISASSOCIATE;

	trace_cfg80211_rx_unprot_mlme_mgmt(dev, buf, len);
	nl80211_send_mlme_event(rdev, dev, buf, len, cmd, GFP_ATOMIC, -1,
				NULL, 0);
}