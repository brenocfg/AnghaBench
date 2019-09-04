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
struct tty_struct {int /*<<< orphan*/  name; struct mgsl_struct* driver_data; } ;
struct mgsl_struct {int /*<<< orphan*/  irq_spinlock; int /*<<< orphan*/  serial_signals; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 scalar_t__ C_CRTSCTS (struct tty_struct*) ; 
 scalar_t__ DEBUG_LEVEL_INFO ; 
 scalar_t__ I_IXOFF (struct tty_struct*) ; 
 int /*<<< orphan*/  STOP_CHAR (struct tty_struct*) ; 
 int /*<<< orphan*/  SerialSignal_RTS ; 
 scalar_t__ debug_level ; 
 scalar_t__ mgsl_paranoia_check (struct mgsl_struct*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mgsl_send_xchar (struct tty_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usc_set_serial_signals (struct mgsl_struct*) ; 

__attribute__((used)) static void mgsl_throttle(struct tty_struct * tty)
{
	struct mgsl_struct *info = tty->driver_data;
	unsigned long flags;
	
	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgsl_throttle(%s) entry\n",
			 __FILE__,__LINE__, info->device_name );

	if (mgsl_paranoia_check(info, tty->name, "mgsl_throttle"))
		return;
	
	if (I_IXOFF(tty))
		mgsl_send_xchar(tty, STOP_CHAR(tty));

	if (C_CRTSCTS(tty)) {
		spin_lock_irqsave(&info->irq_spinlock,flags);
		info->serial_signals &= ~SerialSignal_RTS;
	 	usc_set_serial_signals(info);
		spin_unlock_irqrestore(&info->irq_spinlock,flags);
	}
}