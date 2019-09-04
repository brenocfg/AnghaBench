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

/* Variables and functions */
 int /*<<< orphan*/  DIAG_WDOG_BUSY ; 
 int /*<<< orphan*/  EBUSY ; 
 int NOTIFY_DONE ; 
 int notifier_from_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_status ; 

__attribute__((used)) static int wdt_suspend(void)
{
	if (test_and_set_bit(DIAG_WDOG_BUSY, &wdt_status)) {
		pr_err("Linux cannot be suspended while the watchdog is in use\n");
		return notifier_from_errno(-EBUSY);
	}
	return NOTIFY_DONE;
}