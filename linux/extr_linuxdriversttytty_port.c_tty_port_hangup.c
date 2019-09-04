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
struct tty_struct {int /*<<< orphan*/  flags; } ;
struct tty_port {int /*<<< orphan*/  delta_msr_wait; int /*<<< orphan*/  open_wait; int /*<<< orphan*/  lock; struct tty_struct* tty; scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_IO_ERROR ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_port_set_active (struct tty_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_port_shutdown (struct tty_port*,struct tty_struct*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void tty_port_hangup(struct tty_port *port)
{
	struct tty_struct *tty;
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);
	port->count = 0;
	tty = port->tty;
	if (tty)
		set_bit(TTY_IO_ERROR, &tty->flags);
	port->tty = NULL;
	spin_unlock_irqrestore(&port->lock, flags);
	tty_port_set_active(port, 0);
	tty_port_shutdown(port, tty);
	tty_kref_put(tty);
	wake_up_interruptible(&port->open_wait);
	wake_up_interruptible(&port->delta_msr_wait);
}