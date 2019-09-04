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
struct uart_state {int /*<<< orphan*/  xmit; } ;
struct uart_port {int dummy; } ;
struct tty_struct {struct uart_state* driver_data; } ;

/* Variables and functions */
 int uart_circ_chars_free (int /*<<< orphan*/ *) ; 
 struct uart_port* uart_port_lock (struct uart_state*,unsigned long) ; 
 int /*<<< orphan*/  uart_port_unlock (struct uart_port*,unsigned long) ; 

__attribute__((used)) static int uart_write_room(struct tty_struct *tty)
{
	struct uart_state *state = tty->driver_data;
	struct uart_port *port;
	unsigned long flags;
	int ret;

	port = uart_port_lock(state, flags);
	ret = uart_circ_chars_free(&state->xmit);
	uart_port_unlock(port, flags);
	return ret;
}