#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct watchdog_device {unsigned int timeout; } ;
struct ts4800_wdt {int /*<<< orphan*/  feed_val; } ;
struct TYPE_2__ {unsigned int timeout; int /*<<< orphan*/  regval; } ;

/* Variables and functions */
 int MAX_TIMEOUT_INDEX ; 
 TYPE_1__* ts4800_wdt_map ; 
 struct ts4800_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int ts4800_wdt_set_timeout(struct watchdog_device *wdd,
				  unsigned int timeout)
{
	struct ts4800_wdt *wdt = watchdog_get_drvdata(wdd);
	int i;

	for (i = 0; i < MAX_TIMEOUT_INDEX; i++) {
		if (ts4800_wdt_map[i].timeout >= timeout)
			break;
	}

	wdd->timeout = ts4800_wdt_map[i].timeout;
	wdt->feed_val = ts4800_wdt_map[i].regval;

	return 0;
}