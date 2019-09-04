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
struct sp5100_tco {int /*<<< orphan*/  tcobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  SP5100_WDT_COUNT (int /*<<< orphan*/ ) ; 
 struct sp5100_tco* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tco_timer_set_timeout(struct watchdog_device *wdd,
				 unsigned int t)
{
	struct sp5100_tco *tco = watchdog_get_drvdata(wdd);

	/* Write new heartbeat to watchdog */
	writel(t, SP5100_WDT_COUNT(tco->tcobase));

	wdd->timeout = t;

	return 0;
}