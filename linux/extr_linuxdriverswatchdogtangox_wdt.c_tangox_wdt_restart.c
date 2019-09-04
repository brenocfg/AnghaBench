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
struct tangox_wdt_device {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ WD_COUNTER ; 
 struct tangox_wdt_device* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int tangox_wdt_restart(struct watchdog_device *wdt,
			      unsigned long action, void *data)
{
	struct tangox_wdt_device *dev = watchdog_get_drvdata(wdt);

	writel(1, dev->base + WD_COUNTER);

	return 0;
}