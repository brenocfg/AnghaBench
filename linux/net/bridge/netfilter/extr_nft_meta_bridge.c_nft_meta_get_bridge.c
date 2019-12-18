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

/* Variables and functions */
 struct net_device const* netdev_master_upper_dev_get_rcu (struct net_device*) ; 
 scalar_t__ netif_is_bridge_port (struct net_device const*) ; 

__attribute__((used)) static const struct net_device *
nft_meta_get_bridge(const struct net_device *dev)
{
	if (dev && netif_is_bridge_port(dev))
		return netdev_master_upper_dev_get_rcu((struct net_device *)dev);

	return NULL;
}