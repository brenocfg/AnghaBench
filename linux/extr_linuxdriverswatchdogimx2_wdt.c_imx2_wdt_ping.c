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
struct imx2_wdt_device {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX2_WDT_SEQ1 ; 
 int /*<<< orphan*/  IMX2_WDT_SEQ2 ; 
 int /*<<< orphan*/  IMX2_WDT_WSR ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct imx2_wdt_device* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int imx2_wdt_ping(struct watchdog_device *wdog)
{
	struct imx2_wdt_device *wdev = watchdog_get_drvdata(wdog);

	regmap_write(wdev->regmap, IMX2_WDT_WSR, IMX2_WDT_SEQ1);
	regmap_write(wdev->regmap, IMX2_WDT_WSR, IMX2_WDT_SEQ2);
	return 0;
}