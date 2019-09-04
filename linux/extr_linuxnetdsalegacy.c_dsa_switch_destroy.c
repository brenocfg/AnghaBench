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
struct dsa_switch {int num_ports; scalar_t__ slave_mii_bus; TYPE_1__* ops; TYPE_2__* ports; } ;
struct TYPE_4__ {int /*<<< orphan*/  slave; } ;
struct TYPE_3__ {scalar_t__ phy_read; } ;

/* Variables and functions */
 scalar_t__ dsa_is_cpu_port (struct dsa_switch*,int) ; 
 scalar_t__ dsa_is_dsa_port (struct dsa_switch*,int) ; 
 int /*<<< orphan*/  dsa_is_user_port (struct dsa_switch*,int) ; 
 int /*<<< orphan*/  dsa_port_link_unregister_of (TYPE_2__*) ; 
 int /*<<< orphan*/  dsa_slave_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsa_switch_unregister_notifier (struct dsa_switch*) ; 
 int /*<<< orphan*/  mdiobus_unregister (scalar_t__) ; 

__attribute__((used)) static void dsa_switch_destroy(struct dsa_switch *ds)
{
	int port;

	/* Destroy network devices for physical switch ports. */
	for (port = 0; port < ds->num_ports; port++) {
		if (!dsa_is_user_port(ds, port))
			continue;

		if (!ds->ports[port].slave)
			continue;

		dsa_slave_destroy(ds->ports[port].slave);
	}

	/* Disable configuration of the CPU and DSA ports */
	for (port = 0; port < ds->num_ports; port++) {
		if (!(dsa_is_cpu_port(ds, port) || dsa_is_dsa_port(ds, port)))
			continue;
		dsa_port_link_unregister_of(&ds->ports[port]);
	}

	if (ds->slave_mii_bus && ds->ops->phy_read)
		mdiobus_unregister(ds->slave_mii_bus);

	dsa_switch_unregister_notifier(ds);
}