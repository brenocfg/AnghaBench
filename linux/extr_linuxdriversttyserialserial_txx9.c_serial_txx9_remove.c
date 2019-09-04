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
struct TYPE_2__ {int /*<<< orphan*/ * dev; } ;
struct uart_txx9_port {TYPE_1__ port; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int UART_NR ; 
 struct uart_txx9_port* serial_txx9_ports ; 
 int /*<<< orphan*/  serial_txx9_unregister_port (int) ; 

__attribute__((used)) static int serial_txx9_remove(struct platform_device *dev)
{
	int i;

	for (i = 0; i < UART_NR; i++) {
		struct uart_txx9_port *up = &serial_txx9_ports[i];

		if (up->port.dev == &dev->dev)
			serial_txx9_unregister_port(i);
	}
	return 0;
}