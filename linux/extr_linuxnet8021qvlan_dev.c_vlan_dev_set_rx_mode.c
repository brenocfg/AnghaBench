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
struct TYPE_2__ {int /*<<< orphan*/  real_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_mc_sync (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  dev_uc_sync (int /*<<< orphan*/ ,struct net_device*) ; 
 TYPE_1__* vlan_dev_priv (struct net_device*) ; 

__attribute__((used)) static void vlan_dev_set_rx_mode(struct net_device *vlan_dev)
{
	dev_mc_sync(vlan_dev_priv(vlan_dev)->real_dev, vlan_dev);
	dev_uc_sync(vlan_dev_priv(vlan_dev)->real_dev, vlan_dev);
}