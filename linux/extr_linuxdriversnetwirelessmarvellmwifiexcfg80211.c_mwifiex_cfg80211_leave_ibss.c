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
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct mwifiex_private {int /*<<< orphan*/  cfg_bssid; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  MSG ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ mwifiex_deauthenticate (struct mwifiex_private*,int /*<<< orphan*/ *) ; 
 struct mwifiex_private* mwifiex_netdev_get_priv (struct net_device*) ; 

__attribute__((used)) static int
mwifiex_cfg80211_leave_ibss(struct wiphy *wiphy, struct net_device *dev)
{
	struct mwifiex_private *priv = mwifiex_netdev_get_priv(dev);

	mwifiex_dbg(priv->adapter, MSG, "info: disconnecting from essid %pM\n",
		    priv->cfg_bssid);
	if (mwifiex_deauthenticate(priv, NULL))
		return -EFAULT;

	eth_zero_addr(priv->cfg_bssid);

	return 0;
}