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
 int /*<<< orphan*/  WDT_DC ; 
 int /*<<< orphan*/  inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wd_heartbeat ; 
 int /*<<< orphan*/  wdt_ctr_load (int,int) ; 
 int /*<<< orphan*/  wdt_ctr_mode (int,int) ; 
 int /*<<< orphan*/  wdt_lock ; 

__attribute__((used)) static int wdt_start(void)
{
	unsigned long flags;
	spin_lock_irqsave(&wdt_lock, flags);
	inb_p(WDT_DC);			/* Disable watchdog */
	wdt_ctr_mode(0, 3);		/* Program CTR0 for Mode 3:
						Square Wave Generator */
	wdt_ctr_mode(1, 2);		/* Program CTR1 for Mode 2:
						Rate Generator */
	wdt_ctr_mode(2, 0);		/* Program CTR2 for Mode 0:
						Pulse on Terminal Count */
	wdt_ctr_load(0, 8948);		/* Count at 100Hz */
	wdt_ctr_load(1, wd_heartbeat);	/* Heartbeat */
	wdt_ctr_load(2, 65535);		/* Length of reset pulse */
	outb_p(0, WDT_DC);		/* Enable watchdog */
	spin_unlock_irqrestore(&wdt_lock, flags);
	return 0;
}