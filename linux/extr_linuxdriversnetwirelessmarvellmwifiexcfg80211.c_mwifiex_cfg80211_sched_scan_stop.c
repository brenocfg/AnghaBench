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
typedef  int /*<<< orphan*/  u64 ;
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct mwifiex_private {int dummy; } ;

/* Variables and functions */
 struct mwifiex_private* mwifiex_netdev_get_priv (struct net_device*) ; 
 int /*<<< orphan*/  mwifiex_stop_bg_scan (struct mwifiex_private*) ; 
 int /*<<< orphan*/  wiphy_info (struct wiphy*,char*) ; 

__attribute__((used)) static int mwifiex_cfg80211_sched_scan_stop(struct wiphy *wiphy,
					    struct net_device *dev, u64 reqid)
{
	struct mwifiex_private *priv = mwifiex_netdev_get_priv(dev);

	wiphy_info(wiphy, "sched scan stop!");
	mwifiex_stop_bg_scan(priv);

	return 0;
}