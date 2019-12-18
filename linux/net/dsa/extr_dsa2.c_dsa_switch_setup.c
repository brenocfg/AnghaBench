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
struct dsa_switch {int /*<<< orphan*/ * devlink; int /*<<< orphan*/  slave_mii_bus; int /*<<< orphan*/  dev; TYPE_1__* ops; int /*<<< orphan*/  phys_mii_mask; } ;
struct TYPE_2__ {int (* setup ) (struct dsa_switch*) ;scalar_t__ phy_read; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * devlink_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_free (int /*<<< orphan*/ *) ; 
 int devlink_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_mdiobus_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsa_devlink_ops ; 
 int /*<<< orphan*/  dsa_slave_mii_bus_init (struct dsa_switch*) ; 
 int dsa_switch_register_notifier (struct dsa_switch*) ; 
 int /*<<< orphan*/  dsa_switch_unregister_notifier (struct dsa_switch*) ; 
 int /*<<< orphan*/  dsa_user_ports (struct dsa_switch*) ; 
 int mdiobus_register (int /*<<< orphan*/ ) ; 
 int stub1 (struct dsa_switch*) ; 

__attribute__((used)) static int dsa_switch_setup(struct dsa_switch *ds)
{
	int err = 0;

	/* Initialize ds->phys_mii_mask before registering the slave MDIO bus
	 * driver and before ops->setup() has run, since the switch drivers and
	 * the slave MDIO bus driver rely on these values for probing PHY
	 * devices or not
	 */
	ds->phys_mii_mask |= dsa_user_ports(ds);

	/* Add the switch to devlink before calling setup, so that setup can
	 * add dpipe tables
	 */
	ds->devlink = devlink_alloc(&dsa_devlink_ops, 0);
	if (!ds->devlink)
		return -ENOMEM;

	err = devlink_register(ds->devlink, ds->dev);
	if (err)
		goto free_devlink;

	err = dsa_switch_register_notifier(ds);
	if (err)
		goto unregister_devlink;

	err = ds->ops->setup(ds);
	if (err < 0)
		goto unregister_notifier;

	if (!ds->slave_mii_bus && ds->ops->phy_read) {
		ds->slave_mii_bus = devm_mdiobus_alloc(ds->dev);
		if (!ds->slave_mii_bus) {
			err = -ENOMEM;
			goto unregister_notifier;
		}

		dsa_slave_mii_bus_init(ds);

		err = mdiobus_register(ds->slave_mii_bus);
		if (err < 0)
			goto unregister_notifier;
	}

	return 0;

unregister_notifier:
	dsa_switch_unregister_notifier(ds);
unregister_devlink:
	devlink_unregister(ds->devlink);
free_devlink:
	devlink_free(ds->devlink);
	ds->devlink = NULL;

	return err;
}