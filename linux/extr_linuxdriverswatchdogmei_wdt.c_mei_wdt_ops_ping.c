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
struct mei_wdt {scalar_t__ state; int /*<<< orphan*/  response; scalar_t__ resp_required; } ;

/* Variables and functions */
 scalar_t__ MEI_WDT_RUNNING ; 
 scalar_t__ MEI_WDT_START ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int mei_wdt_ping (struct mei_wdt*) ; 
 int wait_for_completion_killable (int /*<<< orphan*/ *) ; 
 struct mei_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int mei_wdt_ops_ping(struct watchdog_device *wdd)
{
	struct mei_wdt *wdt = watchdog_get_drvdata(wdd);
	int ret;

	if (wdt->state != MEI_WDT_START && wdt->state != MEI_WDT_RUNNING)
		return 0;

	if (wdt->resp_required)
		init_completion(&wdt->response);

	wdt->state = MEI_WDT_RUNNING;
	ret = mei_wdt_ping(wdt);
	if (ret)
		return ret;

	if (wdt->resp_required)
		ret = wait_for_completion_killable(&wdt->response);

	return ret;
}