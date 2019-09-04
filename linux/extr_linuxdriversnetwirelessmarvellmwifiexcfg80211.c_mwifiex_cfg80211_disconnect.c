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
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;
struct mwifiex_private {int hs2_enabled; int /*<<< orphan*/  cfg_bssid; TYPE_1__ wdev; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  cfg80211_sched_scan_stopped_rtnl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ mwifiex_deauthenticate (struct mwifiex_private*,int /*<<< orphan*/ *) ; 
 struct mwifiex_private* mwifiex_netdev_get_priv (struct net_device*) ; 
 int /*<<< orphan*/  mwifiex_stop_bg_scan (struct mwifiex_private*) ; 

__attribute__((used)) static int
mwifiex_cfg80211_disconnect(struct wiphy *wiphy, struct net_device *dev,
			    u16 reason_code)
{
	struct mwifiex_private *priv = mwifiex_netdev_get_priv(dev);

	if (!mwifiex_stop_bg_scan(priv))
		cfg80211_sched_scan_stopped_rtnl(priv->wdev.wiphy, 0);

	if (mwifiex_deauthenticate(priv, NULL))
		return -EFAULT;

	eth_zero_addr(priv->cfg_bssid);
	priv->hs2_enabled = false;

	return 0;
}