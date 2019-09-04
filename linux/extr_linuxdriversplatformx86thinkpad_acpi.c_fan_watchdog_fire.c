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
struct work_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__ TPACPI_LIFE_RUNNING ; 
 int fan_set_enable () ; 
 int /*<<< orphan*/  fan_watchdog_reset () ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  pr_notice (char*) ; 
 scalar_t__ tpacpi_lifecycle ; 

__attribute__((used)) static void fan_watchdog_fire(struct work_struct *ignored)
{
	int rc;

	if (tpacpi_lifecycle != TPACPI_LIFE_RUNNING)
		return;

	pr_notice("fan watchdog: enabling fan\n");
	rc = fan_set_enable();
	if (rc < 0) {
		pr_err("fan watchdog: error %d while enabling fan, will try again later...\n",
		       rc);
		/* reschedule for later */
		fan_watchdog_reset();
	}
}