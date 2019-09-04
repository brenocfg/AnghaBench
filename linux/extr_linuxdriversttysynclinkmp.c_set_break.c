#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  name; TYPE_1__* driver_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_1__ SLMP_INFO ;

/* Variables and functions */
 unsigned char BIT3 ; 
 int /*<<< orphan*/  CTL ; 
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int EINVAL ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,int) ; 
 unsigned char read_reg (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ sanity_check (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_reg (TYPE_1__*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static int set_break(struct tty_struct *tty, int break_state)
{
	unsigned char RegValue;
	SLMP_INFO * info = tty->driver_data;
	unsigned long flags;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):%s set_break(%d)\n",
			 __FILE__,__LINE__, info->device_name, break_state);

	if (sanity_check(info, tty->name, "set_break"))
		return -EINVAL;

	spin_lock_irqsave(&info->lock,flags);
	RegValue = read_reg(info, CTL);
 	if (break_state == -1)
		RegValue |= BIT3;
	else
		RegValue &= ~BIT3;
	write_reg(info, CTL, RegValue);
	spin_unlock_irqrestore(&info->lock,flags);
	return 0;
}