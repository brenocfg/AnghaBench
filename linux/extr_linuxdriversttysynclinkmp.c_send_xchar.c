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
struct TYPE_4__ {char x_char; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_enabled; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_1__ SLMP_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,char) ; 
 scalar_t__ sanity_check (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tx_start (TYPE_1__*) ; 

__attribute__((used)) static void send_xchar(struct tty_struct *tty, char ch)
{
	SLMP_INFO *info = tty->driver_data;
	unsigned long flags;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):%s send_xchar(%d)\n",
			 __FILE__,__LINE__, info->device_name, ch );

	if (sanity_check(info, tty->name, "send_xchar"))
		return;

	info->x_char = ch;
	if (ch) {
		/* Make sure transmit interrupts are on */
		spin_lock_irqsave(&info->lock,flags);
		if (!info->tx_enabled)
		 	tx_start(info);
		spin_unlock_irqrestore(&info->lock,flags);
	}
}