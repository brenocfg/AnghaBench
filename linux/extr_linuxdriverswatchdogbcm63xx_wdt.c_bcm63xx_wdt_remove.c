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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIMER_WDT_ID ; 
 int /*<<< orphan*/  bcm63xx_timer_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm63xx_wdt_miscdev ; 
 int /*<<< orphan*/  bcm63xx_wdt_pause () ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nowayout ; 

__attribute__((used)) static int bcm63xx_wdt_remove(struct platform_device *pdev)
{
	if (!nowayout)
		bcm63xx_wdt_pause();

	misc_deregister(&bcm63xx_wdt_miscdev);
	bcm63xx_timer_unregister(TIMER_WDT_ID);
	return 0;
}