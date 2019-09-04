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
struct tty_port {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  blocked_open; int /*<<< orphan*/  count; int /*<<< orphan*/  open_wait; } ;
struct file {int f_flags; } ;

/* Variables and functions */
 int ASYNC_HUP_NOTIFY ; 
 scalar_t__ C_BAUD (struct tty_struct*) ; 
 scalar_t__ C_CLOCAL (struct tty_struct*) ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int ERESTARTSYS ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ tty_hung_up_p (struct file*) ; 
 scalar_t__ tty_io_error (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_lock (struct tty_struct*) ; 
 scalar_t__ tty_port_carrier_raised (struct tty_port*) ; 
 scalar_t__ tty_port_initialized (struct tty_port*) ; 
 int /*<<< orphan*/  tty_port_raise_dtr_rts (struct tty_port*) ; 
 int /*<<< orphan*/  tty_port_set_active (struct tty_port*,int) ; 
 int /*<<< orphan*/  tty_unlock (struct tty_struct*) ; 
 int /*<<< orphan*/  wait ; 

int tty_port_block_til_ready(struct tty_port *port,
				struct tty_struct *tty, struct file *filp)
{
	int do_clocal = 0, retval;
	unsigned long flags;
	DEFINE_WAIT(wait);

	/* if non-blocking mode is set we can pass directly to open unless
	   the port has just hung up or is in another error state */
	if (tty_io_error(tty)) {
		tty_port_set_active(port, 1);
		return 0;
	}
	if (filp == NULL || (filp->f_flags & O_NONBLOCK)) {
		/* Indicate we are open */
		if (C_BAUD(tty))
			tty_port_raise_dtr_rts(port);
		tty_port_set_active(port, 1);
		return 0;
	}

	if (C_CLOCAL(tty))
		do_clocal = 1;

	/* Block waiting until we can proceed. We may need to wait for the
	   carrier, but we must also wait for any close that is in progress
	   before the next open may complete */

	retval = 0;

	/* The port lock protects the port counts */
	spin_lock_irqsave(&port->lock, flags);
	port->count--;
	port->blocked_open++;
	spin_unlock_irqrestore(&port->lock, flags);

	while (1) {
		/* Indicate we are open */
		if (C_BAUD(tty) && tty_port_initialized(port))
			tty_port_raise_dtr_rts(port);

		prepare_to_wait(&port->open_wait, &wait, TASK_INTERRUPTIBLE);
		/* Check for a hangup or uninitialised port.
							Return accordingly */
		if (tty_hung_up_p(filp) || !tty_port_initialized(port)) {
			if (port->flags & ASYNC_HUP_NOTIFY)
				retval = -EAGAIN;
			else
				retval = -ERESTARTSYS;
			break;
		}
		/*
		 * Probe the carrier. For devices with no carrier detect
		 * tty_port_carrier_raised will always return true.
		 * Never ask drivers if CLOCAL is set, this causes troubles
		 * on some hardware.
		 */
		if (do_clocal || tty_port_carrier_raised(port))
			break;
		if (signal_pending(current)) {
			retval = -ERESTARTSYS;
			break;
		}
		tty_unlock(tty);
		schedule();
		tty_lock(tty);
	}
	finish_wait(&port->open_wait, &wait);

	/* Update counts. A parallel hangup will have set count to zero and
	   we must not mess that up further */
	spin_lock_irqsave(&port->lock, flags);
	if (!tty_hung_up_p(filp))
		port->count++;
	port->blocked_open--;
	spin_unlock_irqrestore(&port->lock, flags);
	if (retval == 0)
		tty_port_set_active(port, 1);
	return retval;
}