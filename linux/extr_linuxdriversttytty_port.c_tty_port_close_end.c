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
struct tty_struct {scalar_t__ closing; } ;
struct tty_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  open_wait; scalar_t__ close_delay; scalar_t__ blocked_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies_to_msecs (scalar_t__) ; 
 int /*<<< orphan*/  msleep_interruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_ldisc_flush (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_port_set_active (struct tty_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void tty_port_close_end(struct tty_port *port, struct tty_struct *tty)
{
	unsigned long flags;

	tty_ldisc_flush(tty);
	tty->closing = 0;

	spin_lock_irqsave(&port->lock, flags);

	if (port->blocked_open) {
		spin_unlock_irqrestore(&port->lock, flags);
		if (port->close_delay)
			msleep_interruptible(jiffies_to_msecs(port->close_delay));
		spin_lock_irqsave(&port->lock, flags);
		wake_up_interruptible(&port->open_wait);
	}
	spin_unlock_irqrestore(&port->lock, flags);
	tty_port_set_active(port, 0);
}