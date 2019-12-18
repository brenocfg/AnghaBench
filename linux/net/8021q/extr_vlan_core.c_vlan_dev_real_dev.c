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
typedef  struct net_device const net_device ;
struct TYPE_2__ {struct net_device const* real_dev; } ;

/* Variables and functions */
 scalar_t__ is_vlan_dev (struct net_device const*) ; 
 TYPE_1__* vlan_dev_priv (struct net_device const*) ; 

struct net_device *vlan_dev_real_dev(const struct net_device *dev)
{
	struct net_device *ret = vlan_dev_priv(dev)->real_dev;

	while (is_vlan_dev(ret))
		ret = vlan_dev_priv(ret)->real_dev;

	return ret;
}