#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int VLAN_FLAG_BRIDGE_BINDING ; 
 scalar_t__ is_vlan_dev (struct net_device const*) ; 
 TYPE_1__* vlan_dev_priv (struct net_device const*) ; 

__attribute__((used)) static int br_vlan_is_bind_vlan_dev(const struct net_device *dev)
{
	return is_vlan_dev(dev) &&
		!!(vlan_dev_priv(dev)->flags & VLAN_FLAG_BRIDGE_BINDING);
}