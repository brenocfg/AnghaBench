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
 scalar_t__ WDT_CONFIG ; 
 int WDT_OUT_KRST ; 
 int WDT_OUT_PWROK ; 
 scalar_t__ WDT_TIMEOUT ; 
 int WDT_UNIT_SEC ; 
 int margin ; 
 int max_units ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int revision ; 
 int /*<<< orphan*/  superio_outb (int,scalar_t__) ; 

__attribute__((used)) static void it8712f_wdt_update_margin(void)
{
	int config = WDT_OUT_KRST | WDT_OUT_PWROK;
	int units = margin;

	/* Switch to minutes precision if the configured margin
	 * value does not fit within the register width.
	 */
	if (units <= max_units) {
		config |= WDT_UNIT_SEC; /* else UNIT is MINUTES */
		pr_info("timer margin %d seconds\n", units);
	} else {
		units /= 60;
		pr_info("timer margin %d minutes\n", units);
	}
	superio_outb(config, WDT_CONFIG);

	if (revision >= 0x08)
		superio_outb(units >> 8, WDT_TIMEOUT + 1);
	superio_outb(units, WDT_TIMEOUT);
}