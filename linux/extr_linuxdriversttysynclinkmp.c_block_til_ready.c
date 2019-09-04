#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {TYPE_1__* driver; } ;
struct tty_port {int flags; int /*<<< orphan*/  count; int /*<<< orphan*/  blocked_open; int /*<<< orphan*/  open_wait; } ;
struct file {int f_flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; struct tty_port port; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ SLMP_INFO ;

/* Variables and functions */
 int ASYNC_HUP_NOTIFY ; 
 scalar_t__ C_BAUD (struct tty_struct*) ; 
 scalar_t__ C_CLOCAL (struct tty_struct*) ; 
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int ERESTARTSYS ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ tty_hung_up_p (struct file*) ; 
 scalar_t__ tty_io_error (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_lock (struct tty_struct*) ; 
 int tty_port_carrier_raised (struct tty_port*) ; 
 scalar_t__ tty_port_initialized (struct tty_port*) ; 
 int /*<<< orphan*/  tty_port_raise_dtr_rts (struct tty_port*) ; 
 int /*<<< orphan*/  tty_port_set_active (struct tty_port*,int) ; 
 int /*<<< orphan*/  tty_unlock (struct tty_struct*) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int block_til_ready(struct tty_struct *tty, struct file *filp,
			   SLMP_INFO *info)
{
	DECLARE_WAITQUEUE(wait, current);
	int		retval;
	bool		do_clocal = false;
	unsigned long	flags;
	int		cd;
	struct tty_port *port = &info->port;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):%s block_til_ready()\n",
			 __FILE__,__LINE__, tty->driver->name );

	if (filp->f_flags & O_NONBLOCK || tty_io_error(tty)) {
		/* nonblock mode is set or port is not enabled */
		/* just verify that callout device is not active */
		tty_port_set_active(port, 1);
		return 0;
	}

	if (C_CLOCAL(tty))
		do_clocal = true;

	/* Wait for carrier detect and the line to become
	 * free (i.e., not in use by the callout).  While we are in
	 * this loop, port->count is dropped by one, so that
	 * close() knows when to free things.  We restore it upon
	 * exit, either normal or abnormal.
	 */

	retval = 0;
	add_wait_queue(&port->open_wait, &wait);

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):%s block_til_ready() before block, count=%d\n",
			 __FILE__,__LINE__, tty->driver->name, port->count );

	spin_lock_irqsave(&info->lock, flags);
	port->count--;
	spin_unlock_irqrestore(&info->lock, flags);
	port->blocked_open++;

	while (1) {
		if (C_BAUD(tty) && tty_port_initialized(port))
			tty_port_raise_dtr_rts(port);

		set_current_state(TASK_INTERRUPTIBLE);

		if (tty_hung_up_p(filp) || !tty_port_initialized(port)) {
			retval = (port->flags & ASYNC_HUP_NOTIFY) ?
					-EAGAIN : -ERESTARTSYS;
			break;
		}

		cd = tty_port_carrier_raised(port);
		if (do_clocal || cd)
			break;

		if (signal_pending(current)) {
			retval = -ERESTARTSYS;
			break;
		}

		if (debug_level >= DEBUG_LEVEL_INFO)
			printk("%s(%d):%s block_til_ready() count=%d\n",
				 __FILE__,__LINE__, tty->driver->name, port->count );

		tty_unlock(tty);
		schedule();
		tty_lock(tty);
	}

	set_current_state(TASK_RUNNING);
	remove_wait_queue(&port->open_wait, &wait);
	if (!tty_hung_up_p(filp))
		port->count++;
	port->blocked_open--;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):%s block_til_ready() after, count=%d\n",
			 __FILE__,__LINE__, tty->driver->name, port->count );

	if (!retval)
		tty_port_set_active(port, 1);

	return retval;
}