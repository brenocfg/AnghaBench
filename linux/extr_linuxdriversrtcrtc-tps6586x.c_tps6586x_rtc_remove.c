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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int CL_SEL_MASK ; 
 int OSC_SRC_SEL ; 
 int PRE_BYPASS ; 
 int /*<<< orphan*/  RTC_CTRL ; 
 int RTC_ENABLE ; 
 struct device* to_tps6586x_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tps6586x_update (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tps6586x_rtc_remove(struct platform_device *pdev)
{
	struct device *tps_dev = to_tps6586x_dev(&pdev->dev);

	tps6586x_update(tps_dev, RTC_CTRL, 0,
		RTC_ENABLE | OSC_SRC_SEL | PRE_BYPASS | CL_SEL_MASK);
	return 0;
}