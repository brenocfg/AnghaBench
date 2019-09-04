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
struct mgsl_struct {char x_char; int /*<<< orphan*/  irq_spinlock; int /*<<< orphan*/  tx_enabled; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 scalar_t__ debug_level ; 
 scalar_t__ mgsl_paranoia_check (struct mgsl_struct*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usc_start_transmitter (struct mgsl_struct*) ; 

__attribute__((used)) static void mgsl_send_xchar(struct tty_struct *tty, char ch)
{
	struct mgsl_struct *info = tty->driver_data;
	unsigned long flags;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgsl_send_xchar(%s,%d)\n",
			 __FILE__,__LINE__, info->device_name, ch );
			 
	if (mgsl_paranoia_check(info, tty->name, "mgsl_send_xchar"))
		return;

	info->x_char = ch;
	if (ch) {
		/* Make sure transmit interrupts are on */
		spin_lock_irqsave(&info->irq_spinlock,flags);
		if (!info->tx_enabled)
		 	usc_start_transmitter(info);
		spin_unlock_irqrestore(&info->irq_spinlock,flags);
	}
}