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
struct uart_port {scalar_t__ irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  function; } ;
struct uart_8250_port {TYPE_1__ timer; struct uart_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  serial8250_timeout ; 
 int /*<<< orphan*/  serial_unlink_irq_chain (struct uart_8250_port*) ; 

__attribute__((used)) static void univ8250_release_irq(struct uart_8250_port *up)
{
	struct uart_port *port = &up->port;

	del_timer_sync(&up->timer);
	up->timer.function = serial8250_timeout;
	if (port->irq)
		serial_unlink_irq_chain(up);
}