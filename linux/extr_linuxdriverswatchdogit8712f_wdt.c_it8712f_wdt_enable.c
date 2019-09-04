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
 int /*<<< orphan*/  LDN_GPIO ; 
 int /*<<< orphan*/  WDT_CONTROL ; 
 int /*<<< orphan*/  it8712f_wdt_ping () ; 
 int /*<<< orphan*/  it8712f_wdt_update_margin () ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int superio_enter () ; 
 int /*<<< orphan*/  superio_exit () ; 
 int /*<<< orphan*/  superio_outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superio_select (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdt_control_reg ; 

__attribute__((used)) static int it8712f_wdt_enable(void)
{
	int ret = superio_enter();
	if (ret)
		return ret;

	pr_debug("enabling watchdog timer\n");
	superio_select(LDN_GPIO);

	superio_outb(wdt_control_reg, WDT_CONTROL);

	it8712f_wdt_update_margin();

	superio_exit();

	it8712f_wdt_ping();

	return 0;
}