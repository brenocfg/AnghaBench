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
struct uart_state {int dummy; } ;
struct uart_port {scalar_t__ type; int fifosize; int timeout; TYPE_1__* ops; int /*<<< orphan*/  line; } ;
struct tty_struct {struct uart_state* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* tx_empty ) (struct uart_port*) ;} ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ PORT_UNKNOWN ; 
 int /*<<< orphan*/  current ; 
 int jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (unsigned long) ; 
 int /*<<< orphan*/  msleep_interruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,unsigned long) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct uart_port*) ; 
 scalar_t__ time_after (int,unsigned long) ; 
 int /*<<< orphan*/  uart_port_deref (struct uart_port*) ; 
 struct uart_port* uart_port_ref (struct uart_state*) ; 

__attribute__((used)) static void uart_wait_until_sent(struct tty_struct *tty, int timeout)
{
	struct uart_state *state = tty->driver_data;
	struct uart_port *port;
	unsigned long char_time, expire;

	port = uart_port_ref(state);
	if (!port)
		return;

	if (port->type == PORT_UNKNOWN || port->fifosize == 0) {
		uart_port_deref(port);
		return;
	}

	/*
	 * Set the check interval to be 1/5 of the estimated time to
	 * send a single character, and make it at least 1.  The check
	 * interval should also be less than the timeout.
	 *
	 * Note: we have to use pretty tight timings here to satisfy
	 * the NIST-PCTS.
	 */
	char_time = (port->timeout - HZ/50) / port->fifosize;
	char_time = char_time / 5;
	if (char_time == 0)
		char_time = 1;
	if (timeout && timeout < char_time)
		char_time = timeout;

	/*
	 * If the transmitter hasn't cleared in twice the approximate
	 * amount of time to send the entire FIFO, it probably won't
	 * ever clear.  This assumes the UART isn't doing flow
	 * control, which is currently the case.  Hence, if it ever
	 * takes longer than port->timeout, this is probably due to a
	 * UART bug of some kind.  So, we clamp the timeout parameter at
	 * 2*port->timeout.
	 */
	if (timeout == 0 || timeout > 2 * port->timeout)
		timeout = 2 * port->timeout;

	expire = jiffies + timeout;

	pr_debug("uart_wait_until_sent(%d), jiffies=%lu, expire=%lu...\n",
		port->line, jiffies, expire);

	/*
	 * Check whether the transmitter is empty every 'char_time'.
	 * 'timeout' / 'expire' give us the maximum amount of time
	 * we wait.
	 */
	while (!port->ops->tx_empty(port)) {
		msleep_interruptible(jiffies_to_msecs(char_time));
		if (signal_pending(current))
			break;
		if (time_after(jiffies, expire))
			break;
	}
	uart_port_deref(port);
}