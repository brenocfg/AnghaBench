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
struct TYPE_2__ {int /*<<< orphan*/  line; int /*<<< orphan*/  dev; } ;
struct uart_omap_port {char const* name; TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct uart_omap_port* to_uart_omap_port (struct uart_port*) ; 

__attribute__((used)) static const char *
serial_omap_type(struct uart_port *port)
{
	struct uart_omap_port *up = to_uart_omap_port(port);

	dev_dbg(up->port.dev, "serial_omap_type+%d\n", up->port.line);
	return up->name;
}