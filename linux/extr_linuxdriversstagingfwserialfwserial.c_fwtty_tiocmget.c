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
struct tty_struct {struct fwtty_port* driver_data; } ;
struct fwtty_port {unsigned int mctrl; unsigned int mstatus; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned int MCTRL_MASK ; 
 int /*<<< orphan*/  fwtty_dbg (struct fwtty_port*,char*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fwtty_tiocmget(struct tty_struct *tty)
{
	struct fwtty_port *port = tty->driver_data;
	unsigned int tiocm;

	spin_lock_bh(&port->lock);
	tiocm = (port->mctrl & MCTRL_MASK) | (port->mstatus & ~MCTRL_MASK);
	spin_unlock_bh(&port->lock);

	fwtty_dbg(port, "%x\n", tiocm);

	return tiocm;
}