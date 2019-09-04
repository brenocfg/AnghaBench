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
struct max63xx_wdt {int /*<<< orphan*/  (* set ) (struct max63xx_wdt*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MAX6369_WDSET_DISABLED ; 
 int /*<<< orphan*/  stub1 (struct max63xx_wdt*,int /*<<< orphan*/ ) ; 
 struct max63xx_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int max63xx_wdt_stop(struct watchdog_device *wdd)
{
	struct max63xx_wdt *wdt = watchdog_get_drvdata(wdd);

	wdt->set(wdt, MAX6369_WDSET_DISABLED);
	return 0;
}