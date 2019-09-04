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
struct net_device {int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/  watchdog_timeo; } ;
struct napi_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GELIC_NET_WATCHDOG_TIMEOUT ; 
 int /*<<< orphan*/  NAPI_POLL_WEIGHT ; 
 int /*<<< orphan*/  gelic_ether_ethtool_ops ; 
 int /*<<< orphan*/  gelic_net_poll ; 
 int /*<<< orphan*/  gelic_netdevice_ops ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,struct napi_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gelic_ether_setup_netdev_ops(struct net_device *netdev,
					 struct napi_struct *napi)
{
	netdev->watchdog_timeo = GELIC_NET_WATCHDOG_TIMEOUT;
	/* NAPI */
	netif_napi_add(netdev, napi, gelic_net_poll, NAPI_POLL_WEIGHT);
	netdev->ethtool_ops = &gelic_ether_ethtool_ops;
	netdev->netdev_ops = &gelic_netdevice_ops;
}