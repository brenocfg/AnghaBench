#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int queue; int /*<<< orphan*/  running; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 scalar_t__ CPU5WDT_ENABLE_REG ; 
 scalar_t__ CPU5WDT_INTERVAL ; 
 scalar_t__ CPU5WDT_MODE_REG ; 
 scalar_t__ CPU5WDT_RESET_REG ; 
 scalar_t__ CPU5WDT_TIME_A_REG ; 
 scalar_t__ CPU5WDT_TIME_B_REG ; 
 TYPE_1__ cpu5wdt_device ; 
 int /*<<< orphan*/  cpu5wdt_lock ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 scalar_t__ port ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cpu5wdt_start(void)
{
	unsigned long flags;

	spin_lock_irqsave(&cpu5wdt_lock, flags);
	if (!cpu5wdt_device.queue) {
		cpu5wdt_device.queue = 1;
		outb(0, port + CPU5WDT_TIME_A_REG);
		outb(0, port + CPU5WDT_TIME_B_REG);
		outb(1, port + CPU5WDT_MODE_REG);
		outb(0, port + CPU5WDT_RESET_REG);
		outb(0, port + CPU5WDT_ENABLE_REG);
		mod_timer(&cpu5wdt_device.timer, jiffies + CPU5WDT_INTERVAL);
	}
	/* if process dies, counter is not decremented */
	cpu5wdt_device.running++;
	spin_unlock_irqrestore(&cpu5wdt_lock, flags);
}