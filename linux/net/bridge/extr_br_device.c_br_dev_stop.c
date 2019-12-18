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
struct net_bridge {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  br_multicast_stop (struct net_bridge*) ; 
 int /*<<< orphan*/  br_stp_disable_bridge (struct net_bridge*) ; 
 struct net_bridge* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int br_dev_stop(struct net_device *dev)
{
	struct net_bridge *br = netdev_priv(dev);

	br_stp_disable_bridge(br);
	br_multicast_stop(br);

	netif_stop_queue(dev);

	return 0;
}