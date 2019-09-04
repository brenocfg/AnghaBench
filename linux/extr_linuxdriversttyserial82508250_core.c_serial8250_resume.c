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
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/ * dev; } ;
struct uart_8250_port {TYPE_1__ port; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ PORT_UNKNOWN ; 
 int UART_NR ; 
 struct uart_8250_port* serial8250_ports ; 
 int /*<<< orphan*/  serial8250_resume_port (int) ; 

__attribute__((used)) static int serial8250_resume(struct platform_device *dev)
{
	int i;

	for (i = 0; i < UART_NR; i++) {
		struct uart_8250_port *up = &serial8250_ports[i];

		if (up->port.type != PORT_UNKNOWN && up->port.dev == &dev->dev)
			serial8250_resume_port(i);
	}

	return 0;
}