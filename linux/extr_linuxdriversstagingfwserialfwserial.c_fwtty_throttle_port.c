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
struct tty_struct {int dummy; } ;
struct fwtty_port {unsigned int mctrl; int /*<<< orphan*/  lock; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 scalar_t__ C_CRTSCTS (struct tty_struct*) ; 
 unsigned int OOB_RX_THROTTLE ; 
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  __fwtty_write_port_status (struct fwtty_port*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fwtty_throttle_port(struct fwtty_port *port)
{
	struct tty_struct *tty;
	unsigned int old;

	tty = tty_port_tty_get(&port->port);
	if (!tty)
		return;

	spin_lock_bh(&port->lock);

	old = port->mctrl;
	port->mctrl |= OOB_RX_THROTTLE;
	if (C_CRTSCTS(tty))
		port->mctrl &= ~TIOCM_RTS;
	if (~old & OOB_RX_THROTTLE)
		__fwtty_write_port_status(port);

	spin_unlock_bh(&port->lock);

	tty_kref_put(tty);
}