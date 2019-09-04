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
struct watchdog_device {int dummy; } ;
struct sama5d4_wdt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_WDT_CR ; 
 int AT91_WDT_KEY ; 
 int AT91_WDT_WDRSTT ; 
 struct sama5d4_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  wdt_write (struct sama5d4_wdt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sama5d4_wdt_ping(struct watchdog_device *wdd)
{
	struct sama5d4_wdt *wdt = watchdog_get_drvdata(wdd);

	wdt_write(wdt, AT91_WDT_CR, AT91_WDT_KEY | AT91_WDT_WDRSTT);

	return 0;
}