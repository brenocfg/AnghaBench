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
struct uart_port {scalar_t__ type; int /*<<< orphan*/  line; } ;

/* Variables and functions */
 scalar_t__ PORT_CPM ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *cpm_uart_type(struct uart_port *port)
{
	pr_debug("CPM uart[%d]:uart_type\n", port->line);

	return port->type == PORT_CPM ? "CPM UART" : NULL;
}