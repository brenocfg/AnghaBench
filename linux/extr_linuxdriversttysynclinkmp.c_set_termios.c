#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {scalar_t__ hw_stopped; TYPE_1__* driver; TYPE_2__* driver_data; } ;
struct ktermios {int c_cflag; } ;
struct TYPE_6__ {int serial_signals; int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ SLMP_INFO ;

/* Variables and functions */
 int CBAUD ; 
 int CRTSCTS ; 
 scalar_t__ C_BAUD (struct tty_struct*) ; 
 int /*<<< orphan*/  C_CRTSCTS (struct tty_struct*) ; 
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int SerialSignal_DTR ; 
 int SerialSignal_RTS ; 
 int /*<<< orphan*/  change_params (TYPE_2__*) ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_signals (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_throttled (struct tty_struct*) ; 
 int /*<<< orphan*/  tx_release (struct tty_struct*) ; 

__attribute__((used)) static void set_termios(struct tty_struct *tty, struct ktermios *old_termios)
{
	SLMP_INFO *info = tty->driver_data;
	unsigned long flags;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):%s set_termios()\n", __FILE__,__LINE__,
			tty->driver->name );

	change_params(info);

	/* Handle transition to B0 status */
	if ((old_termios->c_cflag & CBAUD) && !C_BAUD(tty)) {
		info->serial_signals &= ~(SerialSignal_RTS | SerialSignal_DTR);
		spin_lock_irqsave(&info->lock,flags);
	 	set_signals(info);
		spin_unlock_irqrestore(&info->lock,flags);
	}

	/* Handle transition away from B0 status */
	if (!(old_termios->c_cflag & CBAUD) && C_BAUD(tty)) {
		info->serial_signals |= SerialSignal_DTR;
		if (!C_CRTSCTS(tty) || !tty_throttled(tty))
			info->serial_signals |= SerialSignal_RTS;
		spin_lock_irqsave(&info->lock,flags);
	 	set_signals(info);
		spin_unlock_irqrestore(&info->lock,flags);
	}

	/* Handle turning off CRTSCTS */
	if (old_termios->c_cflag & CRTSCTS && !C_CRTSCTS(tty)) {
		tty->hw_stopped = 0;
		tx_release(tty);
	}
}