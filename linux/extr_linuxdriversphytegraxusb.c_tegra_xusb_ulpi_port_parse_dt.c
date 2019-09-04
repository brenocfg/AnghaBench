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
struct tegra_xusb_ulpi_port {int /*<<< orphan*/  internal; struct tegra_xusb_port base; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 

__attribute__((used)) static int tegra_xusb_ulpi_port_parse_dt(struct tegra_xusb_ulpi_port *ulpi)
{
	struct tegra_xusb_port *port = &ulpi->base;
	struct device_node *np = port->dev.of_node;

	ulpi->internal = of_property_read_bool(np, "nvidia,internal");

	return 0;
}