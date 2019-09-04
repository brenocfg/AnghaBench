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
struct TYPE_3__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_4__ {int line; } ;
struct mps2_uart_port {TYPE_2__ port; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int MPS2_MAX_PORTS ; 
 scalar_t__ WARN_ON (int) ; 
 struct mps2_uart_port* mps2_uart_ports ; 
 int of_alias_get_id (struct device_node*,char*) ; 

__attribute__((used)) static struct mps2_uart_port *mps2_of_get_port(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	int id;

	if (!np)
		return NULL;

	id = of_alias_get_id(np, "serial");
	if (id < 0)
		id = 0;

	if (WARN_ON(id >= MPS2_MAX_PORTS))
		return NULL;

	mps2_uart_ports[id].port.line = id;
	return &mps2_uart_ports[id];
}