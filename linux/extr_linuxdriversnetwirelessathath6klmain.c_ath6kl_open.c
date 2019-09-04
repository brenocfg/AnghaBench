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
 int /*<<< orphan*/  CONNECTED ; 
 int /*<<< orphan*/  WLAN_ENABLED ; 
 struct ath6kl_vif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath6kl_open(struct net_device *dev)
{
	struct ath6kl_vif *vif = netdev_priv(dev);

	set_bit(WLAN_ENABLED, &vif->flags);

	if (test_bit(CONNECTED, &vif->flags)) {
		netif_carrier_on(dev);
		netif_wake_queue(dev);
	} else {
		netif_carrier_off(dev);
	}

	return 0;
}