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
struct pic32_wdt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pic32_wdt_keepalive (struct pic32_wdt*) ; 
 struct pic32_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int pic32_wdt_ping(struct watchdog_device *wdd)
{
	struct pic32_wdt *wdt = watchdog_get_drvdata(wdd);

	pic32_wdt_keepalive(wdt);

	return 0;
}