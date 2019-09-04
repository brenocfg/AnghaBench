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
struct TYPE_2__ {int /*<<< orphan*/  default_ticks; scalar_t__ running; } ;

/* Variables and functions */
 int EIO ; 
 TYPE_1__ cpu5wdt_device ; 
 int /*<<< orphan*/  cpu5wdt_lock ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  ticks ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int cpu5wdt_stop(void)
{
	unsigned long flags;

	spin_lock_irqsave(&cpu5wdt_lock, flags);
	if (cpu5wdt_device.running)
		cpu5wdt_device.running = 0;
	ticks = cpu5wdt_device.default_ticks;
	spin_unlock_irqrestore(&cpu5wdt_lock, flags);
	if (verbose)
		pr_crit("stop not possible\n");
	return -EIO;
}