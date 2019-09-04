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
struct net_device {int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIU_TX_TIMEOUT ; 
 int /*<<< orphan*/  niu_ethtool_ops ; 
 int /*<<< orphan*/  niu_netdev_ops ; 

__attribute__((used)) static void niu_assign_netdev_ops(struct net_device *dev)
{
	dev->netdev_ops = &niu_netdev_ops;
	dev->ethtool_ops = &niu_ethtool_ops;
	dev->watchdog_timeo = NIU_TX_TIMEOUT;
}