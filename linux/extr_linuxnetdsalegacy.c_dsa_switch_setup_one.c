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
struct net_device {int dummy; } ;
struct dsa_switch_tree {struct dsa_port* cpu_dp; } ;
struct dsa_switch_ops {int (* get_tag_protocol ) (struct dsa_switch*,int /*<<< orphan*/ ) ;int (* setup ) (struct dsa_switch*) ;scalar_t__ phy_read; } ;
struct dsa_switch {int index; int num_ports; struct dsa_port* ports; int /*<<< orphan*/  slave_mii_bus; int /*<<< orphan*/  dev; int /*<<< orphan*/  rtable; int /*<<< orphan*/  phys_mii_mask; struct dsa_chip_data* cd; struct dsa_switch_tree* dst; struct dsa_switch_ops* ops; } ;
struct dsa_port {char* name; struct dsa_port* cpu_dp; int /*<<< orphan*/  dn; struct dsa_switch_tree* dst; struct dsa_device_ops const* tag_ops; int /*<<< orphan*/  rcv; int /*<<< orphan*/  index; struct dsa_switch* ds; int /*<<< orphan*/  type; struct net_device* master; } ;
struct dsa_device_ops {int /*<<< orphan*/  rcv; } ;
struct dsa_chip_data {char** port_names; int /*<<< orphan*/ * port_dn; int /*<<< orphan*/  rtable; } ;
typedef  enum dsa_tag_protocol { ____Placeholder_dsa_tag_protocol } dsa_tag_protocol ;

/* Variables and functions */
 int /*<<< orphan*/  DSA_PORT_TYPE_CPU ; 
 int /*<<< orphan*/  DSA_PORT_TYPE_DSA ; 
 int /*<<< orphan*/  DSA_PORT_TYPE_USER ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct dsa_device_ops const*) ; 
 int PTR_ERR (struct dsa_device_ops const*) ; 
 int /*<<< orphan*/  devm_mdiobus_alloc (int /*<<< orphan*/ ) ; 
 int dsa_cpu_dsa_setups (struct dsa_switch*) ; 
 int /*<<< orphan*/  dsa_is_user_port (struct dsa_switch*,int) ; 
 struct dsa_device_ops* dsa_resolve_tag_protocol (int) ; 
 int dsa_slave_create (struct dsa_port*) ; 
 int /*<<< orphan*/  dsa_slave_mii_bus_init (struct dsa_switch*) ; 
 int dsa_switch_register_notifier (struct dsa_switch*) ; 
 int /*<<< orphan*/  dsa_user_ports (struct dsa_switch*) ; 
 int mdiobus_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int stub1 (struct dsa_switch*,int /*<<< orphan*/ ) ; 
 int stub2 (struct dsa_switch*) ; 

__attribute__((used)) static int dsa_switch_setup_one(struct dsa_switch *ds,
				struct net_device *master)
{
	const struct dsa_switch_ops *ops = ds->ops;
	struct dsa_switch_tree *dst = ds->dst;
	struct dsa_chip_data *cd = ds->cd;
	bool valid_name_found = false;
	int index = ds->index;
	struct dsa_port *dp;
	int i, ret;

	/*
	 * Validate supplied switch configuration.
	 */
	for (i = 0; i < ds->num_ports; i++) {
		char *name;

		dp = &ds->ports[i];

		name = cd->port_names[i];
		if (name == NULL)
			continue;
		dp->name = name;

		if (!strcmp(name, "cpu")) {
			if (dst->cpu_dp) {
				netdev_err(master,
					   "multiple cpu ports?!\n");
				return -EINVAL;
			}
			dst->cpu_dp = &ds->ports[i];
			dst->cpu_dp->master = master;
			dp->type = DSA_PORT_TYPE_CPU;
		} else if (!strcmp(name, "dsa")) {
			dp->type = DSA_PORT_TYPE_DSA;
		} else {
			dp->type = DSA_PORT_TYPE_USER;
		}
		valid_name_found = true;
	}

	if (!valid_name_found && i == ds->num_ports)
		return -EINVAL;

	/* Make the built-in MII bus mask match the number of ports,
	 * switch drivers can override this later
	 */
	ds->phys_mii_mask |= dsa_user_ports(ds);

	/*
	 * If the CPU connects to this switch, set the switch tree
	 * tagging protocol to the preferred tagging format of this
	 * switch.
	 */
	if (dst->cpu_dp->ds == ds) {
		const struct dsa_device_ops *tag_ops;
		enum dsa_tag_protocol tag_protocol;

		tag_protocol = ops->get_tag_protocol(ds, dst->cpu_dp->index);
		tag_ops = dsa_resolve_tag_protocol(tag_protocol);
		if (IS_ERR(tag_ops))
			return PTR_ERR(tag_ops);

		dst->cpu_dp->tag_ops = tag_ops;

		/* Few copies for faster access in master receive hot path */
		dst->cpu_dp->rcv = dst->cpu_dp->tag_ops->rcv;
		dst->cpu_dp->dst = dst;
	}

	memcpy(ds->rtable, cd->rtable, sizeof(ds->rtable));

	/*
	 * Do basic register setup.
	 */
	ret = ops->setup(ds);
	if (ret < 0)
		return ret;

	ret = dsa_switch_register_notifier(ds);
	if (ret)
		return ret;

	if (!ds->slave_mii_bus && ops->phy_read) {
		ds->slave_mii_bus = devm_mdiobus_alloc(ds->dev);
		if (!ds->slave_mii_bus)
			return -ENOMEM;
		dsa_slave_mii_bus_init(ds);

		ret = mdiobus_register(ds->slave_mii_bus);
		if (ret < 0)
			return ret;
	}

	/*
	 * Create network devices for physical switch ports.
	 */
	for (i = 0; i < ds->num_ports; i++) {
		ds->ports[i].dn = cd->port_dn[i];
		ds->ports[i].cpu_dp = dst->cpu_dp;

		if (!dsa_is_user_port(ds, i))
			continue;

		ret = dsa_slave_create(&ds->ports[i]);
		if (ret < 0)
			netdev_err(master, "[%d]: can't create dsa slave device for port %d(%s): %d\n",
				   index, i, cd->port_names[i], ret);
	}

	/* Perform configuration of the CPU and DSA ports */
	ret = dsa_cpu_dsa_setups(ds);
	if (ret < 0)
		netdev_err(master, "[%d] : can't configure CPU and DSA ports\n",
			   index);

	return 0;
}