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
struct tty_struct {int hw_stopped; int /*<<< orphan*/  flags; } ;
struct tty_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  console; } ;
struct fwtty_port {int mctrl; int mstatus; int /*<<< orphan*/  lock; TYPE_1__ port; int /*<<< orphan*/  max_payload; int /*<<< orphan*/  tx_fifo; } ;

/* Variables and functions */
 scalar_t__ C_CRTSCTS (struct tty_struct*) ; 
 int /*<<< orphan*/  FWTTY_PORT_MAX_PEND_DMA ; 
 int /*<<< orphan*/  FWTTY_PORT_TXFIFO_LEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TIOCM_CTS ; 
 int TIOCM_DTR ; 
 int TIOCM_RTS ; 
 int /*<<< orphan*/  TTY_IO_ERROR ; 
 int /*<<< orphan*/  __fwtty_write_port_status (struct fwtty_port*) ; 
 int /*<<< orphan*/  cache_line_size () ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dma_fifo_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fwtty_port* port ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int set_termios (struct fwtty_port*,struct tty_struct*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct fwtty_port* to_port (struct tty_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fwtty_port_activate(struct tty_port *tty_port,
			       struct tty_struct *tty)
{
	struct fwtty_port *port = to_port(tty_port, port);
	unsigned int baud;
	int err;

	set_bit(TTY_IO_ERROR, &tty->flags);

	err = dma_fifo_alloc(&port->tx_fifo, FWTTY_PORT_TXFIFO_LEN,
			     cache_line_size(),
			     port->max_payload,
			     FWTTY_PORT_MAX_PEND_DMA,
			     GFP_KERNEL);
	if (err)
		return err;

	spin_lock_bh(&port->lock);

	baud = set_termios(port, tty);

	/* if console, don't change carrier state */
	if (!port->port.console) {
		port->mctrl = 0;
		if (baud != 0)
			port->mctrl = TIOCM_DTR | TIOCM_RTS;
	}

	if (C_CRTSCTS(tty) && ~port->mstatus & TIOCM_CTS)
		tty->hw_stopped = 1;

	__fwtty_write_port_status(port);
	spin_unlock_bh(&port->lock);

	clear_bit(TTY_IO_ERROR, &tty->flags);

	return 0;
}