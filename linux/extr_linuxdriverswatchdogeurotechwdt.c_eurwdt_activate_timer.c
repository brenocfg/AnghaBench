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
 int /*<<< orphan*/  WDT_CTRL_REG ; 
 int WDT_EVENT_INT ; 
 int WDT_EVENT_REBOOT ; 
 int /*<<< orphan*/  WDT_OUTPIN_CFG ; 
 int /*<<< orphan*/  WDT_TIMER_CFG ; 
 int WDT_UNIT_SECS ; 
 int /*<<< orphan*/  WDT_UNIT_SEL ; 
 int /*<<< orphan*/  eurwdt_disable_timer () ; 
 int /*<<< orphan*/  eurwdt_set_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eurwdt_write_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ev ; 
 int irq ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eurwdt_activate_timer(void)
{
	eurwdt_disable_timer();
	eurwdt_write_reg(WDT_CTRL_REG, 0x01);	/* activate the WDT */
	eurwdt_write_reg(WDT_OUTPIN_CFG,
		!strcmp("int", ev) ? WDT_EVENT_INT : WDT_EVENT_REBOOT);

	/* Setting interrupt line */
	if (irq == 2 || irq > 15 || irq < 0) {
		pr_err("invalid irq number\n");
		irq = 0;	/* if invalid we disable interrupt */
	}
	if (irq == 0)
		pr_info("interrupt disabled\n");

	eurwdt_write_reg(WDT_TIMER_CFG, irq << 4);

	eurwdt_write_reg(WDT_UNIT_SEL, WDT_UNIT_SECS);	/* we use seconds */
	eurwdt_set_timeout(0);	/* the default timeout */
}