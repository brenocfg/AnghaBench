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
struct vnet {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct vnet* netdev_priv (struct net_device*) ; 
 void sunvnet_set_rx_mode_common (struct net_device*,struct vnet*) ; 

__attribute__((used)) static void vnet_set_rx_mode(struct net_device *dev)
{
	struct vnet *vp = netdev_priv(dev);

	return sunvnet_set_rx_mode_common(dev, vp);
}