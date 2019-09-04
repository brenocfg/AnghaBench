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
struct watchdog_device {scalar_t__ min_timeout; scalar_t__ max_timeout; int /*<<< orphan*/  max_hw_heartbeat_ms; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static void watchdog_check_min_max_timeout(struct watchdog_device *wdd)
{
	/*
	 * Check that we have valid min and max timeout values, if
	 * not reset them both to 0 (=not used or unknown)
	 */
	if (!wdd->max_hw_heartbeat_ms && wdd->min_timeout > wdd->max_timeout) {
		pr_info("Invalid min and max timeout values, resetting to 0!\n");
		wdd->min_timeout = 0;
		wdd->max_timeout = 0;
	}
}