#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct phy_device {int interface; TYPE_2__ mdio; } ;
struct dsa_switch {TYPE_1__* ops; int /*<<< orphan*/  dev; } ;
struct dsa_port {int index; struct dsa_switch* ds; struct device_node* dn; } ;
struct device_node {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* adjust_link ) (struct dsa_switch*,int,struct phy_device*) ;} ;

/* Variables and functions */
 int PHY_INTERFACE_MODE_NA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  genphy_read_status (struct phy_device*) ; 
 int of_get_phy_mode (struct device_node*) ; 
 struct phy_device* of_phy_find_device (struct device_node*) ; 
 int of_phy_register_fixed_link (struct device_node*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct dsa_switch*,int,struct phy_device*) ; 

__attribute__((used)) static int dsa_port_fixed_link_register_of(struct dsa_port *dp)
{
	struct device_node *dn = dp->dn;
	struct dsa_switch *ds = dp->ds;
	struct phy_device *phydev;
	int port = dp->index;
	int mode;
	int err;

	err = of_phy_register_fixed_link(dn);
	if (err) {
		dev_err(ds->dev,
			"failed to register the fixed PHY of port %d\n",
			port);
		return err;
	}

	phydev = of_phy_find_device(dn);

	mode = of_get_phy_mode(dn);
	if (mode < 0)
		mode = PHY_INTERFACE_MODE_NA;
	phydev->interface = mode;

	genphy_read_status(phydev);

	if (ds->ops->adjust_link)
		ds->ops->adjust_link(ds, port, phydev);

	put_device(&phydev->mdio.dev);

	return 0;
}