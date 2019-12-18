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
struct net_device {TYPE_1__* ieee80211_ptr; } ;
struct ieee80211_local {int dummy; } ;
struct ethtool_ringparam {scalar_t__ rx_mini_pending; scalar_t__ rx_jumbo_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_pending; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int EINVAL ; 
 int drv_set_ringparam (struct ieee80211_local*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ieee80211_local* wiphy_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ieee80211_set_ringparam(struct net_device *dev,
				   struct ethtool_ringparam *rp)
{
	struct ieee80211_local *local = wiphy_priv(dev->ieee80211_ptr->wiphy);

	if (rp->rx_mini_pending != 0 || rp->rx_jumbo_pending != 0)
		return -EINVAL;

	return drv_set_ringparam(local, rp->tx_pending, rp->rx_pending);
}