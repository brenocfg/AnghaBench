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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int /*<<< orphan*/  dev; } ;
struct dsa_switch {scalar_t__ slave_mii_bus; TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; int /*<<< orphan*/ * dev; } ;
struct dsa_port {int /*<<< orphan*/  pl; int /*<<< orphan*/  index; TYPE_2__ pl_config; struct dsa_switch* ds; struct device_node* dn; } ;
struct device_node {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_phy_flags ) (struct dsa_switch*,int /*<<< orphan*/ ) ;scalar_t__ phylink_fixed_state; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHYLINK_NETDEV ; 
 int PHY_INTERFACE_MODE_NA ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsa_port_phylink_mac_ops ; 
 int dsa_slave_phy_connect (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsa_slave_phylink_fixed_state ; 
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int,...) ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 int of_get_phy_mode (struct device_node*) ; 
 int /*<<< orphan*/  phylink_create (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phylink_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phylink_fixed_state_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phylink_of_phy_connect (int /*<<< orphan*/ ,struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dsa_switch*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsa_slave_phy_setup(struct net_device *slave_dev)
{
	struct dsa_port *dp = dsa_slave_to_port(slave_dev);
	struct device_node *port_dn = dp->dn;
	struct dsa_switch *ds = dp->ds;
	u32 phy_flags = 0;
	int mode, ret;

	mode = of_get_phy_mode(port_dn);
	if (mode < 0)
		mode = PHY_INTERFACE_MODE_NA;

	dp->pl_config.dev = &slave_dev->dev;
	dp->pl_config.type = PHYLINK_NETDEV;

	dp->pl = phylink_create(&dp->pl_config, of_fwnode_handle(port_dn), mode,
				&dsa_port_phylink_mac_ops);
	if (IS_ERR(dp->pl)) {
		netdev_err(slave_dev,
			   "error creating PHYLINK: %ld\n", PTR_ERR(dp->pl));
		return PTR_ERR(dp->pl);
	}

	/* Register only if the switch provides such a callback, since this
	 * callback takes precedence over polling the link GPIO in PHYLINK
	 * (see phylink_get_fixed_state).
	 */
	if (ds->ops->phylink_fixed_state)
		phylink_fixed_state_cb(dp->pl, dsa_slave_phylink_fixed_state);

	if (ds->ops->get_phy_flags)
		phy_flags = ds->ops->get_phy_flags(ds, dp->index);

	ret = phylink_of_phy_connect(dp->pl, port_dn, phy_flags);
	if (ret == -ENODEV && ds->slave_mii_bus) {
		/* We could not connect to a designated PHY or SFP, so try to
		 * use the switch internal MDIO bus instead
		 */
		ret = dsa_slave_phy_connect(slave_dev, dp->index);
		if (ret) {
			netdev_err(slave_dev,
				   "failed to connect to port %d: %d\n",
				   dp->index, ret);
			phylink_destroy(dp->pl);
			return ret;
		}
	}

	return ret;
}