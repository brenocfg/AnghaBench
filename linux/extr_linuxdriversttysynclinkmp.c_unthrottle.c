#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  name; TYPE_1__* driver_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  serial_signals; scalar_t__ x_char; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_1__ SLMP_INFO ;

/* Variables and functions */
 scalar_t__ C_CRTSCTS (struct tty_struct*) ; 
 scalar_t__ DEBUG_LEVEL_INFO ; 
 scalar_t__ I_IXOFF (struct tty_struct*) ; 
 int /*<<< orphan*/  START_CHAR (struct tty_struct*) ; 
 int /*<<< orphan*/  SerialSignal_RTS ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sanity_check (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  send_xchar (struct tty_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_signals (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void unthrottle(struct tty_struct * tty)
{
	SLMP_INFO *info = tty->driver_data;
	unsigned long flags;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):%s unthrottle() entry\n",
			 __FILE__,__LINE__, info->device_name );

	if (sanity_check(info, tty->name, "unthrottle"))
		return;

	if (I_IXOFF(tty)) {
		if (info->x_char)
			info->x_char = 0;
		else
			send_xchar(tty, START_CHAR(tty));
	}

 	if (C_CRTSCTS(tty)) {
		spin_lock_irqsave(&info->lock,flags);
		info->serial_signals |= SerialSignal_RTS;
	 	set_signals(info);
		spin_unlock_irqrestore(&info->lock,flags);
	}
}