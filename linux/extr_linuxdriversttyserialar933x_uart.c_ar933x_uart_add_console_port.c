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
struct TYPE_2__ {size_t line; } ;
struct ar933x_uart_port {TYPE_1__ port; } ;

/* Variables and functions */
 struct ar933x_uart_port** ar933x_console_ports ; 
 int /*<<< orphan*/  ar933x_uart_console_enabled () ; 

__attribute__((used)) static void ar933x_uart_add_console_port(struct ar933x_uart_port *up)
{
	if (!ar933x_uart_console_enabled())
		return;

	ar933x_console_ports[up->port.line] = up;
}