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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct phy_device {TYPE_1__ mdio; } ;
struct net_device {int dummy; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  phy_interface_t ;

/* Variables and functions */
 struct phy_device* of_phy_find_device (struct device_node*) ; 
 int phy_attach_direct (struct net_device*,struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

struct phy_device *of_phy_attach(struct net_device *dev,
				 struct device_node *phy_np, u32 flags,
				 phy_interface_t iface)
{
	struct phy_device *phy = of_phy_find_device(phy_np);
	int ret;

	if (!phy)
		return NULL;

	ret = phy_attach_direct(dev, phy, flags, iface);

	/* refcount is held by phy_attach_direct() on success */
	put_device(&phy->mdio.dev);

	return ret ? NULL : phy;
}