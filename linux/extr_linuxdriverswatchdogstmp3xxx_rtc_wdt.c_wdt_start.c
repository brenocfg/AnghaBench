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
struct watchdog_device {int timeout; } ;
struct stmp3xxx_wdt_pdata {int /*<<< orphan*/  (* wdt_set_timeout ) (int /*<<< orphan*/ ,int) ;} ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int WDOG_TICK_RATE ; 
 struct stmp3xxx_wdt_pdata* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 struct device* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int wdt_start(struct watchdog_device *wdd)
{
	struct device *dev = watchdog_get_drvdata(wdd);
	struct stmp3xxx_wdt_pdata *pdata = dev_get_platdata(dev);

	pdata->wdt_set_timeout(dev->parent, wdd->timeout * WDOG_TICK_RATE);
	return 0;
}