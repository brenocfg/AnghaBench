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
struct TYPE_2__ {struct fintek_8250* private_data; int /*<<< orphan*/  dev; } ;
struct uart_8250_port {TYPE_1__ port; } ;
struct fintek_8250 {int dummy; } ;
typedef  int /*<<< orphan*/  probe_data ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct fintek_8250* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fintek_8250_set_rs485_handler (struct uart_8250_port*) ; 
 int /*<<< orphan*/  fintek_8250_set_termios_handler (struct uart_8250_port*) ; 
 int /*<<< orphan*/  memcpy (struct fintek_8250*,struct fintek_8250*,int) ; 
 scalar_t__ probe_setup_port (struct fintek_8250*,struct uart_8250_port*) ; 

int fintek_8250_probe(struct uart_8250_port *uart)
{
	struct fintek_8250 *pdata;
	struct fintek_8250 probe_data;

	if (probe_setup_port(&probe_data, uart))
		return -ENODEV;

	pdata = devm_kzalloc(uart->port.dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return -ENOMEM;

	memcpy(pdata, &probe_data, sizeof(probe_data));
	uart->port.private_data = pdata;
	fintek_8250_set_rs485_handler(uart);
	fintek_8250_set_termios_handler(uart);

	return 0;
}