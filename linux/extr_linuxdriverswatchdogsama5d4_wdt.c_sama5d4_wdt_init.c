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
typedef  int u32 ;
struct sama5d4_wdt {int mr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_WDT_MR ; 
 int AT91_WDT_WDDIS ; 
 scalar_t__ wdt_enabled ; 
 int wdt_read (struct sama5d4_wdt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdt_write_nosleep (struct sama5d4_wdt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sama5d4_wdt_init(struct sama5d4_wdt *wdt)
{
	u32 reg;
	/*
	 * When booting and resuming, the bootloader may have changed the
	 * watchdog configuration.
	 * If the watchdog is already running, we can safely update it.
	 * Else, we have to disable it properly.
	 */
	if (wdt_enabled) {
		wdt_write_nosleep(wdt, AT91_WDT_MR, wdt->mr);
	} else {
		reg = wdt_read(wdt, AT91_WDT_MR);
		if (!(reg & AT91_WDT_WDDIS))
			wdt_write_nosleep(wdt, AT91_WDT_MR,
					  reg | AT91_WDT_WDDIS);
	}
	return 0;
}