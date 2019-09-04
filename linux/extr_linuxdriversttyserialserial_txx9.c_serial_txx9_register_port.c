#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; int line; scalar_t__ dev; scalar_t__ mapbase; int /*<<< orphan*/  iotype; int /*<<< orphan*/  uartclk; int /*<<< orphan*/  irq; int /*<<< orphan*/  membase; scalar_t__ iobase; } ;
struct uart_txx9_port {TYPE_1__ port; } ;
struct uart_port {int flags; scalar_t__ dev; scalar_t__ mapbase; int /*<<< orphan*/  iotype; int /*<<< orphan*/  uartclk; int /*<<< orphan*/  irq; int /*<<< orphan*/  membase; scalar_t__ iobase; } ;

/* Variables and functions */
 int ENOSPC ; 
 int UART_NR ; 
 int UPF_BOOT_AUTOCONF ; 
 int UPF_FIXED_PORT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serial_txx9_mutex ; 
 struct uart_txx9_port* serial_txx9_ports ; 
 int /*<<< orphan*/  serial_txx9_reg ; 
 int uart_add_one_port (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ uart_match_port (TYPE_1__*,struct uart_port*) ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int serial_txx9_register_port(struct uart_port *port)
{
	int i;
	struct uart_txx9_port *uart;
	int ret = -ENOSPC;

	mutex_lock(&serial_txx9_mutex);
	for (i = 0; i < UART_NR; i++) {
		uart = &serial_txx9_ports[i];
		if (uart_match_port(&uart->port, port)) {
			uart_remove_one_port(&serial_txx9_reg, &uart->port);
			break;
		}
	}
	if (i == UART_NR) {
		/* Find unused port */
		for (i = 0; i < UART_NR; i++) {
			uart = &serial_txx9_ports[i];
			if (!(uart->port.iobase || uart->port.mapbase))
				break;
		}
	}
	if (i < UART_NR) {
		uart->port.iobase = port->iobase;
		uart->port.membase = port->membase;
		uart->port.irq      = port->irq;
		uart->port.uartclk  = port->uartclk;
		uart->port.iotype   = port->iotype;
		uart->port.flags    = port->flags
			| UPF_BOOT_AUTOCONF | UPF_FIXED_PORT;
		uart->port.mapbase  = port->mapbase;
		if (port->dev)
			uart->port.dev = port->dev;
		ret = uart_add_one_port(&serial_txx9_reg, &uart->port);
		if (ret == 0)
			ret = uart->port.line;
	}
	mutex_unlock(&serial_txx9_mutex);
	return ret;
}