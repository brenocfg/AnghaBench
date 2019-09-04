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
struct vlan_dev_priv {int /*<<< orphan*/  real_dev_addr; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_uc_add (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_uc_del (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vlan_dev_inherit_address (struct net_device*,struct net_device*) ; 
 struct vlan_dev_priv* vlan_dev_priv (struct net_device*) ; 

__attribute__((used)) static void vlan_sync_address(struct net_device *dev,
			      struct net_device *vlandev)
{
	struct vlan_dev_priv *vlan = vlan_dev_priv(vlandev);

	/* May be called without an actual change */
	if (ether_addr_equal(vlan->real_dev_addr, dev->dev_addr))
		return;

	/* vlan continues to inherit address of lower device */
	if (vlan_dev_inherit_address(vlandev, dev))
		goto out;

	/* vlan address was different from the old address and is equal to
	 * the new address */
	if (!ether_addr_equal(vlandev->dev_addr, vlan->real_dev_addr) &&
	    ether_addr_equal(vlandev->dev_addr, dev->dev_addr))
		dev_uc_del(dev, vlandev->dev_addr);

	/* vlan address was equal to the old address and is different from
	 * the new address */
	if (ether_addr_equal(vlandev->dev_addr, vlan->real_dev_addr) &&
	    !ether_addr_equal(vlandev->dev_addr, dev->dev_addr))
		dev_uc_add(dev, vlandev->dev_addr);

out:
	ether_addr_copy(vlan->real_dev_addr, dev->dev_addr);
}