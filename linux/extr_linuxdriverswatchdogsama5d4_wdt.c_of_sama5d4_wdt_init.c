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
struct sama5d4_wdt {int /*<<< orphan*/  mr; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_WDT_WDDBGHLT ; 
 int /*<<< orphan*/  AT91_WDT_WDDIS ; 
 int /*<<< orphan*/  AT91_WDT_WDFIEN ; 
 int /*<<< orphan*/  AT91_WDT_WDIDLEHLT ; 
 int /*<<< orphan*/  AT91_WDT_WDRSTEN ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_string (struct device_node*,char*,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int of_sama5d4_wdt_init(struct device_node *np, struct sama5d4_wdt *wdt)
{
	const char *tmp;

	wdt->mr = AT91_WDT_WDDIS;

	if (!of_property_read_string(np, "atmel,watchdog-type", &tmp) &&
	    !strcmp(tmp, "software"))
		wdt->mr |= AT91_WDT_WDFIEN;
	else
		wdt->mr |= AT91_WDT_WDRSTEN;

	if (of_property_read_bool(np, "atmel,idle-halt"))
		wdt->mr |= AT91_WDT_WDIDLEHLT;

	if (of_property_read_bool(np, "atmel,dbg-halt"))
		wdt->mr |= AT91_WDT_WDDBGHLT;

	return 0;
}