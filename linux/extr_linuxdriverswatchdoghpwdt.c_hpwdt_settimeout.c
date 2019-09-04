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
struct watchdog_device {unsigned int timeout; unsigned int pretimeout; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hpwdt_ping (struct watchdog_device*) ; 
 int /*<<< orphan*/  hpwdt_start (struct watchdog_device*) ; 
 scalar_t__ pretimeout ; 
 scalar_t__ watchdog_active (struct watchdog_device*) ; 

__attribute__((used)) static int hpwdt_settimeout(struct watchdog_device *wdd, unsigned int val)
{
	dev_dbg(wdd->parent, "set_timeout = %d\n", val);

	wdd->timeout = val;
	if (val <= wdd->pretimeout) {
		dev_dbg(wdd->parent, "pretimeout < timeout. Setting to zero\n");
		wdd->pretimeout = 0;
		pretimeout = 0;
		if (watchdog_active(wdd))
			hpwdt_start(wdd);
	}
	hpwdt_ping(wdd);

	return 0;
}