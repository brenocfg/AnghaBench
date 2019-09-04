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
struct pdc_wdt_dev {int /*<<< orphan*/  wdt_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pdc_wdt_stop (int /*<<< orphan*/ *) ; 
 struct pdc_wdt_dev* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void pdc_wdt_shutdown(struct platform_device *pdev)
{
	struct pdc_wdt_dev *pdc_wdt = platform_get_drvdata(pdev);

	pdc_wdt_stop(&pdc_wdt->wdt_dev);
}