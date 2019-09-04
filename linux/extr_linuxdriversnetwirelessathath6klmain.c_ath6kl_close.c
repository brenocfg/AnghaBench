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
struct net_device {int dummy; } ;
struct ath6kl_vif {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_ENABLED ; 
 int /*<<< orphan*/  ath6kl_cfg80211_stop (struct ath6kl_vif*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ath6kl_vif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int ath6kl_close(struct net_device *dev)
{
	struct ath6kl_vif *vif = netdev_priv(dev);

	netif_stop_queue(dev);

	ath6kl_cfg80211_stop(vif);

	clear_bit(WLAN_ENABLED, &vif->flags);

	return 0;
}