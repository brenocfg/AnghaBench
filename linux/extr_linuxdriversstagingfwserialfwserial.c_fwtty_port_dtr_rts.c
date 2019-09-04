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
struct tty_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  console; } ;
struct fwtty_port {int mctrl; int /*<<< orphan*/  lock; TYPE_1__ port; } ;

/* Variables and functions */
 int TIOCM_DTR ; 
 int TIOCM_RTS ; 
 int /*<<< orphan*/  __fwtty_write_port_status (struct fwtty_port*) ; 
 int /*<<< orphan*/  fwtty_dbg (struct fwtty_port*,char*,int) ; 
 struct fwtty_port* port ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct fwtty_port* to_port (struct tty_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fwtty_port_dtr_rts(struct tty_port *tty_port, int on)
{
	struct fwtty_port *port = to_port(tty_port, port);

	fwtty_dbg(port, "on/off: %d\n", on);

	spin_lock_bh(&port->lock);
	/* Don't change carrier state if this is a console */
	if (!port->port.console) {
		if (on)
			port->mctrl |= TIOCM_DTR | TIOCM_RTS;
		else
			port->mctrl &= ~(TIOCM_DTR | TIOCM_RTS);
	}

	__fwtty_write_port_status(port);
	spin_unlock_bh(&port->lock);
}