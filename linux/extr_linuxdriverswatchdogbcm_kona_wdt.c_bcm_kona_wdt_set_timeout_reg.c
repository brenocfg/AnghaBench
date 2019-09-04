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
struct bcm_kona_wdt {int dummy; } ;

/* Variables and functions */
 unsigned int SECS_TO_TICKS (int /*<<< orphan*/ ,struct bcm_kona_wdt*) ; 
 int /*<<< orphan*/  SECWDOG_COUNT_MASK ; 
 int bcm_kona_wdt_ctrl_reg_modify (struct bcm_kona_wdt*,int /*<<< orphan*/ ,unsigned int) ; 
 struct bcm_kona_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int bcm_kona_wdt_set_timeout_reg(struct watchdog_device *wdog,
					unsigned watchdog_flags)
{
	struct bcm_kona_wdt *wdt = watchdog_get_drvdata(wdog);

	return bcm_kona_wdt_ctrl_reg_modify(wdt, SECWDOG_COUNT_MASK,
					SECS_TO_TICKS(wdog->timeout, wdt) |
					watchdog_flags);
}