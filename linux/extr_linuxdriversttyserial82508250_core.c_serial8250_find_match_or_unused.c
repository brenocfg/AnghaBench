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
struct uart_port {int line; } ;
struct TYPE_2__ {scalar_t__ type; scalar_t__ iobase; } ;
struct uart_8250_port {TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ PORT_UNKNOWN ; 
 int nr_uarts ; 
 struct uart_8250_port* serial8250_ports ; 
 scalar_t__ uart_match_port (TYPE_1__*,struct uart_port*) ; 

__attribute__((used)) static struct uart_8250_port *serial8250_find_match_or_unused(struct uart_port *port)
{
	int i;

	/*
	 * First, find a port entry which matches.
	 */
	for (i = 0; i < nr_uarts; i++)
		if (uart_match_port(&serial8250_ports[i].port, port))
			return &serial8250_ports[i];

	/* try line number first if still available */
	i = port->line;
	if (i < nr_uarts && serial8250_ports[i].port.type == PORT_UNKNOWN &&
			serial8250_ports[i].port.iobase == 0)
		return &serial8250_ports[i];
	/*
	 * We didn't find a matching entry, so look for the first
	 * free entry.  We look for one which hasn't been previously
	 * used (indicated by zero iobase).
	 */
	for (i = 0; i < nr_uarts; i++)
		if (serial8250_ports[i].port.type == PORT_UNKNOWN &&
		    serial8250_ports[i].port.iobase == 0)
			return &serial8250_ports[i];

	/*
	 * That also failed.  Last resort is to find any entry which
	 * doesn't have a real port associated with it.
	 */
	for (i = 0; i < nr_uarts; i++)
		if (serial8250_ports[i].port.type == PORT_UNKNOWN)
			return &serial8250_ports[i];

	return NULL;
}