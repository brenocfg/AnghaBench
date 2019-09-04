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
struct watchdog_device {unsigned int timeout; } ;
struct mei_wdt {unsigned int timeout; } ;

/* Variables and functions */
 struct mei_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int mei_wdt_ops_set_timeout(struct watchdog_device *wdd,
				   unsigned int timeout)
{

	struct mei_wdt *wdt = watchdog_get_drvdata(wdd);

	/* valid value is already checked by the caller */
	wdt->timeout = timeout;
	wdd->timeout = timeout;

	return 0;
}