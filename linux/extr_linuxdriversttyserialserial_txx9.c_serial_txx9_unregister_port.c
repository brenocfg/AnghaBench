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
struct TYPE_2__ {int /*<<< orphan*/ * dev; int /*<<< orphan*/ * membase; scalar_t__ mapbase; scalar_t__ iobase; int /*<<< orphan*/  type; scalar_t__ flags; } ;
struct uart_txx9_port {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_UNKNOWN ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serial_txx9_mutex ; 
 struct uart_txx9_port* serial_txx9_ports ; 
 int /*<<< orphan*/  serial_txx9_reg ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void serial_txx9_unregister_port(int line)
{
	struct uart_txx9_port *uart = &serial_txx9_ports[line];

	mutex_lock(&serial_txx9_mutex);
	uart_remove_one_port(&serial_txx9_reg, &uart->port);
	uart->port.flags = 0;
	uart->port.type = PORT_UNKNOWN;
	uart->port.iobase = 0;
	uart->port.mapbase = 0;
	uart->port.membase = NULL;
	uart->port.dev = NULL;
	mutex_unlock(&serial_txx9_mutex);
}