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
struct dsa_switch {int /*<<< orphan*/  index; int /*<<< orphan*/  dev; int /*<<< orphan*/  devlink; } ;
struct dsa_port {int type; int /*<<< orphan*/  slave; int /*<<< orphan*/  devlink_port; int /*<<< orphan*/  index; struct dsa_switch* ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_PORT_FLAVOUR_CPU ; 
 int /*<<< orphan*/  DEVLINK_PORT_FLAVOUR_DSA ; 
 int /*<<< orphan*/  DEVLINK_PORT_FLAVOUR_PHYSICAL ; 
#define  DSA_PORT_TYPE_CPU 131 
#define  DSA_PORT_TYPE_DSA 130 
#define  DSA_PORT_TYPE_UNUSED 129 
#define  DSA_PORT_TYPE_USER 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_port_attrs_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int devlink_port_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_port_type_eth_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dsa_port_link_register_of (struct dsa_port*) ; 
 int dsa_slave_create (struct dsa_port*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dsa_port_setup(struct dsa_port *dp)
{
	struct dsa_switch *ds = dp->ds;
	int err = 0;

	memset(&dp->devlink_port, 0, sizeof(dp->devlink_port));

	if (dp->type != DSA_PORT_TYPE_UNUSED)
		err = devlink_port_register(ds->devlink, &dp->devlink_port,
					    dp->index);
	if (err)
		return err;

	switch (dp->type) {
	case DSA_PORT_TYPE_UNUSED:
		break;
	case DSA_PORT_TYPE_CPU:
		/* dp->index is used now as port_number. However
		 * CPU ports should have separate numbering
		 * independent from front panel port numbers.
		 */
		devlink_port_attrs_set(&dp->devlink_port,
				       DEVLINK_PORT_FLAVOUR_CPU,
				       dp->index, false, 0);
		err = dsa_port_link_register_of(dp);
		if (err) {
			dev_err(ds->dev, "failed to setup link for port %d.%d\n",
				ds->index, dp->index);
			return err;
		}
		break;
	case DSA_PORT_TYPE_DSA:
		/* dp->index is used now as port_number. However
		 * DSA ports should have separate numbering
		 * independent from front panel port numbers.
		 */
		devlink_port_attrs_set(&dp->devlink_port,
				       DEVLINK_PORT_FLAVOUR_DSA,
				       dp->index, false, 0);
		err = dsa_port_link_register_of(dp);
		if (err) {
			dev_err(ds->dev, "failed to setup link for port %d.%d\n",
				ds->index, dp->index);
			return err;
		}
		break;
	case DSA_PORT_TYPE_USER:
		devlink_port_attrs_set(&dp->devlink_port,
				       DEVLINK_PORT_FLAVOUR_PHYSICAL,
				       dp->index, false, 0);
		err = dsa_slave_create(dp);
		if (err)
			dev_err(ds->dev, "failed to create slave for port %d.%d\n",
				ds->index, dp->index);
		else
			devlink_port_type_eth_set(&dp->devlink_port, dp->slave);
		break;
	}

	return 0;
}