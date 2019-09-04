#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  parent; int /*<<< orphan*/  of_node; int /*<<< orphan*/ * type; } ;
struct tegra_xusb_port {unsigned int index; TYPE_1__ dev; struct tegra_xusb_padctl* padctl; int /*<<< orphan*/  list; } ;
struct tegra_xusb_padctl {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int dev_set_name (TYPE_1__*,char*,char const*,unsigned int) ; 
 int device_add (TYPE_1__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  device_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  tegra_xusb_port_type ; 

__attribute__((used)) static int tegra_xusb_port_init(struct tegra_xusb_port *port,
				struct tegra_xusb_padctl *padctl,
				struct device_node *np,
				const char *name,
				unsigned int index)
{
	int err;

	INIT_LIST_HEAD(&port->list);
	port->padctl = padctl;
	port->index = index;

	device_initialize(&port->dev);
	port->dev.type = &tegra_xusb_port_type;
	port->dev.of_node = of_node_get(np);
	port->dev.parent = padctl->dev;

	err = dev_set_name(&port->dev, "%s-%u", name, index);
	if (err < 0)
		goto unregister;

	err = device_add(&port->dev);
	if (err < 0)
		goto unregister;

	return 0;

unregister:
	device_unregister(&port->dev);
	return err;
}