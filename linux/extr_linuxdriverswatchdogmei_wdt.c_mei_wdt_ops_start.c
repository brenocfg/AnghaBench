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
struct watchdog_device {int /*<<< orphan*/  timeout; } ;
struct mei_wdt {int /*<<< orphan*/  timeout; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEI_WDT_START ; 
 struct mei_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int mei_wdt_ops_start(struct watchdog_device *wdd)
{
	struct mei_wdt *wdt = watchdog_get_drvdata(wdd);

	wdt->state = MEI_WDT_START;
	wdd->timeout = wdt->timeout;
	return 0;
}