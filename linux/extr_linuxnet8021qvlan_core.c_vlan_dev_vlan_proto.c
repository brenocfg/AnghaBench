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
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int /*<<< orphan*/  vlan_proto; } ;

/* Variables and functions */
 TYPE_1__* vlan_dev_priv (struct net_device const*) ; 

__be16 vlan_dev_vlan_proto(const struct net_device *dev)
{
	return vlan_dev_priv(dev)->vlan_proto;
}