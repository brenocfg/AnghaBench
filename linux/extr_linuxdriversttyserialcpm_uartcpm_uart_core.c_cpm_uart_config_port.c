#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct uart_port {int /*<<< orphan*/  type; int /*<<< orphan*/  line; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_CPM ; 
 int UART_CONFIG_TYPE ; 
 int /*<<< orphan*/  cpm_uart_request_port (struct uart_port*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpm_uart_config_port(struct uart_port *port, int flags)
{
	pr_debug("CPM uart[%d]:config_port\n", port->line);

	if (flags & UART_CONFIG_TYPE) {
		port->type = PORT_CPM;
		cpm_uart_request_port(port);
	}
}