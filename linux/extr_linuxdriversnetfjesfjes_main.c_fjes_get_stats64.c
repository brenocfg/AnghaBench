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
struct net_device {int dummy; } ;
struct fjes_adapter {int /*<<< orphan*/  stats64; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct rtnl_link_stats64*,int /*<<< orphan*/ *,int) ; 
 struct fjes_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
fjes_get_stats64(struct net_device *netdev, struct rtnl_link_stats64 *stats)
{
	struct fjes_adapter *adapter = netdev_priv(netdev);

	memcpy(stats, &adapter->stats64, sizeof(struct rtnl_link_stats64));
}