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

/* Variables and functions */
 int /*<<< orphan*/  power_state_active_cnt ; 
 int /*<<< orphan*/  power_state_active_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void power_state_active_enable(void)
{
	unsigned long flags;

	spin_lock_irqsave(&power_state_active_lock, flags);
	power_state_active_cnt++;
	spin_unlock_irqrestore(&power_state_active_lock, flags);
}