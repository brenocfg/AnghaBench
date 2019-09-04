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
struct sk_buff {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NL80211_MCGRP_SCAN ; 
 int /*<<< orphan*/  genlmsg_multicast_netns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl80211_fam ; 
 int /*<<< orphan*/  wiphy_net (int /*<<< orphan*/ *) ; 

void nl80211_send_scan_msg(struct cfg80211_registered_device *rdev,
			   struct sk_buff *msg)
{
	if (!msg)
		return;

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_SCAN, GFP_KERNEL);
}