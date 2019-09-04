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
typedef  int u8 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TCO_TMR (int /*<<< orphan*/ ) ; 
 int heartbeat ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 unsigned char seconds_to_ticks (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tco_lock ; 
 int /*<<< orphan*/  tcobase ; 

__attribute__((used)) static int tco_timer_set_heartbeat(int t)
{
	int ret = 0;
	unsigned char tmrval;
	unsigned long flags;
	u8 val;

	/*
	 * note seconds_to_ticks(t) > t, so if t > 0x3f, so is
	 * tmrval=seconds_to_ticks(t).  Check that the count in seconds isn't
	 * out of range on it's own (to avoid overflow in tmrval).
	 */
	if (t < 0 || t > 0x3f)
		return -EINVAL;
	tmrval = seconds_to_ticks(t);

	/* "Values of 0h-3h are ignored and should not be attempted" */
	if (tmrval > 0x3f || tmrval < 0x04)
		return -EINVAL;

	/* Write new heartbeat to watchdog */
	spin_lock_irqsave(&tco_lock, flags);
	val = inb(TCO_TMR(tcobase));
	val &= 0xc0;
	val |= tmrval;
	outb(val, TCO_TMR(tcobase));
	val = inb(TCO_TMR(tcobase));

	if ((val & 0x3f) != tmrval)
		ret = -EINVAL;
	spin_unlock_irqrestore(&tco_lock, flags);

	if (ret)
		return ret;

	heartbeat = t;
	return 0;
}