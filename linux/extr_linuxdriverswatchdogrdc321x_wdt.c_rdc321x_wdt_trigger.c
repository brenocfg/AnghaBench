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
typedef  int /*<<< orphan*/  u32 ;
struct timer_list {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  stop; int /*<<< orphan*/  timer; scalar_t__ queue; int /*<<< orphan*/  lock; int /*<<< orphan*/  base_reg; int /*<<< orphan*/  sb_pdev; scalar_t__ running; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDC_WDT_EN ; 
 scalar_t__ RDC_WDT_INTERVAL ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ rdc321x_wdt_device ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ ticks ; 

__attribute__((used)) static void rdc321x_wdt_trigger(struct timer_list *unused)
{
	unsigned long flags;
	u32 val;

	if (rdc321x_wdt_device.running)
		ticks--;

	/* keep watchdog alive */
	spin_lock_irqsave(&rdc321x_wdt_device.lock, flags);
	pci_read_config_dword(rdc321x_wdt_device.sb_pdev,
					rdc321x_wdt_device.base_reg, &val);
	val |= RDC_WDT_EN;
	pci_write_config_dword(rdc321x_wdt_device.sb_pdev,
					rdc321x_wdt_device.base_reg, val);
	spin_unlock_irqrestore(&rdc321x_wdt_device.lock, flags);

	/* requeue?? */
	if (rdc321x_wdt_device.queue && ticks)
		mod_timer(&rdc321x_wdt_device.timer,
				jiffies + RDC_WDT_INTERVAL);
	else {
		/* ticks doesn't matter anyway */
		complete(&rdc321x_wdt_device.stop);
	}

}