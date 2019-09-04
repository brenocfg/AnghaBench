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
struct tty_struct {int /*<<< orphan*/  name; struct slgt_info* driver_data; } ;
struct slgt_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  signals; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 scalar_t__ C_CRTSCTS (struct tty_struct*) ; 
 int /*<<< orphan*/  DBGINFO (char*) ; 
 scalar_t__ I_IXOFF (struct tty_struct*) ; 
 int /*<<< orphan*/  STOP_CHAR (struct tty_struct*) ; 
 int /*<<< orphan*/  SerialSignal_RTS ; 
 scalar_t__ sanity_check (struct slgt_info*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  send_xchar (struct tty_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_signals (struct slgt_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void throttle(struct tty_struct * tty)
{
	struct slgt_info *info = tty->driver_data;
	unsigned long flags;

	if (sanity_check(info, tty->name, "throttle"))
		return;
	DBGINFO(("%s throttle\n", info->device_name));
	if (I_IXOFF(tty))
		send_xchar(tty, STOP_CHAR(tty));
 	if (C_CRTSCTS(tty)) {
		spin_lock_irqsave(&info->lock,flags);
		info->signals &= ~SerialSignal_RTS;
	 	set_signals(info);
		spin_unlock_irqrestore(&info->lock,flags);
	}
}