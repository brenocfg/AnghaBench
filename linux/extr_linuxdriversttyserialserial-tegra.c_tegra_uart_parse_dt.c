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
struct TYPE_3__ {int line; } ;
struct tegra_uart_port {int /*<<< orphan*/  enable_modem_interrupt; TYPE_1__ uport; } ;
struct TYPE_4__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 int of_alias_get_id (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 

__attribute__((used)) static int tegra_uart_parse_dt(struct platform_device *pdev,
	struct tegra_uart_port *tup)
{
	struct device_node *np = pdev->dev.of_node;
	int port;

	port = of_alias_get_id(np, "serial");
	if (port < 0) {
		dev_err(&pdev->dev, "failed to get alias id, errno %d\n", port);
		return port;
	}
	tup->uport.line = port;

	tup->enable_modem_interrupt = of_property_read_bool(np,
					"nvidia,enable-modem-interrupt");
	return 0;
}