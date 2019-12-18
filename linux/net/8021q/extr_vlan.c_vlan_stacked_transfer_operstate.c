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
struct vlan_dev_priv {int flags; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int VLAN_FLAG_BRIDGE_BINDING ; 
 int /*<<< orphan*/  netif_stacked_transfer_operstate (struct net_device const*,struct net_device*) ; 

__attribute__((used)) static void vlan_stacked_transfer_operstate(const struct net_device *rootdev,
					    struct net_device *dev,
					    struct vlan_dev_priv *vlan)
{
	if (!(vlan->flags & VLAN_FLAG_BRIDGE_BINDING))
		netif_stacked_transfer_operstate(rootdev, dev);
}