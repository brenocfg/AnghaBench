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
struct uart_port {int (* startup ) (struct uart_port*) ;} ;

/* Variables and functions */
 int serial8250_do_startup (struct uart_port*) ; 
 int stub1 (struct uart_port*) ; 

__attribute__((used)) static int serial8250_startup(struct uart_port *port)
{
	if (port->startup)
		return port->startup(port);
	return serial8250_do_startup(port);
}