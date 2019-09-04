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
struct TYPE_2__ {struct device_node* of_node; } ;
struct tegra_xusb_port {TYPE_1__ dev; } ;
struct tegra_xusb_usb2_port {int /*<<< orphan*/  supply; int /*<<< orphan*/  internal; struct tegra_xusb_port base; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regulator_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 

__attribute__((used)) static int tegra_xusb_usb2_port_parse_dt(struct tegra_xusb_usb2_port *usb2)
{
	struct tegra_xusb_port *port = &usb2->base;
	struct device_node *np = port->dev.of_node;

	usb2->internal = of_property_read_bool(np, "nvidia,internal");

	usb2->supply = devm_regulator_get(&port->dev, "vbus");
	return PTR_ERR_OR_ZERO(usb2->supply);
}