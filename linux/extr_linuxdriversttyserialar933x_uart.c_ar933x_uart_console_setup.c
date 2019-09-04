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
struct console {size_t index; } ;
struct ar933x_uart_port {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 size_t CONFIG_SERIAL_AR933X_NR_UARTS ; 
 int EINVAL ; 
 int ENODEV ; 
 struct ar933x_uart_port** ar933x_console_ports ; 
 int /*<<< orphan*/  uart_parse_options (char*,int*,int*,int*,int*) ; 
 int uart_set_options (int /*<<< orphan*/ *,struct console*,int,int,int,int) ; 

__attribute__((used)) static int ar933x_uart_console_setup(struct console *co, char *options)
{
	struct ar933x_uart_port *up;
	int baud = 115200;
	int bits = 8;
	int parity = 'n';
	int flow = 'n';

	if (co->index < 0 || co->index >= CONFIG_SERIAL_AR933X_NR_UARTS)
		return -EINVAL;

	up = ar933x_console_ports[co->index];
	if (!up)
		return -ENODEV;

	if (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	return uart_set_options(&up->port, co, baud, parity, bits, flow);
}