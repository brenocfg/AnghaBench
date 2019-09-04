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

/* Variables and functions */
 int /*<<< orphan*/  ACPI_WDAT_RESET ; 
 int /*<<< orphan*/  to_wdat_wdt (struct watchdog_device*) ; 
 int wdat_wdt_run_action (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wdat_wdt_ping(struct watchdog_device *wdd)
{
	return wdat_wdt_run_action(to_wdat_wdt(wdd), ACPI_WDAT_RESET, 0, NULL);
}