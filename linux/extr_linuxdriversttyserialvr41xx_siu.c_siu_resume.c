#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uart_port {scalar_t__ type; int /*<<< orphan*/ * dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int nr; } ;

/* Variables and functions */
 scalar_t__ PORT_VR41XX_DSIU ; 
 scalar_t__ PORT_VR41XX_SIU ; 
 TYPE_1__ siu_uart_driver ; 
 struct uart_port* siu_uart_ports ; 
 int /*<<< orphan*/  uart_resume_port (TYPE_1__*,struct uart_port*) ; 

__attribute__((used)) static int siu_resume(struct platform_device *dev)
{
	struct uart_port *port;
	int i;

	for (i = 0; i < siu_uart_driver.nr; i++) {
		port = &siu_uart_ports[i];
		if ((port->type == PORT_VR41XX_SIU ||
		     port->type == PORT_VR41XX_DSIU) && port->dev == &dev->dev)
			uart_resume_port(&siu_uart_driver, port);
	}

	return 0;
}