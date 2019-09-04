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
struct uart_port {int dummy; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  type; int /*<<< orphan*/  line; int /*<<< orphan*/  dev; } ;
struct uart_omap_port {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_OMAP ; 
 int UPF_HARD_FLOW ; 
 int UPF_SOFT_FLOW ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct uart_omap_port* to_uart_omap_port (struct uart_port*) ; 

__attribute__((used)) static void serial_omap_config_port(struct uart_port *port, int flags)
{
	struct uart_omap_port *up = to_uart_omap_port(port);

	dev_dbg(up->port.dev, "serial_omap_config_port+%d\n",
							up->port.line);
	up->port.type = PORT_OMAP;
	up->port.flags |= UPF_SOFT_FLOW | UPF_HARD_FLOW;
}