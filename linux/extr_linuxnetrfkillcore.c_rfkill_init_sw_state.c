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
struct rfkill {int registered; int persistent; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __rfkill_set_sw_state (struct rfkill*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void rfkill_init_sw_state(struct rfkill *rfkill, bool blocked)
{
	unsigned long flags;

	BUG_ON(!rfkill);
	BUG_ON(rfkill->registered);

	spin_lock_irqsave(&rfkill->lock, flags);
	__rfkill_set_sw_state(rfkill, blocked);
	rfkill->persistent = true;
	spin_unlock_irqrestore(&rfkill->lock, flags);
}