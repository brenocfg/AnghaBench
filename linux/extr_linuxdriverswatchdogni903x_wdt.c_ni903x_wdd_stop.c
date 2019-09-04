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
struct ni903x_wdt {scalar_t__ io_base; } ;

/* Variables and functions */
 scalar_t__ NIWD_CONTROL ; 
 int /*<<< orphan*/  NIWD_CONTROL_RESET ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 struct ni903x_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int ni903x_wdd_stop(struct watchdog_device *wdd)
{
	struct ni903x_wdt *wdt = watchdog_get_drvdata(wdd);

	outb(NIWD_CONTROL_RESET, wdt->io_base + NIWD_CONTROL);

	return 0;
}