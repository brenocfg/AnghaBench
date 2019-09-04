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
struct bcm_kona_wdt {int dummy; } ;

/* Variables and functions */
 int SECWDOG_EN_MASK ; 
 int SECWDOG_SRSTEN_MASK ; 
 int bcm_kona_wdt_ctrl_reg_modify (struct bcm_kona_wdt*,int,int /*<<< orphan*/ ) ; 
 struct bcm_kona_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int bcm_kona_wdt_stop(struct watchdog_device *wdog)
{
	struct bcm_kona_wdt *wdt = watchdog_get_drvdata(wdog);

	return bcm_kona_wdt_ctrl_reg_modify(wdt, SECWDOG_EN_MASK |
					    SECWDOG_SRSTEN_MASK, 0);
}