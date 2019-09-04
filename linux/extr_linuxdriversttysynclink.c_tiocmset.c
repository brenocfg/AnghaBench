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
struct tty_struct {struct mgsl_struct* driver_data; } ;
struct mgsl_struct {int /*<<< orphan*/  irq_spinlock; int /*<<< orphan*/  serial_signals; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int /*<<< orphan*/  SerialSignal_DTR ; 
 int /*<<< orphan*/  SerialSignal_RTS ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RTS ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usc_set_serial_signals (struct mgsl_struct*) ; 

__attribute__((used)) static int tiocmset(struct tty_struct *tty,
				    unsigned int set, unsigned int clear)
{
	struct mgsl_struct *info = tty->driver_data;
 	unsigned long flags;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):%s tiocmset(%x,%x)\n",
			__FILE__,__LINE__,info->device_name, set, clear);

	if (set & TIOCM_RTS)
		info->serial_signals |= SerialSignal_RTS;
	if (set & TIOCM_DTR)
		info->serial_signals |= SerialSignal_DTR;
	if (clear & TIOCM_RTS)
		info->serial_signals &= ~SerialSignal_RTS;
	if (clear & TIOCM_DTR)
		info->serial_signals &= ~SerialSignal_DTR;

	spin_lock_irqsave(&info->irq_spinlock,flags);
 	usc_set_serial_signals(info);
	spin_unlock_irqrestore(&info->irq_spinlock,flags);

	return 0;
}