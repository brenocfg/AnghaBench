#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {TYPE_1__* driver_data; } ;
struct TYPE_3__ {int serial_signals; int /*<<< orphan*/  device_name; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ SLMP_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int SerialSignal_CTS ; 
 int SerialSignal_DCD ; 
 int SerialSignal_DSR ; 
 int SerialSignal_DTR ; 
 int SerialSignal_RI ; 
 int SerialSignal_RTS ; 
 unsigned int TIOCM_CAR ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RNG ; 
 unsigned int TIOCM_RTS ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  get_signals (TYPE_1__*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int tiocmget(struct tty_struct *tty)
{
	SLMP_INFO *info = tty->driver_data;
	unsigned int result;
 	unsigned long flags;

	spin_lock_irqsave(&info->lock,flags);
 	get_signals(info);
	spin_unlock_irqrestore(&info->lock,flags);

	result = ((info->serial_signals & SerialSignal_RTS) ? TIOCM_RTS : 0) |
		 ((info->serial_signals & SerialSignal_DTR) ? TIOCM_DTR : 0) |
		 ((info->serial_signals & SerialSignal_DCD) ? TIOCM_CAR : 0) |
		 ((info->serial_signals & SerialSignal_RI)  ? TIOCM_RNG : 0) |
		 ((info->serial_signals & SerialSignal_DSR) ? TIOCM_DSR : 0) |
		 ((info->serial_signals & SerialSignal_CTS) ? TIOCM_CTS : 0);

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):%s tiocmget() value=%08X\n",
			 __FILE__,__LINE__, info->device_name, result );
	return result;
}