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
struct uart_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;
struct ktermios {scalar_t__ c_line; int /*<<< orphan*/  c_cflag; } ;

/* Variables and functions */
 scalar_t__ N_PPS ; 
 int /*<<< orphan*/  UART_ENABLE_MS (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPF_HARDPPS_CD ; 
 int /*<<< orphan*/  serial8250_disable_ms (struct uart_port*) ; 
 int /*<<< orphan*/  serial8250_enable_ms (struct uart_port*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void serial8250_do_set_ldisc(struct uart_port *port, struct ktermios *termios)
{
	if (termios->c_line == N_PPS) {
		port->flags |= UPF_HARDPPS_CD;
		spin_lock_irq(&port->lock);
		serial8250_enable_ms(port);
		spin_unlock_irq(&port->lock);
	} else {
		port->flags &= ~UPF_HARDPPS_CD;
		if (!UART_ENABLE_MS(port, termios->c_cflag)) {
			spin_lock_irq(&port->lock);
			serial8250_disable_ms(port);
			spin_unlock_irq(&port->lock);
		}
	}
}