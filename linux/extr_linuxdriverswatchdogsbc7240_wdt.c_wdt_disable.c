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
 int /*<<< orphan*/  SBC7240_DISABLE_PORT ; 
 int /*<<< orphan*/  SBC7240_ENABLED_STATUS_BIT ; 
 int /*<<< orphan*/  inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_status ; 

__attribute__((used)) static void wdt_disable(void)
{
	/* disable the watchdog */
	if (test_and_clear_bit(SBC7240_ENABLED_STATUS_BIT, &wdt_status)) {
		inb_p(SBC7240_DISABLE_PORT);
		pr_info("Watchdog timer is now disabled\n");
	}
}