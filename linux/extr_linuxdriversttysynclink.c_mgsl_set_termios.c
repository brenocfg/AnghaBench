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
struct tty_struct {scalar_t__ hw_stopped; TYPE_1__* driver; struct mgsl_struct* driver_data; } ;
struct mgsl_struct {int serial_signals; int /*<<< orphan*/  irq_spinlock; } ;
struct ktermios {int c_cflag; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int CBAUD ; 
 int CRTSCTS ; 
 scalar_t__ C_BAUD (struct tty_struct*) ; 
 int /*<<< orphan*/  C_CRTSCTS (struct tty_struct*) ; 
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int SerialSignal_DTR ; 
 int SerialSignal_RTS ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  mgsl_change_params (struct mgsl_struct*) ; 
 int /*<<< orphan*/  mgsl_start (struct tty_struct*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_throttled (struct tty_struct*) ; 
 int /*<<< orphan*/  usc_set_serial_signals (struct mgsl_struct*) ; 

__attribute__((used)) static void mgsl_set_termios(struct tty_struct *tty, struct ktermios *old_termios)
{
	struct mgsl_struct *info = tty->driver_data;
	unsigned long flags;
	
	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgsl_set_termios %s\n", __FILE__,__LINE__,
			tty->driver->name );
	
	mgsl_change_params(info);

	/* Handle transition to B0 status */
	if ((old_termios->c_cflag & CBAUD) && !C_BAUD(tty)) {
		info->serial_signals &= ~(SerialSignal_RTS | SerialSignal_DTR);
		spin_lock_irqsave(&info->irq_spinlock,flags);
	 	usc_set_serial_signals(info);
		spin_unlock_irqrestore(&info->irq_spinlock,flags);
	}

	/* Handle transition away from B0 status */
	if (!(old_termios->c_cflag & CBAUD) && C_BAUD(tty)) {
		info->serial_signals |= SerialSignal_DTR;
		if (!C_CRTSCTS(tty) || !tty_throttled(tty))
			info->serial_signals |= SerialSignal_RTS;
		spin_lock_irqsave(&info->irq_spinlock,flags);
	 	usc_set_serial_signals(info);
		spin_unlock_irqrestore(&info->irq_spinlock,flags);
	}

	/* Handle turning off CRTSCTS */
	if (old_termios->c_cflag & CRTSCTS && !C_CRTSCTS(tty)) {
		tty->hw_stopped = 0;
		mgsl_start(tty);
	}

}