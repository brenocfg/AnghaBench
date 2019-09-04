#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* tty; } ;
struct TYPE_11__ {int serial_signals; TYPE_4__ port; int /*<<< orphan*/  lock; int /*<<< orphan*/ * tx_buf; int /*<<< orphan*/  status_timer; int /*<<< orphan*/  tx_timer; int /*<<< orphan*/  event_wait_q; int /*<<< orphan*/  status_event_wait_q; int /*<<< orphan*/  device_name; } ;
struct TYPE_9__ {int c_cflag; } ;
struct TYPE_10__ {int /*<<< orphan*/  flags; TYPE_1__ termios; } ;
typedef  TYPE_3__ SLMP_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int HUPCL ; 
 int SerialSignal_DTR ; 
 int SerialSignal_RTS ; 
 int /*<<< orphan*/  TTY_IO_ERROR ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_port (TYPE_3__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_signals (TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_port_initialized (TYPE_4__*) ; 
 int /*<<< orphan*/  tty_port_set_initialized (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void shutdown(SLMP_INFO * info)
{
	unsigned long flags;

	if (!tty_port_initialized(&info->port))
		return;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):%s synclinkmp_shutdown()\n",
			 __FILE__,__LINE__, info->device_name );

	/* clear status wait queue because status changes */
	/* can't happen after shutting down the hardware */
	wake_up_interruptible(&info->status_event_wait_q);
	wake_up_interruptible(&info->event_wait_q);

	del_timer(&info->tx_timer);
	del_timer(&info->status_timer);

	kfree(info->tx_buf);
	info->tx_buf = NULL;

	spin_lock_irqsave(&info->lock,flags);

	reset_port(info);

 	if (!info->port.tty || info->port.tty->termios.c_cflag & HUPCL) {
		info->serial_signals &= ~(SerialSignal_RTS | SerialSignal_DTR);
		set_signals(info);
	}

	spin_unlock_irqrestore(&info->lock,flags);

	if (info->port.tty)
		set_bit(TTY_IO_ERROR, &info->port.tty->flags);

	tty_port_set_initialized(&info->port, 0);
}