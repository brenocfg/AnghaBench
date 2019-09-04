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
struct phy_device {int dummy; } ;
struct net_device {scalar_t__ phydev; } ;
struct dsa_switch {TYPE_1__* ops; } ;
struct dsa_port {int /*<<< orphan*/  index; struct dsa_switch* ds; } ;
typedef  int /*<<< orphan*/  phy_interface_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* phylink_mac_link_up ) (struct dsa_switch*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,struct phy_device*) ;int /*<<< orphan*/  (* adjust_link ) (struct dsa_switch*,int /*<<< orphan*/ ,scalar_t__) ;} ;

/* Variables and functions */
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct dsa_switch*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct dsa_switch*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,struct phy_device*) ; 

__attribute__((used)) static void dsa_slave_phylink_mac_link_up(struct net_device *dev,
					  unsigned int mode,
					  phy_interface_t interface,
					  struct phy_device *phydev)
{
	struct dsa_port *dp = dsa_slave_to_port(dev);
	struct dsa_switch *ds = dp->ds;

	if (!ds->ops->phylink_mac_link_up) {
		if (ds->ops->adjust_link && dev->phydev)
			ds->ops->adjust_link(ds, dp->index, dev->phydev);
		return;
	}

	ds->ops->phylink_mac_link_up(ds, dp->index, mode, interface, phydev);
}