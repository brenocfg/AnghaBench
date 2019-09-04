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
typedef  int u32 ;
struct imx2_wdt_device {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX2_WDT_WCR ; 
 int IMX2_WDT_WCR_WDE ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static inline bool imx2_wdt_is_running(struct imx2_wdt_device *wdev)
{
	u32 val;

	regmap_read(wdev->regmap, IMX2_WDT_WCR, &val);

	return val & IMX2_WDT_WCR_WDE;
}