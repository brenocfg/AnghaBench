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
struct uart_port {int dummy; } ;
struct uart_8250_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  serial8250_set_sleep (struct uart_8250_port*,int) ; 
 struct uart_8250_port* up_to_u8250p (struct uart_port*) ; 

void serial8250_do_pm(struct uart_port *port, unsigned int state,
		      unsigned int oldstate)
{
	struct uart_8250_port *p = up_to_u8250p(port);

	serial8250_set_sleep(p, state != 0);
}