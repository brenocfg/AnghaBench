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
typedef  int uint32_t ;
struct goldfish_battery_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  ac; int /*<<< orphan*/  battery; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int AC_STATUS_CHANGED ; 
 int BATTERY_INT_MASK ; 
 int /*<<< orphan*/  BATTERY_INT_STATUS ; 
 int BATTERY_STATUS_CHANGED ; 
 int GOLDFISH_BATTERY_READ (struct goldfish_battery_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t goldfish_battery_interrupt(int irq, void *dev_id)
{
	unsigned long irq_flags;
	struct goldfish_battery_data *data = dev_id;
	uint32_t status;

	spin_lock_irqsave(&data->lock, irq_flags);

	/* read status flags, which will clear the interrupt */
	status = GOLDFISH_BATTERY_READ(data, BATTERY_INT_STATUS);
	status &= BATTERY_INT_MASK;

	if (status & BATTERY_STATUS_CHANGED)
		power_supply_changed(data->battery);
	if (status & AC_STATUS_CHANGED)
		power_supply_changed(data->ac);

	spin_unlock_irqrestore(&data->lock, irq_flags);
	return status ? IRQ_HANDLED : IRQ_NONE;
}