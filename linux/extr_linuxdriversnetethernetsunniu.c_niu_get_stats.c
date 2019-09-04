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
struct rtnl_link_stats64 {int dummy; } ;
struct niu {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct niu* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  niu_get_rx_stats (struct niu*,struct rtnl_link_stats64*) ; 
 int /*<<< orphan*/  niu_get_tx_stats (struct niu*,struct rtnl_link_stats64*) ; 

__attribute__((used)) static void niu_get_stats(struct net_device *dev,
			  struct rtnl_link_stats64 *stats)
{
	struct niu *np = netdev_priv(dev);

	if (netif_running(dev)) {
		niu_get_rx_stats(np, stats);
		niu_get_tx_stats(np, stats);
	}
}