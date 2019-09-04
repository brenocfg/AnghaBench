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
struct lpc18xx_wdt_dev {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  lpc18xx_wdt_timer_feed (int /*<<< orphan*/ *) ; 
 struct lpc18xx_wdt_dev* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int lpc18xx_wdt_stop(struct watchdog_device *wdt_dev)
{
	struct lpc18xx_wdt_dev *lpc18xx_wdt = watchdog_get_drvdata(wdt_dev);

	lpc18xx_wdt_timer_feed(&lpc18xx_wdt->timer);

	return 0;
}