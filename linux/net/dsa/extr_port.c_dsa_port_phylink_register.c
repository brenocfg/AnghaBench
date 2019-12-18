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
struct dsa_switch {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; int /*<<< orphan*/  dev; } ;
struct dsa_port {int /*<<< orphan*/  pl; TYPE_1__ pl_config; struct device_node* dn; struct dsa_switch* ds; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHYLINK_DEV ; 
 int PHY_INTERFACE_MODE_NA ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsa_port_phylink_mac_ops ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 int of_get_phy_mode (struct device_node*) ; 
 int /*<<< orphan*/  phylink_create (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phylink_destroy (int /*<<< orphan*/ ) ; 
 int phylink_of_phy_connect (int /*<<< orphan*/ ,struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phylink_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static int dsa_port_phylink_register(struct dsa_port *dp)
{
	struct dsa_switch *ds = dp->ds;
	struct device_node *port_dn = dp->dn;
	int mode, err;

	mode = of_get_phy_mode(port_dn);
	if (mode < 0)
		mode = PHY_INTERFACE_MODE_NA;

	dp->pl_config.dev = ds->dev;
	dp->pl_config.type = PHYLINK_DEV;

	dp->pl = phylink_create(&dp->pl_config, of_fwnode_handle(port_dn),
				mode, &dsa_port_phylink_mac_ops);
	if (IS_ERR(dp->pl)) {
		pr_err("error creating PHYLINK: %ld\n", PTR_ERR(dp->pl));
		return PTR_ERR(dp->pl);
	}

	err = phylink_of_phy_connect(dp->pl, port_dn, 0);
	if (err && err != -ENODEV) {
		pr_err("could not attach to PHY: %d\n", err);
		goto err_phy_connect;
	}

	rtnl_lock();
	phylink_start(dp->pl);
	rtnl_unlock();

	return 0;

err_phy_connect:
	phylink_destroy(dp->pl);
	return err;
}