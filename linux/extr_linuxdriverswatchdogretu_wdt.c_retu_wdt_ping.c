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
struct retu_wdt_dev {int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RETU_REG_WATCHDOG ; 
 int retu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct retu_wdt_dev* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int retu_wdt_ping(struct watchdog_device *wdog)
{
	struct retu_wdt_dev *wdev = watchdog_get_drvdata(wdog);

	return retu_write(wdev->rdev, RETU_REG_WATCHDOG, wdog->timeout);
}