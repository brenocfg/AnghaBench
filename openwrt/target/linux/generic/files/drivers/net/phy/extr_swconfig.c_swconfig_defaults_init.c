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
struct switch_dev_ops {int /*<<< orphan*/  attr_port; scalar_t__ get_port_link; scalar_t__ set_port_pvid; scalar_t__ get_port_pvid; scalar_t__ set_vlan_ports; scalar_t__ get_vlan_ports; } ;
struct switch_dev {scalar_t__ def_global; scalar_t__ def_port; scalar_t__ def_vlan; struct switch_dev_ops* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLOBAL_APPLY ; 
 int /*<<< orphan*/  GLOBAL_RESET ; 
 int /*<<< orphan*/  PORT_LINK ; 
 int /*<<< orphan*/  PORT_PVID ; 
 int /*<<< orphan*/  VLAN_PORTS ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  swconfig_find_attr_by_name (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void swconfig_defaults_init(struct switch_dev *dev)
{
	const struct switch_dev_ops *ops = dev->ops;

	dev->def_global = 0;
	dev->def_vlan = 0;
	dev->def_port = 0;

	if (ops->get_vlan_ports || ops->set_vlan_ports)
		set_bit(VLAN_PORTS, &dev->def_vlan);

	if (ops->get_port_pvid || ops->set_port_pvid)
		set_bit(PORT_PVID, &dev->def_port);

	if (ops->get_port_link &&
	    !swconfig_find_attr_by_name(&ops->attr_port, "link"))
		set_bit(PORT_LINK, &dev->def_port);

	/* always present, can be no-op */
	set_bit(GLOBAL_APPLY, &dev->def_global);
	set_bit(GLOBAL_RESET, &dev->def_global);
}