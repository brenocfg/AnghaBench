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
struct iTCO_wdt_private {int /*<<< orphan*/  wddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  iTCO_wdt_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nowayout ; 
 struct iTCO_wdt_private* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int iTCO_wdt_remove(struct platform_device *pdev)
{
	struct iTCO_wdt_private *p = platform_get_drvdata(pdev);

	/* Stop the timer before we leave */
	if (!nowayout)
		iTCO_wdt_stop(&p->wddev);

	return 0;
}