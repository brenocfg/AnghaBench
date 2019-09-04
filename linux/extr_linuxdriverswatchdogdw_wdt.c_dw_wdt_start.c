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
struct dw_wdt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dw_wdt_arm_system_reset (struct dw_wdt*) ; 
 int /*<<< orphan*/  dw_wdt_set_timeout (struct watchdog_device*,int /*<<< orphan*/ ) ; 
 struct dw_wdt* to_dw_wdt (struct watchdog_device*) ; 

__attribute__((used)) static int dw_wdt_start(struct watchdog_device *wdd)
{
	struct dw_wdt *dw_wdt = to_dw_wdt(wdd);

	dw_wdt_set_timeout(wdd, wdd->timeout);
	dw_wdt_arm_system_reset(dw_wdt);

	return 0;
}